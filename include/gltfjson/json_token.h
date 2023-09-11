#pragma once
#include <charconv>
#include <optional>
#include <stdlib.h>
#include <string_view>

namespace gltfjson {

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

struct Tokenizer
{
  std::u8string_view Src;
  uint32_t Pos = 0;

  Tokenizer(std::u8string_view src)
    : Src(src)
  {
  }

  char8_t operator*() const { return Src[Pos]; }

  std::u8string_view Remain() const { return Src.substr(Pos); }

  bool IsEnd() const { return Pos >= Src.size(); }

  void SkipSpace()
  {
    for (; Pos < Src.size() && IsSpace(Src[Pos]); ++Pos) {
      ;
    }
  }

  std::optional<std::u8string_view> Peek(uint32_t size) const
  {
    if (Pos + size > Src.size()) {
      return std::nullopt;
    }
    return Src.substr(Pos, size);
  }

  std::optional<std::u8string_view> Get(size_t size)
  {
    if (Pos + size > Src.size()) {
      return std::nullopt;
    }
    auto value = Src.substr(Pos, size);
    Pos += size;
    return value;
  }

  std::optional<std::u8string_view> GetSymbol(std::u8string_view symbol)
  {
    if (auto src = Peek(symbol.size())) {
      if (src->starts_with(symbol)) {
        return *Get(symbol.size());
      } else {
        // return std::unexpected{ std::u8string(u8"Not match: ") +
        //                         std::u8string{ src->begin(), src->end() } };
        return {};
      }
    } else {
      // return std::unexpected{ u8"Not enough size" };
      return {};
    }
  }

  std::optional<std::u8string_view> GetNumber(float* p = nullptr)
  {
    auto src = Remain();
    size_t size = 0;
    double value;
#ifdef _MSC_VER
    if (auto [ptr, ec] = std::from_chars(
          (const char*)src.data(), (const char*)src.data() + src.size(), value);
        ec == std::errc{}) {
      size = (ptr - (const char*)src.data());
    } else {
      // return std::unexpected{ u8"Invaild number" };
      return {};
    }
#else
    char* end;
    value = strtod((const char*)src.data(), &end);
    size = (const char8_t*)end - src.data();
#endif

    if (p) {
      *p = value;
    }
    return *Get(size);
  }

  std::optional<std::u8string_view> GetString()
  {
    if (Src[Pos] != '"') {
      // return std::unexpected{ u8"Not starts with \"" };
      return {};
    }

    auto close = Pos + 1;
    bool escaping = false;
    for (; close < Src.size(); ++close) {
      if (escaping) {
        escaping = false;
      } else {
        if (Src[close] == '\\') {
          escaping = true;
        } else if (Src[close] == '"') {
          break;
        }
      }
    }

    if (Src[close] != '"') {
      // return std::unexpected{ u8"Unclosed string" };
      return {};
    }

    return *Get(close - Pos + 1);
  }
};

}
