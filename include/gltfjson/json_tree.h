#pragma once
#include "json_token.h"
#include <assert.h>
#include <charconv>
#include <expected>
#include <list>
#include <memory>
#include <optional>
#include <span>
#include <stack>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

namespace gltfjson {
namespace tree {

struct Node;
using NodePtr = std::shared_ptr<Node>;
using ArrayValue = std::vector<NodePtr>;
using ObjectValue = std::unordered_map<std::u8string, NodePtr>;
struct Node
{
  std::
    variant<std::monostate, bool, float, std::u8string, ArrayValue, ObjectValue>
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
  // template<typename T>
  // std::optional<T> Value() const
  // {
  //   if (std::holds_alternative<T>(Var)) {
  //     return std::get<T>(Var);
  //   } else {
  //     return std::nullopt;
  //   }
  // }
  bool IsNull() const { return std::holds_alternative<std::monostate>(Var); }
  std::u8string U8String() const
  {
    if (auto str = Ptr<std::u8string>()) {
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
  Tokenizer m_token;
  std::stack<NodePtr> Stack;

  Parser(std::u8string_view src)
    : m_token(src)
  {
  }

  Parser(std::span<const uint8_t> src)
    : m_token(
        { (const char8_t*)src.data(), (const char8_t*)src.data() + src.size() })
  {
  }

  NodePtr m_key;
  template<typename T>
  NodePtr Push(const T& value)
  {
    auto node = std::make_shared<Node>();
    node->Var = value;
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

  std::expected<NodePtr, std::u8string> ParseExpected()
  {
    m_token.SkipSpace();
    if (m_token.IsEnd()) {
      return std::unexpected{ u8"empty" };
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
    if (auto src = m_token.GetSymbol(target)) {
      if (*src == u8"null") {
        return Push(std::monostate{});
      } else if (*src == u8"true") {
        return Push(true);
      } else if (*src == u8"false") {
        return Push(false);
      } else {
        return std::unexpected{ u8"not reach here !" };
      }
    } else {
      return std::unexpected{ src.error() };
    }
  }

  std::expected<NodePtr, std::u8string> ParseNumber()
  {
    float value;
    if (auto n = m_token.GetNumber(&value)) {
      return Push(value);
    } else {
      return std::unexpected{ n.error() };
    }
  }

  std::expected<NodePtr, std::u8string> ParseString()
  {
    if (auto str = m_token.GetString()) {
      return Push(std::u8string{ str->begin() + 1, str->end() - 1 });
    } else {
      return std::unexpected{ str.error() };
    }
  }

  std::expected<NodePtr, std::u8string> ParseArray()
  {
    if (*m_token != '[') {
      return std::unexpected{ u8"Not starts with array open" };
    }
    m_token.Get(1);
    Stack.push(Push(ArrayValue()));
    auto node = Stack.top();

    for (int i = 0; !m_token.IsEnd(); ++i) {
      m_token.SkipSpace();
      if (*m_token == ']') {
        // closed
        m_token.Get(1);
        // auto node = Stack.top();
        if (node != Stack.top()) {
          return std::unexpected{ u8"open close mismatch" };
        }
        Stack.pop();
        return node;
      }

      if (i) {
        // must comma
        if (*m_token != ',') {
          return std::unexpected{ u8"comma required" };
        }
        m_token.Get(1);
        m_token.SkipSpace();
      }

      Parse();
    }

    return std::unexpected{ u8"Unclosed array" };
  }

  std::expected<NodePtr, std::u8string> ParseObject()
  {
    if (*m_token != '{') {
      return std::unexpected{ u8"Not starts with object open" };
    }
    m_token.Get(1);
    Stack.push(Push(ObjectValue{}));
    auto node = Stack.top();

    for (int i = 0; !m_token.IsEnd(); ++i) {
      m_token.SkipSpace();
      if (*m_token == '}') {
        // closed
        m_token.Get(1);
        if (node != Stack.top()) {
          return std::unexpected{ u8"open close mismatch" };
        }
        Stack.pop();
        return node;
      }

      if (i) {
        // must comma
        if (*m_token != ',') {
          return std::unexpected{ u8"comma required" };
        }
        m_token.Get(1);
        m_token.SkipSpace();
      }

      // key
      Parse();

      {
        m_token.SkipSpace();
        // must colon
        if (*m_token != ':') {
          return std::unexpected{ u8"colon required" };
        }
        m_token.Get(1);
        m_token.SkipSpace();
      }

      // value
      Parse();
    }

    return std::unexpected{ u8"Unclosed array" };
  }
};

}
}
