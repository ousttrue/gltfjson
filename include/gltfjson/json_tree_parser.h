#pragma once
#include "json_token.h"
#include "json_tree.h"

namespace gltfjson {
namespace tree {

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

  Parser(std::string_view src)
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

  NodePtr Parse()
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
          break;
      }
    }

    // { u8"invalid" };
    return {};
  }

  NodePtr ParseSymbol(std::u8string_view target)
  {
    if (auto src = m_token.GetSymbol(target)) {
      if (*src == u8"null") {
        return Push(std::monostate{});
      } else if (*src == u8"true") {
        return Push(true);
      } else if (*src == u8"false") {
        return Push(false);
      } else {
        // { u8"not reach here !" };
        return {};
      }
    } else {
      // { src.error() };
      return {};
    }
  }

  NodePtr ParseNumber()
  {
    float value;
    if (auto n = m_token.GetNumber(&value)) {
      return Push(value);
    } else {
      // { n.error() };
      return {};
    }
  }

  NodePtr ParseString()
  {
    if (auto str = m_token.GetString()) {
      auto unescaped = unescape(str->substr(1, str->size() - 2));
      return Push(std::u8string{ unescaped.data(), unescaped.size() });
    } else {
      // { str.error() };
      return {};
    }
  }

  NodePtr ParseArray()
  {
    if (*m_token != '[') {
      // { u8"Not starts with array open" };
      return {};
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
          // { u8"open close mismatch" };
          return {};
        }
        Stack.pop();
        return node;
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

  NodePtr ParseObject()
  {
    if (*m_token != '{') {
      // { u8"Not starts with object open" };
      return {};
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
          // { u8"open close mismatch" };
          return {};
        }
        Stack.pop();
        return node;
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

}
}
