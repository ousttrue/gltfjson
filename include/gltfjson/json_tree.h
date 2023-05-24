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
using ArrayValue = std::vector<NodePtr>;
using ObjectValue = std::unordered_map<std::u8string, NodePtr>;
struct Node
{
  std::variant<NullValue, bool, double, std::u8string, ArrayValue, ObjectValue>
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
  std::optional<T> Value() const
  {
    if (std::holds_alternative<T>(Var)) {
      return std::get<T>(Var);
    } else {
      return std::nullopt;
    }
  }
  bool IsNull() const { return std::holds_alternative<NullValue>(Var); }
  std::u8string U8String() const
  {
    if (auto str = Value<std::u8string>()) {
      return *str;
    } else {
      return u8"";
    }
  }
  const ArrayValue* Array() const { return Ptr<ArrayValue>(); }
  ArrayValue* Array() { return Ptr<ArrayValue>(); }
  const ObjectValue* Object() const { return Ptr<ObjectValue>(); }
  ObjectValue* Object() { return Ptr<ObjectValue>(); }
  NodePtr Get(size_t index) const
  {
    if (auto array = Array()) {
      return (*array)[index];
    }

    return nullptr;
  }
  NodePtr Get(std::u8string_view target) const
  {
    if (auto object = Object()) {
      auto found = object->find({ target.begin(), target.end() });
      if (found != object->end()) {
        return found->second;
      }
    }

    return nullptr;
  }
  size_t Size() const
  {
    if (auto array = Ptr<ArrayValue>()) {
      return array->size();
    } else if (auto object = Ptr<ObjectValue>()) {
      return object->size();
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
  NodePtr m_key;
  template<typename T>
  NodePtr Push(uint32_t size, const T& value)
  {
    auto node = std::make_shared<Node>();
    node->Var = value;
    Pos += size;
    if (Stack.size()) {
      if (auto array = Stack.top()->Array()) {
        array->push_back(node);
      } else if (auto object = Stack.top()->Object()) {
        if (m_key) {
          object->insert({ m_key->U8String(), node });
          m_key = nullptr;
        } else {
          m_key = node;
        }
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
      return Push(size, value);
    } else {
      return std::unexpected{ u8"Invaild number" };
    }
#else
    std::string str((const char*)src.data(),
                    (const char*)src.data() + src.size());
    size_t i;
    std::stod(str, &i);
    return Push(i, i);
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

}
}
