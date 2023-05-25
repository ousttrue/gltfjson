#pragma once
#include <charconv>
#include <expected>
#include <optional>
#include <string>

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

  std::expected<std::u8string_view, std::u8string> GetSymbol(
    std::u8string_view symbol)
  {
    if (auto src = Peek(symbol.size())) {
      if (src->starts_with(symbol)) {
        return *Get(symbol.size());
      } else {
        return std::unexpected{ std::u8string(u8"Not match: ") +
                                std::u8string{ src->begin(), src->end() } };
      }
    } else {
      return std::unexpected{ u8"Not enough size" };
    }
  }

  std::expected<std::u8string_view, std::u8string> GetNumber(float* p = nullptr)
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
      return std::unexpected{ u8"Invaild number" };
    }
#else
    std::string str((const char*)src.data(),
                    (const char*)src.data() + src.size());
    value = std::stod(str, &size);
#endif

    if (p) {
      *p = value;
    }
    return *Get(size);
  }

  std::expected<std::u8string_view, std::u8string> GetString()
  {
    if (Src[Pos] != '"') {
      return std::unexpected{ u8"Not starts with \"" };
    }

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

    return *Get(close - Pos + 1);
  }
};

}
