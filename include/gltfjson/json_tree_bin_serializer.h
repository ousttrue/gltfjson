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

public:
  BinSerializer(const NodePtr& json, Bin& bin)
    : m_root(json)
    , m_bin(bin)
  {
  }

  std::vector<uint8_t> Serialize(const GetReplaceBytes& replaceImages,
                                 const GetReplaceBytes& replaceAccessors)
  {
    auto bufferViews = m_root.m_json->Get(u8"bufferViews");
    m_root.m_json->Remove(u8"bufferViews");
    SerializeImages(replaceImages);
    SerializeAccessors(replaceAccessors);
    return m_writer.m_buffer;
  }

  uint32_t PushBufferView(uint32_t offset, uint32_t length)
  {
    auto bufferViews = m_root.m_json->Get(u8"bufferViews");
    if (!bufferViews) {
      bufferViews = m_root.m_json->Add(u8"bufferViews", ArrayValue{});
    }
    auto bufferViewId = bufferViews->Size();
    auto bufferView = bufferViews->Add(ObjectValue{});
    bufferView->Add(u8"bytesOffset", (float)offset);
    bufferView->Add(u8"bytesLength", (float)length);
    return bufferViewId;
  }

  void SerializeImages(const GetReplaceBytes& replaceImages)
  {
    auto images = m_root.m_json->Get(u8"images");
    if (images) {
      m_root.m_json->Remove(u8"images");
    } else {
      images = std::make_shared<Node>();
      images->Set(ArrayValue{});
    }
    auto& src = *images->Array();
    auto dst = m_root.m_json->Add(u8"images", ArrayValue{});
    for (int i = 0; i < src.size(); ++i) {
      std::span<const uint8_t> bytes;
      if (replaceImages) {
        bytes = replaceImages(i);
      }
      if (bytes.size()) {
        // use new
      } else {
        // use old
        auto image = src[i];
      }
      // push bin
      auto [offset, length] = m_writer.PushBufferView(bytes);
      // push bufferview
      auto bufferViewId = PushBufferView(offset, length);
      // push image
      auto new_image = dst->Add(ObjectValue{});
      new_image->Add(u8"bufferView", (float)bufferViewId);
    }
  }

  void SerializeAccessors(const GetReplaceBytes& replaceAccessors)
  {
    auto accessors = m_root.m_json->Get(u8"accessors");
    if (accessors) {
      m_root.m_json->Remove(u8"accessors");
    } else {
      accessors = std::make_shared<Node>();
      accessors->Set(ArrayValue{});
    }
    auto& src = *accessors->Array();
    auto dst = m_root.m_json->Add(u8"accessors", ArrayValue{});
    for (int i = 0; i < src.size(); ++i) {
      std::span<const uint8_t> span;
      if (replaceAccessors) {
        span = replaceAccessors(i);
      }
      if (span.size()) {
        // use new
      } else {
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
      auto bufferViewId = PushBufferView(offset, length);
      // push accessor
      auto new_accessor = dst->Add(ObjectValue{});
      new_accessor->Add(u8"bufferView", (float)bufferViewId);
    }
  }
};

} // namespace
} // namespace
