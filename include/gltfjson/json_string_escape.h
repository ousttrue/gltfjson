#pragma once
#include <optional>
#include <string>

namespace gltfjson {

inline std::optional<uint8_t>
try_hex(char8_t c)
{
  if (c >= '0' && c <= '9') {
    return c - '0';
  }
  if (c >= 'a' && c <= 'f') {
    return 10 + c - 'a';
  } else if (c >= 'A' && c <= 'F') {
    return 10 + c - 'A';
  }
  return std::nullopt;
}

inline char32_t
to_codepoint(char8_t c0, char8_t c1, char8_t c2, char8_t c3)
{
  if (auto h0 = try_hex(c0)) {
    if (auto h1 = try_hex(c1)) {
      if (auto h2 = try_hex(c2)) {
        if (auto h3 = try_hex(c3)) {
          return *h0 << 12 | *h1 << 8 | *h2 << 4 | *h3;
        }
      }
    }
  }
  return 0xFFFD;
}

struct Utf8
{
  char8_t b0 = 0;
  char8_t b1 = 0;
  char8_t b2 = 0;
  char8_t b3 = 0;

  const char8_t* begin() const { return &b0; }

  const char8_t* end() const
  {
    if (b0 == 0) {
      return &b0;
    } else if (b1 == 0) {
      return &b1;
    } else if (b2 == 0) {
      return &b2;
    } else if (b3 == 0) {
      return &b3;
    } else {
      return (&b3) + 1;
    }
  }

  std::u8string_view view() const { return { begin(), end() }; }
};

inline Utf8
to_utf8(char32_t cp)
{
  if (cp < 0x80) {
    return {
      (char8_t)cp,
    };
  } else if (cp < 0x800) {
    return { (char8_t)(cp >> 6 | 0x1C0), (char8_t)((cp & 0x3F) | 0x80) };
  } else if (cp < 0x10000) {
    return {
      (char8_t)(cp >> 12 | 0xE0),
      (char8_t)((cp >> 6 & 0x3F) | 0x80),
      (char8_t)((cp & 0x3F) | 0x80),
    };
  } else if (cp < 0x110000) {
    return {
      (char8_t)(cp >> 18 | 0xF0),
      (char8_t)((cp >> 12 & 0x3F) | 0x80),
      (char8_t)((cp >> 6 & 0x3F) | 0x80),
      (char8_t)((cp & 0x3F) | 0x80),
    };
  } else {
    return { 0xEF, 0xBF, 0xBD };
  }
}

inline std::u8string
unescape(std::u8string_view view)
{
  std::u8string dst{ view.begin(), view.end() };
  auto it = dst.begin();
  for (; it != dst.end();) {
    if (*it == '\\') {
      // escaped
      auto next = it + 1;
      if (next == dst.end()) {
        dst.pop_back();
        break;
      } else {
        switch (*next) {
          case '\\':
            it = dst.erase(it);
            *it = '\\';
            ++it;
            break;
          case 'n':
            it = dst.erase(it);
            *it = '\n';
            ++it;
            break;
          case 'r':
            it = dst.erase(it);
            *it = '\r';
            ++it;
            break;
          case 't':
            it = dst.erase(it);
            *it = '\t';
            ++it;
            break;
          case 'u': {
            // unicode
            auto u0 = next + 1;
            if (u0 == dst.end()) {
              dst.pop_back();
              break;
            }
            auto u1 = u0 + 1;
            if (u1 == dst.end()) {
              dst.pop_back();
              dst.pop_back();
              break;
            }
            auto u2 = u1 + 1;
            if (u2 == dst.end()) {
              dst.pop_back();
              dst.pop_back();
              dst.pop_back();
              break;
            }
            auto u3 = u2 + 1;
            if (u3 == dst.end()) {
              dst.pop_back();
              dst.pop_back();
              dst.pop_back();
              dst.pop_back();
              break;
            }

            // replace utf8-sequence
            auto cp = to_codepoint(*u0, *u1, *u2, *u3);
            auto utf8 = to_utf8(cp);

            it = dst.erase(it, u3 + 1);
            it = dst.insert(it, utf8.begin(), utf8.end());

          } break;
          default:
            it = dst.erase(it);
            ++it;
            break;
        }
      }
    } else {
      ++it;
    }
  }
  return dst;
}

} // namespace
