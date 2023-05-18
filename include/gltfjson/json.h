#pragma once
#include <algorithm>
#include <assert.h>
#include <charconv>
#include <expected>
#include <optional>
#include <ostream>
#include <span>
#include <stack>
#include <stdint.h>
#include <string>
#include <vector>

namespace gltfjson {

struct Value;
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
  struct Iterator
  {
    const Value* m_arrayValue = nullptr;
    const Value* m_current = nullptr;
    bool operator!=(const Iterator& rhs) const
    {
      return m_current != rhs.m_current;
    }
    Iterator& operator++();
    const Value& operator*() const { return *m_current; }
  };

  const Value* m_arrayValue;

  Iterator begin() const;
  Iterator end() const;
  uint32_t Size() const;
  const Value* Get(uint32_t index) const;
};

struct ObjectValue
{
  struct KeyValue
  {
    const Value* Key = nullptr;
    const Value* Value = nullptr;
  };

  struct Iterator
  {
    const Value* m_objectValue = nullptr;
    KeyValue m_current;
    bool operator!=(const Iterator& rhs) const
    {
      return m_current.Key != (*rhs).Key || m_current.Value != (*rhs).Value;
    }
    Iterator& operator++();
    KeyValue operator*() const { return m_current; }
  };

  const Value* m_objectValue;

  Iterator begin() const;
  Iterator end() const;
  uint32_t Size() const;
  const Value* Get(std::u8string_view key) const;
  const Value* Get(std::string_view key) const
  {
    return Get(std::u8string_view((const char8_t*)key.data(),
                                  (const char8_t*)key.data() + key.size()));
  }
};

struct Parser;
struct Value
{
  std::u8string_view Range;
  ValueType Type = ValueType::Primitive;
  Parser* m_parser = nullptr;
  uint32_t m_pos = -1;
  std::optional<uint32_t> m_parentIndex;

  bool operator==(const Value& rhs) const { return Range == rhs.Range; }

  bool Contains(const Value& rhs) const
  {
    if (rhs.Range.data() + rhs.Range.size() < Range.data()) {
      return false;
    }
    if (rhs.Range.data() > Range.data() + Range.size()) {
      return false;
    }
    return true;
  }

  bool IsTrue() const { return Range == u8"true"; }

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

  std::optional<ArrayValue> Array() const
  {
    if (Type == ValueType::Array) {
      return ArrayValue{ this };
    }
    return std::nullopt;
  }
  std::optional<ObjectValue> Object() const
  {
    if (Type == ValueType::Object) {
      return ObjectValue{ this };
    }
    return std::nullopt;
  }

  uint32_t Size() const
  {
    switch (Type) {
      case ValueType::Array:
        if (auto array = Array()) {
          return array->Size();
        }
        break;

      case ValueType::Object:
        if (auto object = Object()) {
          return object->Size();
        }
        break;
    }
    return 0;
  }
  const Value* Get(uint32_t i) const
  {
    if (auto array = Array()) {
      return array->Get(i);
    }
    return nullptr;
  }
  const Value* Get(std::u8string_view key) const
  {
    if (auto object = Object()) {
      return object->Get(key);
    }
    return nullptr;
  }
  const Value* Get(std::string_view key) const
  {
    std::u8string str((const char8_t*)key.data(),
                      (const char8_t*)key.data() + key.size());
    return Get(str);
  }
};

inline std::ostream&
operator<<(std::ostream& os, const Value& value)
{
  os << std::string_view((const char*)value.Range.data(),
                         (const char*)value.Range.data() + value.Range.size());
  return os;
}

struct Parser
{
  friend struct Value;
  friend struct ArrayValue;
  friend struct ObjectValue;

  std::u8string_view Src;
  std::vector<Value> Values;
  std::stack<uint32_t> Stack;
  uint32_t Pos = 0;

  Parser(std::u8string_view src)
    : Src(src)
  {
  }

