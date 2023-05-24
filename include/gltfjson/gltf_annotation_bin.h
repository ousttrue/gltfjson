#pragma once
#include "gltf_annotation.h"
#include "directory.h"

namespace gltfjson {
namespace annotation {

struct Bin
{
  std::shared_ptr<Directory> Dir;
  std::span<const uint8_t> Bytes;

  std::expected<std::span<const uint8_t>, std::string> GetBufferViewBytes(
    const Root& gltf,
    int buffer_view_index) const
  {
    if (buffer_view_index < 0 || buffer_view_index >= gltf.BufferViews.size()) {
      return std::unexpected{ "buffer_view_index is out of range" };
    }

    auto buffer_view = gltf.BufferViews[buffer_view_index];
    // std::cout << buffer_view << std::endl;

    int buffer_index = *buffer_view.Buffer();
    auto buffer = gltf.Buffers[buffer_index];
    auto uri = buffer.Uri().value_or(u8"");
    if (uri.size()) {
      // external file
      if (auto bytes = Dir->GetBuffer(uri)) {
        return bytes->subspan(buffer_view.ByteOffset().value_or(0),
                              *buffer_view.ByteLength());
      } else {
        return bytes;
      }
    } else {
      // glb
      return Bytes.subspan(buffer_view.ByteOffset().value_or(0),
                           *buffer_view.ByteLength());
    }
  }

  template<typename S, typename T>
  std::expected<bool, std::string> GetSparseValue(const Root& gltf,
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
      return std::unexpected{ span.error() };
    }
  }

  mutable std::vector<uint8_t> m_sparseBuffer;
  template<typename T>
  std::expected<std::span<const T>, std::string> GetAccessorBytes(
    const Root& gltf,
    const Accessor& accessor) const
  {
    // std::cout << accessor << std::endl;
    // assert(*item_size(accessor) == sizeof(T));
    int count = *accessor.Count();
    if (auto sparse = accessor.Sparse()) {
      m_sparseBuffer.resize(count * sizeof(T));
      auto begin = (T*)m_sparseBuffer.data();
      auto sparse_span = std::span<T>(begin, begin + count);
      if (accessor.BufferView()) {
        // non zero sparse
        return std::unexpected{ "non zero sparse not implemented" };
      } else {
        // zero fill
        T zero = {};
        std::fill(sparse_span.begin(), sparse_span.end(), zero);
      }
      int sparse_count = *sparse->Count();
      auto sparse_indices = *sparse->Indices();
      auto sparse_values = *sparse->Values();
      switch (*sparse_indices.ComponentType()) {
        case gltfjson::format::ComponentTypes::UNSIGNED_BYTE:
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
              return std::unexpected{ result.error() };
            }
          } else {
            return std::unexpected{ sparse_indices_bytes.error() };
          }

        case gltfjson::format::ComponentTypes::UNSIGNED_SHORT:
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
              return std::unexpected{ result.error() };
            }
          } else {
            return std::unexpected{ sparse_indices_bytes.error() };
          }
        case gltfjson::format::ComponentTypes::UNSIGNED_INT:
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
              return std::unexpected{ result.error() };
            }
          } else {
            return std::unexpected{ sparse_indices_bytes.error() };
          }
        default:
          return std::unexpected{ "sparse.indices: unknown" };
      }
      throw std::runtime_error("not implemented");
    } else if (auto bufferView = accessor.BufferView()) {
      if (auto span = GetBufferViewBytes(gltf, *bufferView)) {
        int offset = accessor.ByteOffset().value_or(0);
        return std::span<const T>((const T*)(span->data() + offset), count);

      } else {
        return std::unexpected{ "invalid bufferView" };
      }
    } else {
      return std::unexpected{ "sparse nor bufferView" };
    }
  }

  template<typename T>
  std::expected<std::span<const T>, std::string> GetAccessorBytes(
    const Root& gltf,
    int accessor_index) const
  {
    return GetAccessorBytes<T>(gltf, gltf.Accessors[accessor_index]);
  }
};

}
}