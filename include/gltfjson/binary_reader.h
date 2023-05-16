#pragma once
#include <span>
#include <stdint.h>
#include <string_view>

namespace gltfjson {

class BinaryReader
{
  std::span<const uint8_t> m_data;
  size_t m_pos = 0;

public:
  BinaryReader(std::span<const uint8_t> data)
    : m_data(data)
  {
  }

  template<typename T>
  T Get()
  {
    auto value = *((T*)&m_data[m_pos]);
    m_pos += sizeof(T);
    return value;
  }

  void Resize(size_t len) { m_data = std::span(m_data.begin(), len); }

  std::span<const uint8_t> Span(size_t size)
  {
    auto value = m_data.subspan(m_pos, size);
    m_pos += size;
    return value;
  }

  std::string_view StringView(size_t size)
  {
    auto value = m_data.subspan(m_pos, size);
    m_pos += size;
    return std::string_view((const char*)value.data(),
                            (const char*)value.data() + value.size());
  }

  bool is_end() const { return m_pos >= m_data.size(); }
};

}