  Parser(std::span<const uint8_t> src)
    : Src((const char8_t*)src.data(), (const char8_t*)src.data() + src.size())
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
        .Range = range,
        .Type = ValueType::Primitive,
        .m_parser = this,
        .m_pos = static_cast<uint32_t>(Values.size()),
        .m_parentIndex = Stack.top(),
      });
    } else {
      Values.push_back({
        .Range = range,
        .Type = ValueType::Primitive,
        .m_parser = this,
        .m_pos = static_cast<uint32_t>(Values.size()),
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

inline ArrayValue::Iterator&
ArrayValue::Iterator::operator++()
{
  if (m_current) {
    auto parser = m_arrayValue->m_parser;
    for (std::vector<Value>::const_iterator it = parser->Values.begin();
         it != parser->Values.end();
         ++it) {
      if (it->Range.data() == m_current->Range.data()) {
        // found
        it = parser->NextSibling(it);
        if (it != parser->Values.end() && m_arrayValue->Contains(*it)) {
          m_current = &*it;
        } else {
          m_current = nullptr;
        }
        break;
      }
    }
  }
  return *this;
}

inline ArrayValue::Iterator
ArrayValue::begin() const
{
  auto parser = m_arrayValue->m_parser;
  for (auto it = parser->Values.begin() + m_arrayValue->m_pos;
       it != parser->Values.end();
       ++it) {
    if (it->Range.data() == m_arrayValue->Range.data()) {
      // found
      ++it;
      if (it != parser->Values.end()) {
        return { m_arrayValue, &*it };
      }
      break;
    }
  }

  return {};
}
inline ArrayValue::Iterator
ArrayValue::end() const
{
  return {};
}

inline uint32_t
ArrayValue::Size() const
{
  auto parser = m_arrayValue->m_parser;
  if (!parser) {
    return 0;
  }
  auto i = 0;
  for (auto& _ : *this) {
    ++i;
  }
  return i;
}

inline const Value*
ArrayValue::Get(uint32_t index) const
{
  auto parser = m_arrayValue->m_parser;
  if (!parser) {
    return {};
  }
  int i = 0;
  for (auto& value : *this) {
    if ((i++) == index) {
      return &value;
    }
  }
  return {};
}

inline ObjectValue::Iterator&
ObjectValue::Iterator::operator++()
{
  if (m_current.Key) {
    auto parser = m_objectValue->m_parser;
    for (std::vector<Value>::const_iterator it = parser->Values.begin();
         it != parser->Values.end();
         ++it) {
      if (it->Range.data() == m_current.Key->Range.data()) {
        // found
        m_current = {};
        ++it;
        auto key = parser->NextSibling(it);
        if (key != parser->Values.end() && m_objectValue->Contains(*key)) {
          auto value = parser->NextSibling(key);
          if (value != parser->Values.end() &&
              m_objectValue->Contains(*value)) {
            m_current = {
              .Key = &*key,
              .Value = &*value,
            };
          }
        }
        break;
      }
    }
  }
  return *this;
}

inline ObjectValue::Iterator
ObjectValue::begin() const
{
  auto parser = m_objectValue->m_parser;
  for (std::vector<Value>::const_iterator it =
         parser->Values.begin() + m_objectValue->m_pos;
       it != parser->Values.end();
       ++it) {
    if (it->Range.data() == m_objectValue->Range.data()) {
      // found
      ++it;
      if (it != parser->Values.end()) {
        KeyValue kv{ &*it };
        ++it;
        if (it != parser->Values.end()) {
          kv.Value = &*it;
          return { m_objectValue, kv };
        }
      }
      break;
    }
  }

  return {};
}

inline ObjectValue::Iterator
ObjectValue::end() const
{
  return {};
}

inline uint32_t
ObjectValue::Size() const
{
  auto parser = m_objectValue->m_parser;
  if (!parser) {
    return 0;
  }
  auto i = 0;
  for (auto _ : *this) {
    ++i;
  }
  return i;
}

inline const Value*
ObjectValue::Get(std::u8string_view target) const
{
  auto parser = m_objectValue->m_parser;
  if (!parser) {
    return {};
  }

  for (auto [key, value] : *this) {
    if (key->String() == target) {
      return value;
    }
  }

  return {};
}

}
