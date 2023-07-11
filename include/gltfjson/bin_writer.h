#pragma once
#include <functional>
#include <span>
#include <stdint.h>

namespace gltfjson {

//
// template<typename T>
// inline Accessor
// CreateAccessor();
//
// template<>
// inline Accessor
// CreateAccessor<uint8_t>()
// {
//   return Accessor{
//     .ComponentType = ComponentTypes::UNSIGNED_BYTE,
//     .Type = Types::SCALAR,
//   };
// }
// template<>
// inline Accessor
// CreateAccessor<uint16_t>()
// {
//   return Accessor{
//     .ComponentType = ComponentTypes::UNSIGNED_SHORT,
//     .Type = Types::SCALAR,
//   };
// }
// template<>
// inline Accessor
// CreateAccessor<uint32_t>()
// {
//   return Accessor{
//     .ComponentType = ComponentTypes::UNSIGNED_INT,
//     .Type = Types::SCALAR,
//   };
// }
// template<>
// inline Accessor
// CreateAccessor<float>()
// {
//   return Accessor{
//     .ComponentType = ComponentTypes::FLOAT,
//     .Type = Types::SCALAR,
//   };
// }
struct BinWriter
{
  std::vector<uint8_t> m_buffer;

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

  // template<typename T>
  // uint32_t PushAccessor(std::span<const T> values)
  // {
  //   auto p = (const uint8_t*)values.data();
  //   auto bufferViewIndex = PushBufferView({ p, p + values.size() * sizeof(T)
  //   }); auto index = Accessors.size();
  //
  //   using TT = std::remove_const<T>::type;
  //   Accessors.push_back(CreateAccessor<TT>());
  //   Accessors.back().BufferView = bufferViewIndex,
  //   Accessors.back().Count = static_cast<uint32_t>(values.size());
  //   return index;
  // }
  //
  // template<typename T>
  // uint32_t PushAccessor(const std::vector<T> values)
  // {
  //   return PushAccessor(std::span(values.data(), values.size()));
  // }
};

} // namespace
