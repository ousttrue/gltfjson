#pragma once
#include <assert.h>
#include <charconv>
#include <expected>
#include <list>
#include <memory>
#include <optional>
#include <string>
#include <variant>

namespace gltfjson {
namespace tree {

struct Node;
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
  std::list<Node> Values;
};
struct ObjectValue
{
  std::list<std::tuple<std::u8string, Node>> KeyValues;
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
  static std::expected<Node, std::u8string> FromSymbol(std::u8string_view src)
  {
    Node node;
    if (src == u8"null") {
      node.Var = NullValue{};
      return node;
    } else if (src == u8"true") {
      node.Var = true;
      return node;
    } else if (src == u8"false") {
      node.Var = false;
      return node;
    } else {
      return std::unexpected{ std::u8string(u8"unknown symbol: ") +
                              std::u8string{ src.begin(), src.end() } };
    }
  }
};

struct Parser
{
  std::u8string_view Src;
  uint32_t Pos = 0;

  Parser(std::u8string_view src)
    : Src(src)
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

  std::expected<Node, std::u8string> Parse()
  {
    SkipSpace();
    if (IsEnd()) {
      return std::unexpected{ u8"empty" };
    }

    auto ch = Src[Pos];
    // if (ch == 0x7b) {
    //   return ParseObject();
    // } else if (ch == '[') {
    //   return ParseArray();
    // }
    // else
    {
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

  std::expected<Node, std::u8string> ParseSymbol(std::u8string_view target)
  {
    if (auto src = Peek(target.size())) {
      if (src->starts_with(target)) {
        Pos += src->size();
        return Node::FromSymbol(target);
      } else {
        return std::unexpected{ std::u8string(u8"Not match: ") +
                                std::u8string{ src->begin(), src->end() } };
      }
    } else {
      return std::unexpected{ u8"Not enough size" };
    }
  }

  std::expected<Node, std::u8string> ParseNumber()
  {
    auto src = Remain();
#ifdef _MSC_VER
    double value;
    if (auto [ptr, ec] = std::from_chars(
          (const char*)src.data(), (const char*)src.data() + src.size(), value);
        ec == std::errc{}) {
      auto size = ptr - (const char*)src.data();
      Node node;
      node.Var = NumberValue::Create(src.substr(0, size));
      Pos += size;
      return node;
    } else {
      return std::unexpected{ u8"Invaild number" };
    }
#else
    std::string str((const char*)src.data(),
                    (const char*)src.data() + src.size());
    size_t i;
    std::stod(str, &i);
    Node node;
    node.Var = NumberValue::Create(src.substr(0, i));
    Pos += i;
    return node;
#endif
  }

  std::expected<Node, std::u8string> ParseString()
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

    Node node;
    node.Var = std::u8string{ Src.begin() + (Pos + 1), Src.begin() + close };
    Pos = close + 1;
    return node;
  }
};

}
}
