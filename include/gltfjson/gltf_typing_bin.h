#pragma once
#include "directory.h"
#include "gltf_typing.h"

namespace gltfjson {

struct Bin
{
  std::shared_ptr<Directory> Dir;
  std::span<const uint8_t> Bytes;

  std::optional<std::span<const uint8_t>> GetBufferViewBytes(
    const Root& gltf,
    int buffer_view_index) const
  {
    if (buffer_view_index < 0 || buffer_view_index >= gltf.BufferViews.size()) {
      // { "buffer_view_index is out of range" };
      return {};
    }

    auto buffer_view = gltf.BufferViews[buffer_view_index];
    // std::cout << buffer_view << std::endl;

    int buffer_index = *buffer_view.Buffer();
    auto buffer = gltf.Buffers[buffer_index];
    auto uri = buffer.Uri();
    if (uri.size()) {
      // external file
      if (auto bytes = Dir->GetBuffer(uri)) {
        return bytes->subspan(value_or<uint32_t>(buffer_view.ByteOffset(), 0),
                              (size_t)*buffer_view.ByteLength());
      } else {
        return bytes;
      }
    } else {
      // glb
      return Bytes.subspan(value_or<uint32_t>(buffer_view.ByteOffset(), 0),
                           (size_t)*buffer_view.ByteLength());
    }
  }

  template<typename S, typename T>
  bool GetSparseValue(const Root& gltf,
                      std::span<const S> indices,
                      uint32_t buffer_view_index,
                      std::span<T> dst) const
  {
    if (auto span = GetBufferViewBytes(gltf, buffer_view_index)) {
      assert(indices.size() == span->size() / sizeof(T));
      auto p = (const T*)span->data();
      for (int i = 0; i < indices.size(); ++i) {
        dst[i] = p[indices[i]];
      }
      return true;
    } else {
      // { span.error() };
      return false;
    }
  }

  mutable std::vector<uint8_t> m_sparseBuffer;
  template<typename T>
  std::optional<std::span<const T>> GetAccessorBytes(
    const Root& gltf,
    const Accessor& accessor) const
  {
    // std::cout << accessor << std::endl;
    // assert(*item_size(accessor) == sizeof(T));
    auto count = (int)*accessor.Count();
    if (auto sparse = accessor.Sparse()) {
      m_sparseBuffer.resize(count * sizeof(T));
      auto begin = (T*)m_sparseBuffer.data();
      auto sparse_span = std::span<T>(begin, begin + count);
      if (accessor.BufferView()) {
        // non zero sparse
        // { "non zero sparse not implemented" };
        return {};
      } else {
        // zero fill
        T zero = {};
        std::fill(sparse_span.begin(), sparse_span.end(), zero);
      }
      auto sparse_count = (uint32_t)*sparse->Count();
      auto sparse_indices = *sparse->Indices();
      auto sparse_values = *sparse->Values();
      switch ((ComponentTypes)*sparse_indices.ComponentType()) {
        case ComponentTypes::UNSIGNED_BYTE:
          if (auto sparse_indices_bytes =
                GetBufferViewBytes(gltf, *sparse_indices.BufferView())) {
            auto begin = (const uint8_t*)sparse_indices_bytes->data();
            auto indices_span = std::span(begin, begin + sparse_count);
            if (auto result = GetSparseValue(gltf,
                                             indices_span,
                                             *sparse_values.BufferView(),
                                             sparse_span)) {
              return sparse_span;
            } else {
              // { result.error() };
              return {};
            }
          } else {
            // { sparse_indices_bytes.error() };
            return {};
          }

        case ComponentTypes::UNSIGNED_SHORT:
          if (auto sparse_indices_bytes =
                GetBufferViewBytes(gltf, *sparse_indices.BufferView())) {
            auto begin = (const uint16_t*)sparse_indices_bytes->data();
            auto indices_span = std::span(begin, begin + sparse_count);
            if (auto result = GetSparseValue(gltf,
                                             indices_span,
                                             *sparse_values.BufferView(),
                                             sparse_span)) {

              return sparse_span;
            } else {
              // { result.error() };
              return {};
            }
          } else {
            // { sparse_indices_bytes.error() };
            return {};
          }
        case ComponentTypes::UNSIGNED_INT:
          if (auto sparse_indices_bytes =
                GetBufferViewBytes(gltf, *sparse_indices.BufferView())) {
            auto begin = (const uint32_t*)sparse_indices_bytes->data();
            auto indices_span = std::span(begin, begin + sparse_count);
            if (auto result = GetSparseValue(gltf,
                                             indices_span,
                                             *sparse_values.BufferView(),
                                             sparse_span)) {
              return sparse_span;
            } else {
              // { result.error() };
              return {};
            }
          } else {
            // { sparse_indices_bytes.error() };
            return {};
          }
        default: {
          // { "sparse.indices: unknown" };
          return {};
        }
      }
      throw std::runtime_error("not implemented");
    } else if (auto bufferView = accessor.BufferView()) {
      if (auto span = GetBufferViewBytes(gltf, *bufferView)) {
        int offset = value_or<uint32_t>(accessor.ByteOffset());
        return std::span<const T>((const T*)(span->data() + offset), count);

      } else {
        // { "invalid bufferView" };
        return {};
      }
    } else {
      // { "sparse nor bufferView" };
      return {};
    }
  }

  template<typename T>
    std::optional <
    std::span<const T> GetAccessorBytes(const Root& gltf,
                                        int accessor_index) const
  {
    return GetAccessorBytes<T>(gltf, gltf.Accessors[accessor_index]);
  }
};

} // namespace
