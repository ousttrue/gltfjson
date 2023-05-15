#pragma once
#include "format.h"
#include <algorithm>
#include <charconv>
#include <expected>
#include <string>

namespace gltfjson {
namespace json {

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

struct Json
{
  std::u8string_view Range;
  bool operator==(const Json& rhs) const { return Range == rhs.Range; }
};

struct Parser
{
  std::u8string_view Src;
  std::vector<Json> Values;
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

  std::optional<std::u8string_view> Peek(size_t size) const
  {
    if (Pos + size > Src.size()) {
      return std::nullopt;
    }
    return Src.substr(Pos, size);
  }

  std::expected<Json, std::u8string> Parse()
  {
    SkipSpace();
    if (IsEnd()) {
      return std::unexpected{ u8"empty" };
    }

    if (Src[0] == '{') {
      return ParseObject();
    } else if (Src[0] == '[') {
      return ParseArray();
    } else {
      // primitive

      switch (Src[0]) {
        case u8'"':
          return std::unexpected{ u8"not implemented" };

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

  std::expected<Json, std::u8string> ParseSymbol(std::u8string_view symbol)
  {
    if (auto src = Peek(symbol.size())) {
      if (src->starts_with(symbol)) {
        Pos += src->size();
        Values.push_back({ *src });
        return Values.back();
      } else {
        return std::unexpected{ std::u8string(u8"Not match: ") +
                                std::u8string{ src->begin(), src->end() } };
      }
    } else {
      return std::unexpected{ u8"Not enough size" };
    }
  }

  std::expected<Json, std::u8string> ParseNumber()
  {
    auto src = Remain();
    double value;
    if (auto [ptr, ec] = std::from_chars(
          (const char*)src.data(), (const char*)src.data() + src.size(), value);
        ec == std::errc{}) {
      return Json{ src.substr(0, ptr - (const char*)src.data()) };
    } else {
      return std::unexpected{ u8"fail to ParseNumber" };
    }
  }

  std::expected<Json, std::u8string> ParseObject()
  {
    return std::unexpected{ u8"not implemented" };
  }

  std::expected<Json, std::u8string> ParseArray()
  {
    return std::unexpected{ u8"not implemented" };
  }
};

}
}
