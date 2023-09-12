#pragma once
#include "json_string_escape.h"
#include "json_token.h"
#include <algorithm>
#include <assert.h>
#include <charconv>
#include <optional>
#include <ostream>
#include <span>
#include <stack>
#include <stdint.h>
#include <string>
#include <vector>
#if !defined(_MSC_VER)
#include <stdlib.h> // strtod
#endif

namespace gltfjson {

struct Value;
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
    bool operator==(const Iterator& rhs) const
    {
      return m_current == rhs.m_current;
    }
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
    bool operator==(const Iterator& rhs) const
    {
      return m_current.Key == (*rhs).Key && m_current.Value == (*rhs).Value;
    }
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
  uint32_t m_pos = (uint32_t)-1;
  uint32_t m_stride = 1;
  std::optional<uint32_t> m_parentIndex;

  bool operator==(const Value& rhs) const { 
    return Range == rhs.Range; 
  }

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
  std::optional<std::u8string> U8String() const
  {
    if (Range.size() >= 2 && Range.front() == '"' && Range.back() == '"') {
      auto view = Range.substr(1, Range.size() - 2);
      return unescape(view);
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
    char* end;
    return strtod((const char*)Range.data(), &end);
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

      default:
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

  std::vector<Value> Values;
  std::stack<uint32_t> Stack;

  Tokenizer m_token;

  Parser(std::u8string_view src)
    : m_token(src)
  {
  }

  Parser(std::span<const uint8_t> src)
    : m_token(
        { (const char8_t*)src.data(), (const char8_t*)src.data() + src.size() })
  {
  }

  void Push(std::u8string_view range)
  {
    // if (auto range = m_token.Get(size)) {
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
    // return true;
    // } else {
    //   return false;
    // }
  }

  std::optional<Value> Parse()
  {
    m_token.SkipSpace();
    if (m_token.IsEnd()) {
      // { u8"empty" };
      return {};
    }

    auto ch = *m_token;
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
          // { u8"invalid" };
          return {};
      }
    }
  }

  std::optional<Value> ParseSymbol(std::u8string_view symbol)
  {
    if (auto read = m_token.GetSymbol(symbol)) {
      Push(*read);
      return Values.back();
    } else {
      // { read.error() };
      return {};
    }
  }

  std::optional<Value> ParseNumber()
  {
    if (auto read = m_token.GetNumber()) {
      Push(*read);
      return Values.back();
    } else {
      // { read.error() };
      return {};
    }
  }

  std::optional<Value> ParseString()
  {
    if (auto read = m_token.GetString()) {
      Push(*read);
      return Values.back();
    } else {
      // { read.error() };
      return {};
    }
  }

  std::optional<Value> ParseArray()
  {
    assert(*m_token == '[');
    auto open = *m_token.Get(1);
    auto arrayIndex = Values.size();
    Push(open);
    Values.back().Type = ValueType::Array;
    Stack.push(arrayIndex);

    for (int i = 0; !m_token.IsEnd(); ++i) {
      m_token.SkipSpace();
      if (*m_token == ']') {
        // closed
        auto close = *m_token.Get(1);
        auto& array = Values[arrayIndex];
        array.Range = { open.data(), close.data() + close.size() };
        array.m_stride = static_cast<uint32_t>(Values.size()) - array.m_pos;
        Stack.pop();
        return Values[arrayIndex];
      }

      if (i) {
        // must comma
        if (*m_token != ',') {
          // { u8"comma required" };
          return {};
        }
        m_token.Get(1);
        m_token.SkipSpace();
      }

      Parse();
    }

    // { u8"Unclosed array" };
    return {};
  }

  std::optional<Value> ParseObject()
  {
    assert(*m_token == '{');
    auto objectIndex = Values.size();
    auto open = *m_token.Get(1);
    Push(open);
    Values.back().Type = ValueType::Object;
    Stack.push(objectIndex);

    for (int i = 0; !m_token.IsEnd(); ++i) {
      m_token.SkipSpace();
      if (*m_token == '}') {
        // closed
        auto close = *m_token.Get(1);
        auto& object = Values[objectIndex];
        object.Range = { open.data(), close.data() + close.size() };
        object.m_stride = static_cast<uint32_t>(Values.size()) - object.m_pos;
        Stack.pop();
        return object;
      }

      if (i) {
        // must comma
        if (*m_token != ',') {
          // { u8"comma required" };
          return {};
        }
        m_token.Get(1);
        m_token.SkipSpace();
      }

      // key
      Parse();
      assert(Values.back().Type == ValueType::Primitive);
      assert(Values.back().Range.front() == '"');

      {
        m_token.SkipSpace();
        // must colon
        if (*m_token != ':') {
          // { u8"colon required" };
          return {};
        }
        m_token.Get(1);
        m_token.SkipSpace();
      }

      // value
      Parse();
    }

    // { u8"Unclosed array" };
    return {};
  }
};

inline ArrayValue::Iterator&
ArrayValue::Iterator::operator++()
{
  if (m_current) {
    auto parser = m_arrayValue->m_parser;
    std::vector<Value>::const_iterator it =
      parser->Values.begin() + m_current->m_pos;
    it += it->m_stride;
    if (it != parser->Values.end() && m_arrayValue->Contains(*it)) {
      m_current = &*it;
      return *this;
    }
  }

  m_current = {};
  return *this;
}

inline ArrayValue::Iterator
ArrayValue::begin() const
{
  auto parser = m_arrayValue->m_parser;
  auto it = parser->Values.begin() + m_arrayValue->m_pos;
  // child
  ++it;
  if (it != parser->Values.end() && m_arrayValue->Contains(*it)) {
    return { m_arrayValue, &*it };
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
  for ([[maybe_unused]] auto& _ : *this) {
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
    std::vector<Value>::const_iterator it =
      parser->Values.begin() + m_current.Value->m_pos;
    auto key = it + it->m_stride;
    if (key != parser->Values.end() && m_objectValue->Contains(*key)) {
      auto value = key + key->m_stride;
      if (value != parser->Values.end() && m_objectValue->Contains(*value)) {
        m_current = {
          .Key = &*key,
          .Value = &*value,
        };
        return *this;
      }
    }
  }

  m_current = {};
  return *this;
}

inline ObjectValue::Iterator
ObjectValue::begin() const
{
  auto parser = m_objectValue->m_parser;
  std::vector<Value>::const_iterator it =
    parser->Values.begin() + m_objectValue->m_pos;
  // child
  ++it;
  if (it != parser->Values.end() && m_objectValue->Contains(*it)) {
    KeyValue kv{ &*it };
    ++it;
    if (it != parser->Values.end() && m_objectValue->Contains(*it)) {
      kv.Value = &*it;
      return { m_objectValue, kv };
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
  for ([[maybe_unused]] auto _ : *this) {
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
    if (key->U8String() == target) {
      return value;
    }
  }

  return {};
}
}
