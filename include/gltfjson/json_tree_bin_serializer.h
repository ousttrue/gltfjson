#pragma once
#include "bin.h"
#include "bin_writer.h"
#include "json_tree.h"
#include <functional>
#include <span>
#include <stdint.h>
#include <vector>

namespace gltfjson {
namespace tree {

using GetReplaceBytes = std::function<std::span<const uint8_t>(uint32_t)>;

class BinSerializer
{
  Root m_root;
  Bin& m_bin;
  BinWriter m_writer;

  NodePtr m_bufferViews;
  NodePtr m_accessors;
  NodePtr m_images;

public:
  BinSerializer(const NodePtr& json, Bin& bin)
    : m_root(json)
    , m_bin(bin)
  {
    m_bufferViews = std::make_shared<Node>(ArrayValue{});
    m_accessors = std::make_shared<Node>(ArrayValue{});
    m_images = std::make_shared<Node>(ArrayValue{});
  }

  std::vector<uint8_t>& Serialize(const GetReplaceBytes& replaceImages,
                                  const GetReplaceBytes& replaceAccessors)
  {
    SerializeImages(replaceImages);
    SerializeAccessors(replaceAccessors);

    auto& o = *m_root.m_json->Object();
    o[u8"bufferViews"] = m_bufferViews;
    o[u8"images"] = m_images;
    o[u8"accessors"] = m_accessors;

    return m_writer.m_buffer;
  }

  uint32_t PushBufferView(uint32_t srcId, uint32_t offset, uint32_t length)
  {
    auto bufferViewId = m_bufferViews->Size();
    auto bufferView = m_bufferViews->Add(ObjectValue{});
    m_root.BufferViews[srcId].m_json->CopyTo(bufferView);
    bufferView->Add(u8"byteOffset", (float)offset);
    bufferView->Add(u8"byteLength", (float)length);
    return bufferViewId;
  }

  void SerializeImages(const GetReplaceBytes& replaceImages)
  {
    for (int i = 0; i < m_root.Images.size(); ++i) {
      auto image = m_root.Images[i];
      std::span<const uint8_t> span;
      if (replaceImages) {
        span = replaceImages(i);
      }
      if (span.empty()) {
        // use old
        if (auto image_span = m_bin.GetImageBytes(m_root, i)) {
          span = *image_span;
        } else {
          throw std::runtime_error(image_span.error());
        }
      }
      // push bin
      auto [offset, length] = m_writer.PushBufferView(span);
      // push bufferview
      auto bufferViewId = PushBufferView(*image.BufferViewId(), offset, length);
      // push image
      auto new_image = m_images->Add(ObjectValue{});
      image.m_json->CopyTo(new_image);
      new_image->Get(u8"bufferView")->Set((float)bufferViewId);
    }
  }

  void SerializeAccessors(const GetReplaceBytes& replaceAccessors)
  {
    for (int i = 0; i < m_root.Accessors.size(); ++i) {
      auto accessor = m_root.Accessors[i];
      std::span<const uint8_t> span;
      if (replaceAccessors) {
        span = replaceAccessors(i);
      }
      if (span.empty()) {
        // use old
        if (auto block = m_bin.GetAccessorBlock(m_root, i)) {
          span = block->Span;
        } else {
          throw std::runtime_error(block.error());
        }
      }
      // push bin
      auto [offset, length] = m_writer.PushBufferView(span);
      // push bufferview
      auto bufferViewId =
        PushBufferView(*accessor.BufferViewId(), offset, length);
      // push accessor
      auto new_accessor = m_accessors->Add(ObjectValue{});
      accessor.m_json->CopyTo(new_accessor);
      new_accessor->Get(u8"bufferView")->Set((float)bufferViewId);
    }
  }
};

} // namespace
} // namespace
