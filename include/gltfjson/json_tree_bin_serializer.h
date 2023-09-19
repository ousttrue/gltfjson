#pragma once
#include "bin.h"
#include "bin_writer.h"
#include "gltf_typing.h"
#include "gltfjson/json_tree.h"
#include "json_tree.h"
#include <functional>
#include <memory>
#include <span>
#include <stdint.h>
#include <vector>

namespace gltfjson {

struct Float16
{
  float _11, _12, _13, _14;
  float _21, _22, _23, _24;
  float _31, _32, _33, _34;
  float _41, _42, _43, _44;
};
struct Float4
{
  float X;
  float Y;
  float Z;
  float W;
};
struct Float3
{
  float X;
  float Y;
  float Z;
};
struct Float2
{
  float X;
  float Y;
};
struct UShort4
{
  uint16_t X;
  uint16_t Y;
  uint16_t Z;
  uint16_t W;
};

namespace tree {

using GetReplaceBytes = std::function<std::span<const uint8_t>(uint32_t)>;

struct BinSerializer
{
  Root& m_root;
  Bin& m_bin;
  BinWriter m_writer;

  NodePtr m_bufferViews;
  NodePtr m_accessors;
  NodePtr m_images;

public:
  BinSerializer(Root& root, Bin& bin, std::vector<uint8_t>& buf)
    : m_root(root)
    , m_bin(bin)
    , m_writer(buf)
  {
    m_bufferViews = NewNode(ArrayValue{});
    m_accessors = NewNode(ArrayValue{});
    m_images = NewNode(ArrayValue{});
  }

  void Serialize(const GetReplaceBytes& replaceImages,
                 const GetReplaceBytes& replaceAccessors)
  {
    SerializeImages(replaceImages);
    SerializeAccessors(replaceAccessors);

    auto o = std::dynamic_pointer_cast<ObjectNode>(m_root.m_json);
    o->Value[u8"bufferViews"] = m_bufferViews;
    o->Value[u8"images"] = m_images;
    o->Value[u8"accessors"] = m_accessors;
    m_root = Root(m_root.m_json);
  }

  uint32_t PushBufferView(uint32_t offset, uint32_t length)
  {
    auto bufferViewId = m_bufferViews->Size();
    auto bufferView = m_bufferViews->Add(ObjectValue{});
    bufferView->SetProperty(u8"buffer", 0.0f);
    bufferView->SetProperty(u8"byteOffset", (float)offset);
    bufferView->SetProperty(u8"byteLength", (float)length);
    return bufferViewId;
  }

  uint32_t PushAccessorFloat2(std::span<const Float2> values)
  {
    auto [offset, length] = m_writer.PushBufferView(values);
    auto bufferView = PushBufferView(offset, length);

    auto index = m_root.Accessors.size();
    auto gltfAccessor = m_root.Accessors.m_json->Add(ObjectValue{});
    gltfAccessor->SetProperty(u8"bufferView", (float)bufferView);
    gltfAccessor->SetProperty(u8"type", u8"VEC2");
    gltfAccessor->SetProperty(u8"componentType", (float)ComponentTypes::FLOAT);
    gltfAccessor->SetProperty(u8"count", (float)values.size());
    return index;
  }

  uint32_t PushAccessorFloat3(std::span<const Float3> values)
  {
    auto [offset, length] = m_writer.PushBufferView(values);
    auto bufferView = PushBufferView(offset, length);

    auto index = m_root.Accessors.size();
    auto gltfAccessor = m_root.Accessors.m_json->Add(ObjectValue{});
    gltfAccessor->SetProperty(u8"bufferView", (float)bufferView);
    gltfAccessor->SetProperty(u8"type", u8"VEC3");
    gltfAccessor->SetProperty(u8"componentType", (float)ComponentTypes::FLOAT);
    gltfAccessor->SetProperty(u8"count", (float)values.size());
    return index;
  }

  uint32_t PushAccessorFloat4(std::span<const Float4> values)
  {
    auto [offset, length] = m_writer.PushBufferView(values);
    auto bufferView = PushBufferView(offset, length);

    auto index = m_root.Accessors.size();
    auto gltfAccessor = m_root.Accessors.m_json->Add(ObjectValue{});
    gltfAccessor->SetProperty(u8"bufferView", (float)bufferView);
    gltfAccessor->SetProperty(u8"type", u8"VEC4");
    gltfAccessor->SetProperty(u8"componentType", (float)ComponentTypes::FLOAT);
    gltfAccessor->SetProperty(u8"count", (float)values.size());
    return index;
  }

  uint32_t PushAccessorUShort4(std::span<const UShort4> values)
  {
    auto [offset, length] = m_writer.PushBufferView(values);
    auto bufferView = PushBufferView(offset, length);

    auto index = m_root.Accessors.size();
    auto gltfAccessor = m_root.Accessors.m_json->Add(ObjectValue{});
    gltfAccessor->SetProperty(u8"bufferView", (float)bufferView);
    gltfAccessor->SetProperty(u8"type", u8"VEC4");
    gltfAccessor->SetProperty(u8"componentType",
                              (float)ComponentTypes::UNSIGNED_SHORT);
    gltfAccessor->SetProperty(u8"count", (float)values.size());
    return index;
  }

