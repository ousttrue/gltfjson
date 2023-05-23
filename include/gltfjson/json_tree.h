#pragma once
#include <expected>
#include <memory>
#include <optional>
#include <string>

namespace gltfjson {
namespace tree {

enum class NodeTypes
{
  Null,
  True,
  False,
  Number,
  String,
  Array,
  Object,
};
inline std::optional<NodeTypes>
GetSymbol(std::u8string_view src)
{
  if (src == u8"true") {
    return NodeTypes::True;
  } else if (src == u8"false") {
    return NodeTypes::False;
  } else if (src == u8"null") {
    return NodeTypes::Null;
  } else {
    return std::nullopt;
  }
}

struct Node
{
  NodeTypes Type = {};
  bool IsTrue() const { return Type == NodeTypes::True; }
  bool IsFalse() const { return Type == NodeTypes::False; }
  bool IsNull() const { return Type == NodeTypes::Null; }
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
          //     case u8'"':
          //       return ParseString();
          //
          //     case u8'-':
          //     case u8'0':
          //     case u8'1':
          //     case u8'2':
          //     case u8'3':
          //     case u8'4':
          //     case u8'5':
          //     case u8'6':
          //     case u8'7':
          //     case u8'8':
          //     case u8'9':
          //       return ParseNumber();
          //
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
    if (auto symbol = GetSymbol(target)) {
      if (auto src = Peek(target.size())) {
        if (src->starts_with(target)) {
          Pos += src->size();
          return Node{ *symbol };
        } else {
          return std::unexpected{ std::u8string(u8"Not match: ") +
                                  std::u8string{ src->begin(), src->end() } };
        }
      } else {
        return std::unexpected{ u8"Not enough size" };
      }
    } else {
      return std::unexpected{ u8"Unknown symbol" };
    }
  }
};

}
}
