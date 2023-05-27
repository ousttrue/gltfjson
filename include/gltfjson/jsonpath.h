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

  static std::optional<int> GetInt(std::u8string_view src)
  {
    int i;
    if (std::from_chars(
          (const char*)src.data(), (const char*)src.data() + src.size(), i)
          .ec == std::errc{}) {
      return i;
    }
    return {};
  }

  std::optional<int> GetInt(int n) const
  {
    auto i_view = (*this)[n];
    if (i_view.empty()) {
      return {};
    }

    return GetInt(i_view);
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

  std::pair<std::u8string_view, int> GetChildOfRootIndex() const
  {
    std::u8string_view childOfRoot;

    size_t size = 0;
    for (auto jp : m_str | std::views::split(DELIMITER)) {
      ++size;
      if (size == 2) {
        childOfRoot = { jp };
      } else if (size == 3) {
        if (auto i = GetInt(std::u8string_view{ jp })) {
          return { childOfRoot, *i };
        }
        break;
      }
    }
    return {};
  }
};

template<typename T>
struct JsonPathMap
{
  struct KeyValue
  {
    std::u8string Key;
    T Value;
  };
  std::list<KeyValue> m_map;

  std::optional<T> Match(std::u8string_view jsonpath)
  {
    for (auto& kv : m_map) {
      if (gltfjson::JsonPath(kv.Key).Match(jsonpath)) {
        return kv.Value;
      }
    }
    // not found
    return std::nullopt;
  }
};

}