  uint32_t PushIndices(std::span<const uint32_t> values)
  {
    auto [offset, length] = m_writer.PushBufferView(values);
    auto bufferView = PushBufferView(offset, length);

    auto index = m_root.Accessors.size();
    auto gltfAccessor = m_root.Accessors.m_json->Add(ObjectValue{});
    gltfAccessor->SetProperty(u8"bufferView", (float)bufferView);
    gltfAccessor->SetProperty(u8"type", u8"SCALAR");
    gltfAccessor->SetProperty(u8"componentType",
                              (float)ComponentTypes::UNSIGNED_INT);
    gltfAccessor->SetProperty(u8"count", (float)values.size());
    return index;
  }

  uint32_t PushAccessorFloat16(std::span<const Float16> values)
  {
    auto [offset, length] = m_writer.PushBufferView(values);
    auto bufferView = PushBufferView(offset, length);

    auto index = m_root.Accessors.size();
    auto gltfAccessor = m_root.Accessors.m_json->Add(ObjectValue{});
    gltfAccessor->SetProperty(u8"bufferView", (float)bufferView);
    gltfAccessor->SetProperty(u8"type", u8"MAT4");
    gltfAccessor->SetProperty(u8"componentType", (float)ComponentTypes::FLOAT);
    gltfAccessor->SetProperty(u8"count", (float)values.size());
    return index;
  }

  void PushPrim(const MeshPrimitive& prim,
                uint32_t materialIndex,
                std::span<const Float3> positions,
                std::span<const Float3> normal,
                std::span<const Float2> uv,
                std::span<const uint32_t> indices,
                std::span<const UShort4> joints,
                std::span<const Float4> weights)
  {
    // auto prim = mesh.Primitives.m_json->Add(ObjectValue{});
    auto attr = prim.m_json->SetProperty(u8"attributes", ObjectValue{});
    attr->SetProperty(u8"POSITION", (float)PushAccessorFloat3(positions));
    attr->SetProperty(u8"NORMAL", (float)PushAccessorFloat3(normal));
    attr->SetProperty(u8"TEXCOORD_0", (float)PushAccessorFloat2(uv));
    if (weights.size() == positions.size() &&
        joints.size() == positions.size()) {
      attr->SetProperty(u8"JOINTS_0", (float)PushAccessorUShort4(joints));
      attr->SetProperty(u8"WEIGHTS_0", (float)PushAccessorFloat4(weights));
    }
    prim.m_json->SetProperty(u8"indices", (float)PushIndices(indices));
    prim.m_json->SetProperty(u8"material", (float)materialIndex);
    prim.m_json->SetProperty(u8"mode", 4.0f);
  }

  void PushMorph(const MeshPrimitive& prim,
                 std::span<const Float3> positions,
                 std::span<const Float3> normal,
                 std::span<const Float2> uv)
  {
    auto targets = prim.m_json->Get(u8"targets");
    if (!targets) {
      targets =
        prim.m_json->SetProperty(u8"targets", gltfjson::tree::ArrayValue{});
    }
    auto target = targets->Add(gltfjson::tree::ObjectValue{});
    target->SetProperty(u8"POSITION", (float)PushAccessorFloat3(positions));
    target->SetProperty(u8"NORMAL", (float)PushAccessorFloat3(normal));
    target->SetProperty(u8"TEXCOORD_0", (float)PushAccessorFloat2(uv));
  }

  void PushMorphEmpty(const MeshPrimitive& prim, uint32_t vertex_count)
  {
    auto targets = prim.m_json->Get(u8"targets");
    if (!targets) {
      targets =
        prim.m_json->SetProperty(u8"targets", gltfjson::tree::ArrayValue{});
    }
    auto target = targets->Add(gltfjson::tree::ObjectValue{});
    std::vector<Float3> positions(vertex_count, Float3{ 0, 0, 0 });
    target->SetProperty(u8"POSITION", (float)PushAccessorFloat3(positions));
    target->SetProperty(u8"NORMAL", (float)PushAccessorFloat3(positions));
    std::vector<Float2> uv(vertex_count, Float2{ 0, 0 });
    target->SetProperty(u8"TEXCOORD_0", (float)PushAccessorFloat2(uv));
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
          throw std::runtime_error("GetImageBytes");
        }
      }
      // push bin
      auto [offset, length] = m_writer.PushBufferView(span);
      // push bufferview
      auto bufferViewId = PushBufferView(offset, length);
      // push image
      auto new_image = image.m_json->Clone();
      new_image->SetProperty(u8"bufferView", (float)bufferViewId);
      m_images->Add(new_image);
    }
  }

  void PushSkin(const Skin& skin, std::span<const Float16> values)
  {
    skin.m_json->SetProperty(u8"inverseBindMatrices",
                             (float)PushAccessorFloat16(values));
  }

  std::vector<uint8_t> m_buf;
  void SerializeAccessors(const GetReplaceBytes& replaceAccessors)
  {
    for (int i = 0; i < m_root.Accessors.size(); ++i) {
      m_buf.clear();
      auto accessor = m_root.Accessors[i];
      if (replaceAccessors) {
        auto span = replaceAccessors(i);
        m_buf.assign(span.begin(), span.end());
      }
      if (m_buf.empty()) {
        // use old
        if (auto block = m_bin.GetAccessorBlock(m_root, i)) {
          m_buf = block->EvalStride();
        } else {
          throw std::runtime_error("GetAccessorBlock");
        }
      }
      // push bin
      auto [offset, length] = m_writer.PushBufferView(m_buf);
      // push bufferview
      auto bufferViewId = PushBufferView(offset, length);
      // push accessor
      auto new_accessor = accessor.m_json->Clone();
      new_accessor->SetProperty(u8"bufferView", (float)bufferViewId);
      m_accessors->Add(new_accessor);
    }
  }
};

} // namespace
} // namespace
