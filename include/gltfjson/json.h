#pragma once
#include "format.h"
#include <algorithm>
#include <assert.h>
#include <charconv>
#include <expected>
#include <stack>
#include <string>

namespace gltfjson {
namespace json {

inline bool
IsSpace(char8_t ch)
{
  switch (ch) {
    case 0x20:
    case 0x0A:
    case 0x0D:
    case 0x09:
      return true;
  }
  return false;
}

enum class ValueType
{
  // null, true, false, number or string
  Primitive,
  Array,
  Object,
};

struct Value
{
  std::u8string_view Range;
  ValueType Type = ValueType::Primitive;
  std::optional<uint32_t> ParentIndex;

  Value(std::u8string_view range = {},
        ValueType type = ValueType::Primitive,
        std::optional<uint32_t> parentIndex = std::nullopt)
    : Range(range)
    , Type(type)
    , ParentIndex(parentIndex)
  {
  }
  Value(const Value& rhs) { *this = rhs; }
  Value& operator=(const Value& rhs)
  {
    Range = rhs.Range;
    Type = rhs.Type;
    ParentIndex = rhs.ParentIndex;
    return *this;
  }

  bool operator==(const Value& rhs) const { return Range == rhs.Range; }

  // get unquoted string
  std::u8string_view String() const
  {
    assert(Range.size() >= 2);
    assert(Range.front() == '"');
    assert(Range.back() == '"');
    return Range.substr(1, Range.size() - 2);
  }
};

struct Parser
{
  std::u8string_view Src;
  std::vector<Value> Values;
  std::stack<uint32_t> Stack;
  uint32_t Pos = 0;

  Parser(std::u8string_view src)
    : Src(src)
  {
  }

  bool IsEnd() const { return Pos >= Src.size(); }

  void SkipSpace()
  {
    for (; Pos < Src.size() && IsSpace(Src[Pos]); ++Pos) {
      ;
    }
  }

  std::u8string_view Remain() const { return Src.substr(Pos); }

  std::optional<std::u8string_view> Peek(uint32_t size) const
  {
    if (Pos + size > Src.size()) {
      return std::nullopt;
    }
    return Src.substr(Pos, size);
  }

  bool Push(uint32_t size)
  {
    if (Pos + size > Src.size()) {
      return false;
    }

    auto range = Src.substr(Pos, size);
    Values.push_back({ range });
    Pos += size;
    if (Stack.size()) {
      Values.back().ParentIndex = Stack.top();
    }
    return true;
  }

  std::expected<Value, std::u8string> Parse()
  {
    SkipSpace();
    if (IsEnd()) {
      return std::unexpected{ u8"empty" };
    }

    auto ch = Src[Pos];
    if (ch == '{') {
      return ParseObject();
    } else if (ch == '[') {
      return ParseArray();
    } else {
      // primitive

      switch (ch) {
        case u8'"':
          return ParseString();

        case u8'-':
        case u8'0':
        case u8'1':
        case u8'2':
        case u8'3':
        case u8'4':
        case u8'5':
        case u8'6':
        case u8'7':
        case u8'8':
        case u8'9':
          return ParseNumber();

        case u8'n':
          return ParseSymbol(u8"null");

        case u8't':
          return ParseSymbol(u8"true");

        case u8'f':
          return ParseSymbol(u8"false");

        default:
          return std::unexpected{ u8"invalid" };
      }
    }
  }

  std::expected<Value, std::u8string> ParseSymbol(std::u8string_view symbol)
  {
    if (auto src = Peek(symbol.size())) {
      if (src->starts_with(symbol)) {
        Push(src->size());
        return Values.back();
      } else {
        return std::unexpected{ std::u8string(u8"Not match: ") +
                                std::u8string{ src->begin(), src->end() } };
      }
    } else {
      return std::unexpected{ u8"Not enough size" };
    }
  }

  std::expected<Value, std::u8string> ParseNumber()
  {
    auto src = Remain();
#ifdef _MSC_VER
    double value;
    if (auto [ptr, ec] = std::from_chars(
          (const char*)src.data(), (const char*)src.data() + src.size(), value);
        ec == std::errc{}) {
      Push(ptr - (const char*)src.data());
      return Values.back();
    } else {
      return std::unexpected{ u8"Invaild number" };
    }
#else
    std::string str((const char*)src.data(),
                    (const char*)src.data() + src.size());
    size_t i;
    std::stod(str, &i);
    Push(i);
    return Values.back();
#endif
  }

