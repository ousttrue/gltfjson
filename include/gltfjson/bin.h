#pragma once
#include "base64.h"
#include "directory.h"
#include "gltf_typing.h"
#include <algorithm>
#include <filesystem>
#include <iostream>
#include <optional>
#include <span>
#include <stdint.h>
#include <string_view>
#include <unordered_map>

namespace gltfjson {

struct MemoryBlock
{
  // Accessor ItemSize
  // (ComponentType("float", ...) x Type("SCALAR", "VEC3", ...))
  uint32_t ItemSize;

  // Accessor.Count
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
  std::vector<uint8_t> EvalStride()
  {
    auto span = Span.subspan(0, ItemSize * ItemCount);
    std::vector<uint8_t> buf;
    if (Stride) {
      auto p = span.data();
      for (int i = 0; i < ItemCount; ++i, p += Stride) {
        for (int i = 0; i < ItemSize; ++i) {
          buf.push_back(p[i]);
        }
      }
    } else {
      buf.assign(span.begin(), span.end());
    }
    return buf;
  }
};

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

    auto offset = gltfjson::deref_or(buffer_view.ByteOffset(), 0);
    auto length = buffer_view.ByteLength();

    int buffer_index = *buffer_view.BufferId();
    auto buffer = gltf.Buffers[buffer_index];
    auto uri = buffer.UriString();
    if (uri.size()) {
      // external file
      if (auto bytes = Dir->GetBuffer(uri)) {
        return bytes->subspan((uint32_t)offset, (uint32_t)*length);
      } else {
        // error
        return {};
      }
    } else {
      // glb
      assert(buffer_index == 0);
      return Bytes.subspan((uint32_t)offset, (uint32_t)*length);
    }
  }

  // fill dst
  template<typename T>
  bool GetSparseValue(const Root& gltf,
                      std::span<const T> indices,
                      uint32_t buffer_view_index,
                      std::span<uint8_t> dst,
                      uint32_t stride) const
  {
    if (auto src = GetBufferViewBytes(gltf, buffer_view_index)) {
      assert(indices.size() == src->size() / stride);
      auto pDst = dst.data();
      for (int i = 0; i < indices.size(); ++i, pDst += stride) {
        auto index = indices[i];
        auto pSrc = src->data() + (index * stride);
        // dst[i] = p[];
        memcpy(pDst, pSrc, stride);
      }
      return true;
    } else {
      // { span.error() };
      return false;
    }
  }

  std::optional<std::span<const uint8_t>> GetImageBytes(const Root& gltf,
                                                        int image_index) const
  {
    auto image = gltf.Images[image_index];
    if (auto bufferViewId = image.BufferViewId()) {
      if (auto span = GetBufferViewBytes(gltf, *bufferViewId)) {
        return *span;
      } else {
        // { "invalid bufferView" };
        return {};
      }
    } else {
      // { "no bufferview" };
      return {};
    }
  }

  mutable std::vector<uint8_t> m_sparseBuffer;
  std::optional<MemoryBlock> GetAccessorBlock(const Root& gltf,
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
        // { "non zero sparse not implemented" };
        return {};
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
                                             sparse_span,
                                             accessor.Stride())) {
              // return sparse_span;
              block.SetSpan(sparse_span, 0);
              return block;
            } else {
              // { result.error() };
              return {};
            }
          } else {
            // { sparse_indices_bytes.error() };
            return {};
          }

        case gltfjson::ComponentTypes::UNSIGNED_SHORT:
          if (auto sparse_indices_bytes =
                GetBufferViewBytes(gltf, *sparse_indices.BufferViewId())) {
            auto begin = (const uint16_t*)sparse_indices_bytes->data();
            auto indices_span = std::span(begin, begin + sparse_count);
            if (auto result = GetSparseValue(gltf,
                                             indices_span,
                                             *sparse_values.BufferViewId(),
                                             sparse_span,
                                             accessor.Stride())) {

              block.SetSpan(sparse_span, 0);
              return block;
            } else {
              // { result.error() };
              return {};
            }
          } else {
            // { sparse_indices_bytes.error() };
            return {};
          }
        case gltfjson::ComponentTypes::UNSIGNED_INT:
          if (auto sparse_indices_bytes =
                GetBufferViewBytes(gltf, *sparse_indices.BufferViewId())) {
            auto begin = (const uint32_t*)sparse_indices_bytes->data();
            auto indices_span = std::span(begin, begin + sparse_count);
            if (auto result = GetSparseValue(gltf,
                                             indices_span,
                                             *sparse_values.BufferViewId(),
                                             sparse_span,
                                             accessor.Stride())) {
              block.SetSpan(sparse_span, 0);
              return block;
            } else {
              // { result.error() };
              return {};
            }
          } else {
            // { sparse_indices_bytes.error() };
            return {};
          }
        default:
          // { "sparse.indices: unknown" };
          return {};
      }
      throw std::runtime_error("not implemented");
    } else if (auto bufferViewId = accessor.BufferViewId()) {
      if (auto span = GetBufferViewBytes(gltf, *bufferViewId)) {
        auto offset = (uint32_t)gltfjson::deref_or(accessor.ByteOffset(), 0);
        auto bufferView = gltf.BufferViews[*bufferViewId];
        block.SetSpan(*span, offset, bufferView.ByteStride());
        return block;
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
  std::optional<std::span<const T>> GetAccessorBytes(
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
      switch ((gltfjson::ComponentTypes)*sparse_indices.ComponentType()) {
        case gltfjson::ComponentTypes::UNSIGNED_BYTE:
          if (auto sparse_indices_bytes =
                GetBufferViewBytes(gltf, *sparse_indices.BufferViewId())) {
            auto begin = (const uint8_t*)sparse_indices_bytes->data();
            auto indices_span = std::span(begin, begin + sparse_count);
            if (auto result = GetSparseValue(
                  gltf,
                  indices_span,
                  *sparse_values.BufferViewId(),
                  { (uint8_t*)sparse_span.data(),
                    (uint8_t*)(sparse_span.data() + sparse_span.size()) },
                  accessor.Stride())) {
              return sparse_span;
            } else {
              // { result.error() };
              return {};
            }
          } else {
            // { sparse_indices_bytes.error() };
            return {};
          }

        case gltfjson::ComponentTypes::UNSIGNED_SHORT:
          if (auto sparse_indices_bytes =
                GetBufferViewBytes(gltf, *sparse_indices.BufferViewId())) {
            auto begin = (const uint16_t*)sparse_indices_bytes->data();
            auto indices_span = std::span(begin, begin + sparse_count);
            if (auto result = GetSparseValue(
                  gltf,
                  indices_span,
                  *sparse_values.BufferViewId(),
                  { (uint8_t*)sparse_span.data(),
                    (uint8_t*)(sparse_span.data() + sparse_span.size()) },
                  accessor.Stride())) {

              return sparse_span;
            } else {
              // { result.error() };
              return {};
            }
          } else {
            // { sparse_indices_bytes.error() };
            return {};
          }
        case gltfjson::ComponentTypes::UNSIGNED_INT:
          if (auto sparse_indices_bytes =
                GetBufferViewBytes(gltf, *sparse_indices.BufferViewId())) {
            auto begin = (const uint32_t*)sparse_indices_bytes->data();
            auto indices_span = std::span(begin, begin + sparse_count);
            if (auto result = GetSparseValue(
                  gltf,
                  indices_span,
                  *sparse_values.BufferViewId(),
                  { (uint8_t*)sparse_span.data(),
                    (uint8_t*)(sparse_span.data() + sparse_span.size()) },
                  accessor.Stride())) {
              return sparse_span;
            } else {
              // { result.error() };
              return {};
            }
          } else {
            // { sparse_indices_bytes.error() };
            return {};
          }
        default:
          // { "sparse.indices: unknown" };
          return {};
      }
      throw std::runtime_error("not implemented");
    } else if (auto bufferView = accessor.BufferViewId()) {
      if (auto span = GetBufferViewBytes(gltf, *bufferView)) {
        auto offset = (uint32_t)gltfjson::deref_or(accessor.ByteOffset(), 0);
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
  std::optional<std::span<const T>> GetAccessorBytes(const Root& gltf,
                                                     int accessor_index) const
  {
    return GetAccessorBytes<T>(gltf, gltf.Accessors[accessor_index]);
  }
};

} // namespace
