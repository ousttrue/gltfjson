#pragma once
#include <functional>
#include <span>
#include <stdint.h>

namespace gltfjson {

struct BinWriter
{
  std::vector<uint8_t>& m_buffer;

  struct BufferView
  {
    uint32_t ByteOffset;
    uint32_t ByteLength;
  };

  void Push(std::span<const uint8_t> values)
  {
    auto size = m_buffer.size();
    m_buffer.resize(size + values.size());
    std::copy(values.begin(), values.end(), m_buffer.data() + size);
  }

  BufferView PushBufferView(std::span<const uint8_t> values)
  {
    if (m_buffer.size() % 4) {
      // 4byte alignment
      auto size = 4 - (m_buffer.size() % 4);
      uint8_t padding[4] = { 0, 0, 0, 0 };
      Push({ padding, size });
    }
    BufferView bufferView{
      .ByteOffset = static_cast<uint32_t>(m_buffer.size()),
      .ByteLength = static_cast<uint32_t>(values.size()),
    };
    Push(values);
    return bufferView;
  }

  template<typename T>
  BufferView PushBufferView(const T* p, size_t size)
  {
    auto byteSize = sizeof(T) * size;
    return PushBufferView(std::span((const uint8_t*)p, byteSize));
  }

  template<typename T>
  BufferView PushBufferView(std::span<const T> values)
  {
    auto byteSize = sizeof(T) * values.size();
    return PushBufferView(std::span((const uint8_t*)values.data(), byteSize));
  }
};

} // namespace
