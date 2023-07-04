#pragma once
#include "base64.h"
#include "directory.h"
#include "gltf_typing.h"
#include <algorithm>
#include <expected>
#include <filesystem>
#include <iostream>
#include <span>
#include <stdint.h>
#include <string_view>
#include <unordered_map>

namespace gltfjson {

struct MemoryBlock
{
  // Accessor ItemSize(type x element)
  uint32_t ItemSize;
  uint32_t ItemCount;
  uint32_t RequiredSize() const { return ItemSize * ItemCount; }
  std::span<const uint8_t> Span;
  // BufferView stride
  uint32_t Stride;
  void SetSpan(std::span<const uint8_t> span,
               uint32_t offset,
               const float* stride = nullptr)
  {
    if (stride) {
      Stride = (uint32_t)*stride;
    }
    Span = span.subspan(offset);
    // assert(Span.size() == Count * Stride);
  }
};

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

    int buffer_index = *buffer_view.BufferId();
    auto buffer = gltf.Buffers[buffer_index];
    auto uri = buffer.UriString();
    if (uri.size()) {
      // external file
      if (auto bytes = Dir->GetBuffer(uri)) {
        return bytes->subspan(
          (uint32_t)gltfjson::deref_or(buffer_view.ByteOffset(), 0),
          (uint32_t)*buffer_view.ByteLength());
      } else {
        return bytes;
      }
    } else {
      // glb
      return Bytes.subspan(
        (uint32_t)gltfjson::deref_or(buffer_view.ByteOffset(), 0),
        (uint32_t)*buffer_view.ByteLength());
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
  std::expected<MemoryBlock, std::string> GetAccessorBlock(
    const Root& gltf,
    int accessor_index) const
  {
    auto accessor = gltf.Accessors[accessor_index];
    MemoryBlock block{
      .ItemSize = accessor.Stride(),
      .ItemCount = (uint32_t)*accessor.Count(),
      .Stride = accessor.Stride(),
    };
    if (auto sparse = accessor.Sparse()) {
      m_sparseBuffer.resize(block.RequiredSize());
      auto begin = m_sparseBuffer.data();
      auto sparse_span =
        std::span<uint8_t>(begin, begin + block.RequiredSize());
      if (accessor.BufferViewId()) {
        // non zero sparse
        return std::unexpected{ "non zero sparse not implemented" };
      } else {
        // zero fill
        std::fill(sparse_span.begin(), sparse_span.end(), 0);
      }
      auto sparse_count = (uint32_t)*sparse->Count();
      auto sparse_indices = *sparse->Indices();
      auto sparse_values = *sparse->Values();
      switch ((gltfjson::ComponentTypes)*sparse_indices.ComponentType()) {
        case gltfjson::ComponentTypes::UNSIGNED_BYTE:
          if (auto sparse_indices_bytes =
                GetBufferViewBytes(gltf, *sparse_indices.BufferViewId())) {
            auto begin = (const uint8_t*)sparse_indices_bytes->data();
            auto indices_span = std::span(begin, begin + sparse_count);
            if (auto result = GetSparseValue(gltf,
                                             indices_span,
                                             *sparse_values.BufferViewId(),
                                             sparse_span)) {
              // return sparse_span;
              block.SetSpan(sparse_span, 0);
              return block;
            } else {
              return std::unexpected{ result.error() };
            }
          } else {
            return std::unexpected{ sparse_indices_bytes.error() };
          }

        case gltfjson::ComponentTypes::UNSIGNED_SHORT:
          if (auto sparse_indices_bytes =
                GetBufferViewBytes(gltf, *sparse_indices.BufferViewId())) {
            auto begin = (const uint16_t*)sparse_indices_bytes->data();
            auto indices_span = std::span(begin, begin + sparse_count);
            if (auto result = GetSparseValue(gltf,
                                             indices_span,
                                             *sparse_values.BufferViewId(),
                                             sparse_span)) {

              block.SetSpan(sparse_span, 0);
              return block;
            } else {
              return std::unexpected{ result.error() };
            }
          } else {
            return std::unexpected{ sparse_indices_bytes.error() };
          }
        case gltfjson::ComponentTypes::UNSIGNED_INT:
          if (auto sparse_indices_bytes =
                GetBufferViewBytes(gltf, *sparse_indices.BufferViewId())) {
            auto begin = (const uint32_t*)sparse_indices_bytes->data();
            auto indices_span = std::span(begin, begin + sparse_count);
            if (auto result = GetSparseValue(gltf,
                                             indices_span,
                                             *sparse_values.BufferViewId(),
                                             sparse_span)) {
              block.SetSpan(sparse_span, 0);
              return block;
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
    } else if (auto bufferViewId = accessor.BufferViewId()) {
      if (auto span = GetBufferViewBytes(gltf, *bufferViewId)) {
        auto offset = (uint32_t)gltfjson::deref_or(accessor.ByteOffset(), 0);
        auto bufferView = gltf.BufferViews[*bufferViewId];
        block.SetSpan(*span, offset, bufferView.ByteStride());
        return block;
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
    const Accessor& accessor) const
  {
    // std::cout << accessor << std::endl;
    // assert(*item_size(accessor) == sizeof(T));
    auto count = (uint32_t)*accessor.Count();
    if (auto sparse = accessor.Sparse()) {
      m_sparseBuffer.resize(count * sizeof(T));
      auto begin = (T*)m_sparseBuffer.data();
      auto sparse_span = std::span<T>(begin, begin + count);
      if (accessor.BufferViewId()) {
        // non zero sparse
        return std::unexpected{ "non zero sparse not implemented" };
      } else {
        // zero fill
        T zero = {};
        std::fill(sparse_span.begin(), sparse_span.end(), zero);
      }
      auto sparse_count = (uint32_t)*sparse->Count();
      auto sparse_indices = *sparse->Indices();
      auto sparse_values = *sparse->Values();
      switch ((gltfjson::ComponentTypes)*sparse_indices.ComponentType()) {
        case gltfjson::ComponentTypes::UNSIGNED_BYTE:
          if (auto sparse_indices_bytes =
                GetBufferViewBytes(gltf, *sparse_indices.BufferViewId())) {
            auto begin = (const uint8_t*)sparse_indices_bytes->data();
            auto indices_span = std::span(begin, begin + sparse_count);
            if (auto result = GetSparseValue(gltf,
                                             indices_span,
                                             *sparse_values.BufferViewId(),
                                             sparse_span)) {
              return sparse_span;
            } else {
              return std::unexpected{ result.error() };
            }
          } else {
            return std::unexpected{ sparse_indices_bytes.error() };
          }

        case gltfjson::ComponentTypes::UNSIGNED_SHORT:
          if (auto sparse_indices_bytes =
                GetBufferViewBytes(gltf, *sparse_indices.BufferViewId())) {
            auto begin = (const uint16_t*)sparse_indices_bytes->data();
            auto indices_span = std::span(begin, begin + sparse_count);
            if (auto result = GetSparseValue(gltf,
                                             indices_span,
                                             *sparse_values.BufferViewId(),
                                             sparse_span)) {

              return sparse_span;
            } else {
              return std::unexpected{ result.error() };
            }
          } else {
            return std::unexpected{ sparse_indices_bytes.error() };
          }
        case gltfjson::ComponentTypes::UNSIGNED_INT:
          if (auto sparse_indices_bytes =
                GetBufferViewBytes(gltf, *sparse_indices.BufferViewId())) {
            auto begin = (const uint32_t*)sparse_indices_bytes->data();
            auto indices_span = std::span(begin, begin + sparse_count);
            if (auto result = GetSparseValue(gltf,
                                             indices_span,
                                             *sparse_values.BufferViewId(),
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
    } else if (auto bufferView = accessor.BufferViewId()) {
      if (auto span = GetBufferViewBytes(gltf, *bufferView)) {
        auto offset = (uint32_t)gltfjson::deref_or(accessor.ByteOffset(), 0);
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

} // namespace
