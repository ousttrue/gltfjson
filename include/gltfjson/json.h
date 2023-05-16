#pragma once
#include <algorithm>
#include <assert.h>
#include <charconv>
#include <expected>
#include <optional>
#include <stack>
#include <stdint.h>
#include <string>
#include <vector>

namespace gltfjson {

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

struct ArrayValue
{
  const struct Value* m_arrayValue;

  uint32_t Size() const;
  const struct Value* Get(uint32_t index) const;
};

struct Parser;
struct Value
{
  std::u8string_view Range;
  ValueType Type = ValueType::Primitive;
  Parser* m_parser = nullptr;
  std::optional<uint32_t> m_parentIndex;
  uint32_t Size() const;
  std::optional<Value> Get(std::u8string_view key) const;
  std::optional<Value> Get(std::string_view key) const
  {
    return Get(std::u8string_view((const char8_t*)key.data(),
                                  (const char8_t*)key.data() + key.size()));
  }

  Value(std::u8string_view range = {},
        ValueType type = ValueType::Primitive,
        Parser* parser = nullptr,
        std::optional<uint32_t> parentIndex = std::nullopt)
    : Range(range)
    , Type(type)
    , m_parser(parser)
    , m_parentIndex(parentIndex)
  {
  }
  Value(const Value& rhs) { *this = rhs; }
  Value& operator=(const Value& rhs)
  {
    Range = rhs.Range;
    Type = rhs.Type;
    m_parser = rhs.m_parser;
    m_parentIndex = rhs.m_parentIndex;
    return *this;
  }

  bool operator==(const Value& rhs) const { return Range == rhs.Range; }

  // get unquoted string
  std::optional<std::u8string_view> String() const
  {
    if (Range.size() >= 2 && Range.front() == '"' && Range.back() == '"') {
      return Range.substr(1, Range.size() - 2);
    }

    return std::nullopt;
  }

  template<typename T>
  std::optional<T> Number() const
  {
#ifdef _MSC_VER
    T value;
    if (auto [ptr, ec] =
          std::from_chars((const char*)Range.data(),
                          (const char*)Range.data() + Range.size(),
                          value);
        ec == std::errc{}) {
      return value;
    } else {
      return std::nullopt;
    }
#else
    std::string str((const char*)Range.data(),
                    (const char*)Range.data() + Range.size());
    return std::stod(str, &i);
#endif
  }

  std::optional<ArrayValue> Array() const { return ArrayValue{ this }; }
};

struct Parser
{
  friend struct Value;
  friend struct ArrayValue;

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
    if (Stack.size()) {
      Values.push_back({
        range,
        ValueType::Primitive,
        this,
        Stack.top(),
      });
    } else {
      Values.push_back({
        range,
        ValueType::Primitive,
        this,
      });
    }
    Pos += size;
    return true;
  }

  std::expected<Value, std::u8string> Parse()
  {
    SkipSpace();
    if (IsEnd()) {
      return std::unexpected{ u8"empty" };
    }

    auto ch = Src[Pos];
    if (ch == 0x7b) {
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

private:
  uint32_t ChildCount(const Value& value) const
  {
    int i = 0;
    for (auto it = Values.begin(); it != Values.end(); ++it, ++i) {
      if (it->Range.data() == value.Range.data()) {
        // found
        if (it->Type == ValueType::Array) {
          ++it;
          int j = 0;
          for (; it != Values.end(); ++it, ++j) {
            if (!it->m_parentIndex || *it->m_parentIndex != i) {
              break;
            }
          }
          return j;
        } else if (it->Type == ValueType::Object) {
          ++it;
          int j = 0;
          for (; it != Values.end(); ++it, ++j) {
            if (!it->m_parentIndex || *it->m_parentIndex != i) {
              break;
            }
          }
          assert(j % 2 == 0);
          return j / 2;
        } else {
          // return std::unexpected{ u8"array nor object" };
          return 0;
        }
      }
    }

    // return std::unexpected{ u8"not found" };
    return 0;
  }

  const Value* GetItem(const Value& value, uint32_t index) const
  {
    int i = 0;
    for (auto it = Values.begin(); it != Values.end(); ++it, ++i) {
      if (it->Range.data() == value.Range.data()) {
        // found
        ++it;
        int j = 0;
        for (; it != Values.end(); ++it, ++j) {
          if (!it->m_parentIndex || *it->m_parentIndex != i) {
            break;
          }
          if (j == index) {
            return &*it;
          }
        }
      }
    }

    return nullptr;
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
          if (!it->m_parentIndex || *it->m_parentIndex != i) {
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

inline uint32_t
Value::Size() const
{
  if (m_parser) {
    return m_parser->ChildCount(*this);
  } else {
    return 0;
  }
}

inline const Value*
ArrayValue::Get(uint32_t index) const
{
  if (auto parser = m_arrayValue->m_parser) {
    return parser->GetItem(*m_arrayValue, index);
  } else {
    return {};
  }
}

inline std::optional<Value>
Value::Get(std::u8string_view key) const
{
  if (m_parser) {
    return m_parser->GetProperty(*this, key);
  } else {
    return std::nullopt;
  }
}

}
