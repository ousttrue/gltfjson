#pragma once
#include "gltf.h"

namespace gltfjson {

using WriteFunc = std::function<void(std::span<const uint8_t>)>;

template<typename T>
inline Accessor
CreateAccessor();

template<>
inline Accessor
CreateAccessor<uint8_t>()
{
  return Accessor{
    .ComponentType = ComponentTypes::UNSIGNED_BYTE,
    .Type = Types::SCALAR,
  };
}
template<>
inline Accessor
CreateAccessor<uint16_t>()
{
  return Accessor{
    .ComponentType = ComponentTypes::UNSIGNED_SHORT,
    .Type = Types::SCALAR,
  };
}
template<>
inline Accessor
CreateAccessor<uint32_t>()
{
  return Accessor{
    .ComponentType = ComponentTypes::UNSIGNED_INT,
    .Type = Types::SCALAR,
  };
}
template<>
inline Accessor
CreateAccessor<float>()
{
  return Accessor{
    .ComponentType = ComponentTypes::FLOAT,
    .Type = Types::SCALAR,
  };
}
struct BinWriter
{
  WriteFunc m_write;

  std::vector<BufferView> BufferViews;
  std::vector<Accessor> Accessors;
  uint32_t BufferPosition = 0;

  BinWriter(const WriteFunc& writer)
    : m_write(writer)
  {
  }

  uint32_t PushBufferView(std::span<const uint8_t> values)
  {
    if (BufferPosition % 4) {
      // 4byte alignment
      auto size = 4 - (BufferPosition % 4);
      uint8_t padding[4] = { 0, 0, 0, 0 };
      m_write({ padding, size });
      BufferPosition += size;
    }

    m_write(values);
    auto index = BufferViews.size();
    BufferViews.push_back({
      .ByteOffset = BufferPosition,
      .ByteLength = static_cast<uint32_t>(values.size()),
    });
    BufferPosition += values.size();
    return index;
  }

  template<typename T>
  uint32_t PushAccessor(std::span<const T> values)
  {
    auto p = (const uint8_t*)values.data();
    auto bufferViewIndex = PushBufferView({ p, p + values.size() * sizeof(T) });
    auto index = Accessors.size();

    using TT = std::remove_const<T>::type;
    Accessors.push_back(CreateAccessor<TT>());
    Accessors.back().BufferView = bufferViewIndex,
    Accessors.back().Count = static_cast<uint32_t>(values.size());
    return index;
  }

  template<typename T>
  uint32_t PushAccessor(const std::vector<T> values)
  {
    return PushAccessor(std::span(values.data(), values.size()));
  }
};

} // namespace
