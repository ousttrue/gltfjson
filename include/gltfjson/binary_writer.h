#pragma once
#include <ostream>
#include <span>
#include <stdint.h>
#include <assert.h>

namespace gltfjson {

class BinaryWriter
{
  std::ostream& m_os;

public:
  BinaryWriter(std::ostream& os)
    : m_os(os)
  {
  }

  void Uint32(uint32_t value) { m_os.write((const char*)&value, 4); }
  void Bytes(std::span<const uint8_t> values)
  {
    m_os.write((const char*)values.data(), values.size());
  }
  void Padding(uint32_t size)
  {
    assert(size < 4);
    uint8_t padding[4] = { 0, 0, 0, 0 };
    Bytes({ padding, size });
  }
};

}