  std::expected<Value, std::u8string> ParseString()
  {
    assert(Src[Pos] == '"');

    auto close = Pos + 1;
    for (; close < Src.size(); ++close) {
      // TODO: escape
      // TODO: utf-8 multibyte
      if (Src[close] == '"') {
        break;
      }
    }

    if (Src[close] != '"') {
      return std::unexpected{ u8"Unclosed string" };
    }

    Push(close - Pos + 1);
    return Values.back();
  }

  std::expected<Value, std::u8string> ParseArray()
  {
    assert(Src[Pos] == '[');

    auto beginPos = Pos;
    auto arrayIndex = Values.size();
    Push(1);
    Values.back().Type = ValueType::Array;
    Stack.push(arrayIndex);

    for (int i = 0; !IsEnd(); ++i) {
      SkipSpace();
      if (Src[Pos] == ']') {
        // closed
        ++Pos;
        Values[arrayIndex].Range = Src.substr(beginPos, Pos - beginPos);
        Stack.pop();
        return Values[arrayIndex];
      }

      if (i) {
        // must comma
        if (Src[Pos] != ',') {
          return std::unexpected{ u8"comma required" };
        }
        ++Pos;
        SkipSpace();
      }

      Parse();
    }

    return std::unexpected{ u8"Unclosed array" };
  }

  std::expected<Value, std::u8string> ParseObject()
  {
    assert(Src[Pos] == '{');

    auto beginPos = Pos;
    auto objectIndex = Values.size();
    Push(1);
    Values.back().Type = ValueType::Object;
    Stack.push(objectIndex);

    for (int i = 0; !IsEnd(); ++i) {
      SkipSpace();
      if (Src[Pos] == '}') {
        // closed
        ++Pos;
        auto& object = Values[objectIndex];
        object.Range = Src.substr(beginPos, Pos - beginPos);
        Stack.pop();
        return object;
      }

      if (i) {
        // must comma
        if (Src[Pos] != ',') {
          return std::unexpected{ u8"comma required" };
        }
        ++Pos;
        SkipSpace();
      }

      // key
      Parse();
      assert(Values.back().Type == ValueType::Primitive);
      assert(Values.back().Range.front() == '"');

      {
        SkipSpace();
        // must colon
        if (Src[Pos] != ':') {
          return std::unexpected{ u8"colon required" };
        }
        ++Pos;
        SkipSpace();
      }

      // value
      Parse();
    }

    return std::unexpected{ u8"Unclosed array" };
  }

  std::expected<uint32_t, std::u8string> ChildCount(const Value& value) const
  {
    int i = 0;
    for (auto it = Values.begin(); it != Values.end(); ++it, ++i) {
      if (it->Range.data() == value.Range.data()) {
        // found
        if (it->Type == ValueType::Array) {
          ++it;
          int j = 0;
          for (; it != Values.end(); ++it, ++j) {
            if (it->ParentIndex != i) {
              break;
            }
          }
          return j;
        } else if (it->Type == ValueType::Object) {
          ++it;
          int j = 0;
          for (; it != Values.end(); ++it, ++j) {
            if (it->ParentIndex != i) {
              break;
            }
          }
          assert(j % 2 == 0);
          return j / 2;
        } else {
          return std::unexpected{ u8"array nor object" };
        }
      }
    }

    return std::unexpected{ u8"not found" };
  }

  std::optional<Value> GetItem(const Value& value, uint32_t index) const
  {
    int i = 0;
    for (auto it = Values.begin(); it != Values.end(); ++it, ++i) {
      if (it->Range.data() == value.Range.data()) {
        // found
        ++it;
        int j = 0;
        for (; it != Values.end(); ++it, ++j) {
          if (it->ParentIndex != i) {
            break;
          }
          if (j == index) {
            return *it;
          }
        }
      }
    }

    return std::nullopt;
  }

  std::optional<Value> GetProperty(const Value& value,
                                   std::u8string_view target) const
  {
    int i = 0;
    for (auto it = Values.begin(); it != Values.end(); ++it, ++i) {
      if (it->Range.data() == value.Range.data()) {
        // found
        ++it;
        for (; it != Values.end();) {
          if (it->ParentIndex != i) {
            break;
          }
          // key
          assert(it->Range[0] == '"');
          auto key = it->String();
          ++it;
          if (key == target) {
            return *it;
          }
          // value
          it = NextSibling(it);
        }
      }
    }

    return std::nullopt;
  }

  std::vector<Value>::const_iterator NextSibling(
    std::vector<Value>::const_iterator it) const
  {
    auto r = it->Range;
    auto p = r.data() + r.size();
    for (; it != Values.end(); ++it) {
      if (it->Range.data() > p) {
        break;
      }
    }
    return it;
  }
};

}
}
