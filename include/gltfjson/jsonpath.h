#pragma once
#include <charconv>
#include <optional>
#include <ranges>
#include <string_view>
#include <vector>

namespace gltfjson {

const auto DELIMITER = '/';

class JsonPath
{
  std::u8string_view m_str;

public:
  JsonPath(std::u8string_view str)
    : m_str(str)
  {
  }

  size_t Size() const
  {
    size_t size = 0;
    for (auto jp : m_str | std::views::split(DELIMITER)) {
      ++size;
    }
    return size;
  }

  std::u8string_view operator[](size_t i) const
  {
    size_t size = 0;
    for (auto jp : m_str | std::views::split(DELIMITER)) {
      if (i == size) {
        return std::u8string_view{ jp };
      }
      ++size;
    }
    return {};
  }

  std::optional<int> GetInt(int n) const
  {
    auto i_view = (*this)[n];
    if (i_view.empty()) {
      return {};
    }
    int i;
    if (std::from_chars((const char*)i_view.data(),
                        (const char*)i_view.data() + i_view.size(),
                        i)
          .ec == std::errc{}) {
      return i;
    }
    return {};
  }

  std::optional<int> GetLastInt() const { return GetInt(Size() - 1); }
  std::u8string_view Back() const { return (*this)[Size() - 1]; }

  bool operator==(const JsonPath& rhs) const { return m_str == rhs.m_str; }
  bool operator!=(const JsonPath& rhs) const { return m_str != rhs.m_str; }

  bool Match(std::u8string_view rhs) const
  {
    auto ls = m_str.begin();
    auto rs = rhs.begin();

    for (; ls != m_str.end() && rs != rhs.end();) {
      auto le = std::find(ls, m_str.end(), DELIMITER);
      auto re = std::find(rs, rhs.end(), DELIMITER);

      std::u8string_view ll(ls, le);
      std::u8string_view rr(rs, re);

      if (ll == u8"*") {
        // wildcard
      } else if (ll != rr) {
        return false;
      }

      ls = le;
      if (ls != m_str.end()) {
        ++ls;
      }
      rs = re;
      if (rs != rhs.end()) {
        ++rs;
      }
    }

    return ls == m_str.end() && rs == rhs.end();
  }
};

}