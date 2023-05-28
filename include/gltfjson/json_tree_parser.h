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

  std::u8string m_dst;
  std::u8string_view UnEscape(std::u8string_view src)
  {
    m_dst.clear();
    for (auto it = src.begin(); it != src.end();) {
      if (*it == '\\') {
        auto peek = it + 1;
        if (peek != src.end() && *peek == '/') {
          m_dst.push_back('/');
          ++it;
          ++it;
          continue;
        }
      }

      m_dst.push_back(*it);
      ++it;
    }
    return m_dst;
  }

  std::expected<NodePtr, std::u8string> ParseString()
  {
    if (auto str = m_token.GetString()) {
      auto unescaped = UnEscape(str->substr(1, str->size() - 2));
      return Push(std::u8string{ unescaped.data(), unescaped.size() });
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
