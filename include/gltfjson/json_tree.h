#pragma once
#include <assert.h>
#include <charconv>
#include <expected>
#include <list>
#include <memory>
#include <optional>
#include <stack>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

namespace gltfjson {
namespace tree {

struct Node;
using NodePtr = std::shared_ptr<Node>;
struct NullValue
{};
struct NumberValue
{
  std::u8string Value;

  static NumberValue Create(std::u8string_view src)
  {
    return NumberValue{ .Value = { src.begin(), src.end() } };
  }
};
struct ArrayValue
{
  std::vector<NodePtr> m_values;
  void Push(const NodePtr& node) { m_values.push_back(node); }
};
struct ObjectValue
{
  std::unordered_map<std::u8string, NodePtr> m_values;
  NodePtr m_lastKey;
  void Push(const NodePtr& node);
};
struct Node
{
  std::variant<NullValue,
               bool,
               NumberValue,
               std::u8string,
               ArrayValue,
               ObjectValue>
    Var;

  template<typename T>
  const T* Ptr() const
  {
    if (std::holds_alternative<T>(Var)) {
      return &std::get<T>(Var);
    } else {
      return nullptr;
    }
  }
  template<typename T>
  T* Ptr()
  {
    if (std::holds_alternative<T>(Var)) {
      return &std::get<T>(Var);
    } else {
      return nullptr;
    }
  }
  template<typename T>
  std::optional<T> Get() const
  {
    if (std::holds_alternative<T>(Var)) {
      return std::get<T>(Var);
    } else {
      return std::nullopt;
    }
  }
  bool IsNull() const { return std::holds_alternative<NullValue>(Var); }
  template<typename T>
  std::optional<T> Number() const
  {
    if (auto n = Get<NumberValue>()) {
#ifdef _MSC_VER
      T value;
      if (auto [ptr, ec] =
            std::from_chars((const char*)n->Value.data(),
                            (const char*)n->Value.data() + n->Value.size(),
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

    } else {
      return std::nullopt;
    }
  }
  const ArrayValue* Array() const { return Ptr<ArrayValue>(); }
  ArrayValue* Array() { return Ptr<ArrayValue>(); }
  const ObjectValue* Object() const { return Ptr<ObjectValue>(); }
  ObjectValue* Object() { return Ptr<ObjectValue>(); }
  NodePtr Get(std::u8string_view target) const
  {
    if (auto object = Object()) {
      auto found = object->m_values.find({ target.begin(), target.end() });
      if (found != object->m_values.end()) {
        return found->second;
      }
    }

    return nullptr;
  }
  size_t Size() const
  {
    if (auto array = Ptr<ArrayValue>()) {
      return array->m_values.size();
    } else if (auto object = Ptr<ObjectValue>()) {
      return object->m_values.size();
    } else {
      return 0;
    }
  }
};

struct Parser
{
  std::u8string_view Src;
  uint32_t Pos = 0;
  std::stack<NodePtr> Stack;

  Parser(std::u8string_view src)
    : Src(src)
  {
  }

  Parser(std::span<const uint8_t> src)
    : Src((const char8_t*)src.data(), (const char8_t*)src.data() + src.size())
  {
  }

  bool IsEnd() const { return Pos >= Src.size(); }
  std::u8string_view Remain() const { return Src.substr(Pos); }
  std::optional<std::u8string_view> Peek(uint32_t size) const
  {
    if (Pos + size > Src.size()) {
      return std::nullopt;
    }
    return Src.substr(Pos, size);
  }
  template<typename T>
  NodePtr Push(uint32_t size, const T& value)
  {
    auto node = std::make_shared<Node>();
    node->Var = value;
    Pos += size;
    if (Stack.size()) {
      if (auto array = Stack.top()->Array()) {
        array->Push(node);
      } else if (auto object = Stack.top()->Object()) {
        object->Push(node);
      } else {
        assert(false);
      }
    }
    return node;
  }

  bool IsSpace(char8_t ch)
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

  void SkipSpace()
  {
    for (; !IsEnd(); ++Pos) {
      if (!IsSpace(Src[Pos])) {
        break;
      }
    }
  }

  std::expected<NodePtr, std::u8string> ParseExpected()
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
          break;
      }
    }

    return std::unexpected{ u8"invalid" };
  }

  NodePtr Parse()
  {
    if (auto result = ParseExpected()) {
      return *result;
    } else {
      return nullptr;
    }
  }

  std::expected<NodePtr, std::u8string> ParseSymbol(std::u8string_view target)
  {
    if (auto src = Peek(target.size())) {
      if (src->starts_with(target)) {
        if (*src == u8"null") {
          return Push(src->size(), NullValue{});
        } else if (*src == u8"true") {
          return Push(src->size(), true);
        } else if (*src == u8"false") {
          return Push(src->size(), false);
        } else {
          return std::unexpected{ std::u8string(u8"unknown symbol: ") +
                                  std::u8string{ src->begin(), src->end() } };
        }
      } else {
        return std::unexpected{ std::u8string(u8"unknown symbol: ") +
                                std::u8string{ src->begin(), src->end() } };
      }
    } else {
      return std::unexpected{ u8"Not enough size" };
    }
  }

  std::expected<NodePtr, std::u8string> ParseNumber()
  {
    auto src = Remain();
#ifdef _MSC_VER
    double value;
    if (auto [ptr, ec] = std::from_chars(
          (const char*)src.data(), (const char*)src.data() + src.size(), value);
        ec == std::errc{}) {
      auto size = ptr - (const char*)src.data();
      return Push(size, NumberValue::Create(src.substr(0, size)));
    } else {
      return std::unexpected{ u8"Invaild number" };
    }
#else
    std::string str((const char*)src.data(),
                    (const char*)src.data() + src.size());
    size_t i;
    std::stod(str, &i);
    return Push(i, NumberValue::Create(src.substr(0, i)));
#endif
  }

  std::expected<NodePtr, std::u8string> ParseString()
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

    return Push(close - Pos + 1,
                std::u8string{ Src.begin() + (Pos + 1), Src.begin() + close });
  }

  std::expected<NodePtr, std::u8string> ParseArray()
  {
    assert(Src[Pos] == '[');

    auto beginPos = Pos;
    Stack.push(Push(1, ArrayValue()));
    auto node = Stack.top();

    for (int i = 0; !IsEnd(); ++i) {
      SkipSpace();
      if (Src[Pos] == ']') {
        // closed
        ++Pos;
        // auto node = Stack.top();
        assert(node == Stack.top());
        Stack.pop();
        return node;
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

  std::expected<NodePtr, std::u8string> ParseObject()
  {
    assert(Src[Pos] == '{');

    auto beginPos = Pos;
    Stack.push(Push(1, ObjectValue{}));

    for (int i = 0; !IsEnd(); ++i) {
      SkipSpace();
      if (Src[Pos] == '}') {
        // closed
        ++Pos;
        auto node = Stack.top();
        Stack.pop();
        return node;
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
      // assert(Values.back().Type == ValueType::Primitive);
      // assert(Values.back().Range.front() == '"');

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
};

void
ObjectValue::Push(const NodePtr& node)
{
  if (m_lastKey) {
    auto key = *m_lastKey->Get<std::u8string>();
    m_values.insert({ key, node });
    m_lastKey = {};
  } else {
    m_lastKey = node;
  }
}

}
}
