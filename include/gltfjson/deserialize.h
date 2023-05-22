#pragma once
#include "gltf.h"
#include "json_parser.h"
#include <iostream>
#include <optional>

namespace gltfjson {
namespace format {

template<typename T>
inline void
DeserializeNumberVector(const Value& value, std::vector<T>& dst)
{
  if (auto array = value.Array()) {
    for (auto& item : *array) {
      dst.push_back(*item.Number<T>());
    }
  }
}

template<typename T, size_t N>
inline std::optional<std::array<T, N>>
DeserializeNumberArray(const Value& value)
{
  if (auto array = value.Array()) {
    if (array->Size() == N) {
      int i = 0;
      std::array<T, N> dst;
      for (auto item : *array) {
        dst[i++] = *item.Number<T>();
      }
      return dst;
    }
  }

  return std::nullopt;
}

inline void
DeserializeString(const Value& value, std::u8string& dst)
{
  if (auto str = value.U8String()) {
    dst = std::u8string(str->data(), str->data() + str->size());
  }
}

inline void
Deserialize(const Value& value, std::list<Extension>& dst)
{
  if (auto obj = value.Object()) {
    for (auto kv : *obj) {
      auto key = kv.Key->U8String();
      dst.push_back({
        .Name = { key->data(), key->size() },
        .Value = { kv.Value->Range.data(), kv.Value->Range.size() },
      });
    }
  }
}

inline void
Deserialize(const Value& value, std::list<Extra>& dst)
{
  if (auto obj = value.Object()) {
    for (auto kv : *obj) {
      auto key = kv.Key->U8String();
      dst.push_back({
        .Name = { key->data(), key->size() },
        .Value = { kv.Value->Range.data(), kv.Value->Range.size() },
      });
    }
  }
}

inline void
DeserializeProp(const Value& value, Property& dst)
{
  if (auto prop = value.Get("extensions")) {
    Deserialize(*prop, dst.Extensions);
  }
  if (auto prop = value.Get("extras")) {
    Deserialize(*prop, dst.Extras);
  }
}

inline void
DeserializeChildOfRootProp(const Value& value, ChildOfRootProperty& dst)
{
  if (auto prop = value.Get("name")) {
    DeserializeString(*prop, dst.Name);
  }
  DeserializeProp(value, dst);
}

inline void
Deserialize(const Value& value, Asset& dst)
{
  if (auto prop = value.Get("copyright")) {
    dst.Copyright = *prop->U8String();
  }
  if (auto prop = value.Get("generator")) {
    dst.Generator = *prop->U8String();
  }
  if (auto prop = value.Get("version")) {
    dst.Version = *prop->U8String();
  }
  if (auto prop = value.Get("minVersion")) {
    dst.MinVersion = *prop->U8String();
  }
}

// buffer/bufferview/accessor
inline void
Deserialize(const Value& buffer, Buffer& dst)
{
  DeserializeChildOfRootProp(buffer, dst);
  if (auto prop = buffer.Get(u8"uri")) {
    dst.Uri = *prop->U8String();
  }
  if (auto prop = buffer.Get(u8"byteLength")) {
    dst.ByteLength = *prop->Number<uint32_t>();
  }
}

inline void
Deserialize(const Value& bufferView, BufferView& dst)
{
  DeserializeChildOfRootProp(bufferView, dst);
  if (auto prop = bufferView.Get(u8"buffer")) {
    dst.Buffer = prop->Number<uint32_t>();
  }
  if (auto prop = bufferView.Get(u8"byteOffset")) {
    dst.ByteOffset = prop->Number<uint32_t>().value_or(0);
  }
  if (auto prop = bufferView.Get(u8"byteLength")) {
    dst.ByteLength = *prop->Number<uint32_t>();
  }
  if (auto prop = bufferView.Get(u8"byteStride")) {
    dst.ByteStride = prop->Number<uint32_t>().value_or(0);
  }
  if (auto prop = bufferView.Get(u8"target")) {
    dst.Target = static_cast<Targets>(*prop->Number<int>());
  }
}

inline void
Deserialize(const Value& sparse, SparseIndices& dst)
{
  if (auto prop = sparse.Get(u8"bufferView")) {
    dst.BufferView = prop->Number<uint32_t>();
  }
  if (auto prop = sparse.Get(u8"byteOffset")) {
    dst.ByteOffset = prop->Number<uint32_t>().value_or(0);
  }
  if (auto prop = sparse.Get(u8"componentType")) {
    dst.ComponentType = static_cast<ComponentTypes>(*prop->Number<int>());
  }
}

inline void
Deserialize(const Value& sparse, SparseValues& dst)
{
  if (auto prop = sparse.Get(u8"bufferView")) {
    dst.BufferView = prop->Number<uint32_t>();
  }
  if (auto prop = sparse.Get(u8"byteOffset")) {
    dst.ByteOffset = prop->Number<uint32_t>().value_or(0);
  }
}

inline Sparse
Deserialize(const Value& sparse)
{
  Sparse dst = {};
  if (auto prop = sparse.Get(u8"count")) {
    dst.Count = *prop->Number<uint32_t>();
  }
  if (auto prop = sparse.Get(u8"indices")) {
    Deserialize(*prop, dst.Indices);
  }
  if (auto prop = sparse.Get(u8"values")) {
    Deserialize(*prop, dst.Values);
  }
  return dst;
}

inline void
Deserialize(const Value& accessor, Accessor& dst)
{
  DeserializeChildOfRootProp(accessor, dst);
  if (auto prop = accessor.Get(u8"bufferView")) {
    dst.BufferView = prop->Number<int>();
  }
  if (auto prop = accessor.Get(u8"byteOffset")) {
    dst.ByteOffset = prop->Number<uint32_t>().value_or(0);
  }
  if (auto prop = accessor.Get(u8"componentType")) {
    dst.ComponentType = static_cast<ComponentTypes>(*prop->Number<int>());
  }
  if (auto prop = accessor.Get(u8"normalized")) {
    dst.Normalized = prop->IsTrue();
  }
  if (auto prop = accessor.Get(u8"count")) {
    dst.Count = *prop->Number<uint32_t>();
  }
  if (auto prop = accessor.Get(u8"type")) {
    auto type = *prop->U8String();
    if (type == u8"SCALAR") {
      dst.Type = Types::SCALAR;
    } else if (type == u8"VEC2") {
      dst.Type = Types::VEC2;
    } else if (type == u8"VEC3") {
      dst.Type = Types::VEC3;
    } else if (type == u8"VEC4") {
      dst.Type = Types::VEC4;
    } else if (type == u8"MAT2") {
      dst.Type = Types::MAT2;
    } else if (type == u8"MAT3") {
      dst.Type = Types::MAT3;
    } else if (type == u8"MAT4") {
      dst.Type = Types::MAT4;
    } else {
      // std::cout << "unknown type: " << type << std::endl;
    }
  }
  if (auto prop = accessor.Get(u8"max")) {
    DeserializeNumberVector(*prop, dst.Max);
  }
  if (auto prop = accessor.Get(u8"min")) {
    DeserializeNumberVector(*prop, dst.Min);
  }
  if (auto prop = accessor.Get(u8"sparse")) {
    dst.Sparse = Deserialize(*prop);
  }
}

// image/sampler/texture/material
inline void
Deserialize(const Value& image, Image& dst)
{
  DeserializeChildOfRootProp(image, dst);
  if (auto prop = image.Get(u8"uri")) {
    DeserializeString(*prop, dst.Uri);
  }
  if (auto prop = image.Get(u8"mimetype")) {
    DeserializeString(*prop, dst.MimeType);
  }
  if (auto prop = image.Get(u8"bufferView")) {
    dst.BufferView = *prop->Number<uint32_t>();
  }
}
inline void
Deserialize(const Value& sampler, Sampler& dst)
{
  DeserializeChildOfRootProp(sampler, dst);
}

inline void
Deserialize(const Value& texture, Texture& dst)
{
  DeserializeChildOfRootProp(texture, dst);
  if (auto prop = texture.Get(u8"sampler")) {
    dst.Sampler = *prop->Number<uint32_t>();
  }
  if (auto prop = texture.Get(u8"source")) {
    dst.Source = *prop->Number<uint32_t>();
  }
}

inline void
DeserializeTextureInfo(const Value& textureInfo, TextureInfo& dst)
{
  if (auto index = textureInfo.Get("index")) {
    dst.Index = index->Number<uint32_t>();
  }
}

inline void
Deserialize(const Value& value, PbrMetallicRoughness& dst)
{
  if (auto prop = value.Get(u8"baseColorFactor")) {
    if (auto factor = DeserializeNumberArray<float, 4>(*prop)) {
      dst.BaseColorFactor = *factor;
    }
  }
  if (auto prop = value.Get(u8"baseColorTexture")) {
    dst.BaseColorTexture = TextureInfo{};
    DeserializeTextureInfo(*prop, *dst.BaseColorTexture);
  }
  if (auto prop = value.Get(u8"metallicFactor")) {
    dst.MetallicFactor = *prop->Number<float>();
  }
  if (auto prop = value.Get(u8"roughnessFactor")) {
    dst.RoughnessFactor = *prop->Number<float>();
  }
  if (auto prop = value.Get(u8"metallicRoughnessTexture")) {
    dst.MetallicRoughnessTexture = TextureInfo{};
    DeserializeTextureInfo(*prop, *dst.MetallicRoughnessTexture);
  }
}

inline void
Deserialize(const Value& material, Material& dst)
{
  DeserializeChildOfRootProp(material, dst);
  if (auto prop = material.Get(u8"pbrMetallicRoughness")) {
    dst.PbrMetallicRoughness = PbrMetallicRoughness{};
    Deserialize(*prop, *dst.PbrMetallicRoughness);
  }
  if (auto prop = material.Get(u8"normalTexture")) {
    dst.NormalTexture = NormalTextureInfo{};
    DeserializeTextureInfo(*prop, *dst.NormalTexture);
  }
  if (auto prop = material.Get(u8"occlusionTexture")) {
    dst.OcclusionTexture = OcclusionTextureInfo{};
    DeserializeTextureInfo(*prop, *dst.OcclusionTexture);
  }
  if (auto prop = material.Get(u8"emissiveTexture")) {
    dst.EmissiveTexture = TextureInfo{};
    DeserializeTextureInfo(*prop, *dst.EmissiveTexture);
  }
  if (auto prop = material.Get(u8"emissiveFactor")) {
    if (auto factor = DeserializeNumberArray<float, 3>(*prop)) {
      dst.EmissiveFactor = *factor;
    }
  }
  if (auto prop = material.Get(u8"alphaMode")) {
    dst.AlphaMode = AlphaModesFromStr(*prop->U8String());
  }
  if (auto prop = material.Get(u8"alphaCutoff")) {
    dst.AlphaCutoff = *prop->Number<float>();
  }
  if (auto prop = material.Get(u8"doubleSided")) {
    dst.DoubleSided = prop->IsTrue();
  }
}

// skin/mesh
inline void
Deserialize(const Value& skin, Skin& dst)
{
  DeserializeChildOfRootProp(skin, dst);
  if (auto prop = skin.Get(u8"inverseBindMatrices")) {
    dst.InverseBindMatrices = *prop->Number<uint32_t>();
  }
  if (auto prop = skin.Get(u8"skeleton")) {
    dst.Skeleton = *prop->Number<uint32_t>();
  }
  if (auto prop = skin.Get(u8"joints")) {
    DeserializeNumberVector(*prop, dst.Joints);
  }
}

inline void
DeserializeAttribute(const Value& attributes, MeshPrimitiveAttributes& dst)
{
  if (auto POSITION = attributes.Get(u8"POSITION")) {
    dst.POSITION = *POSITION->Number<uint32_t>();
  }
  if (auto NORMAL = attributes.Get(u8"NORMAL")) {
    dst.NORMAL = *NORMAL->Number<uint32_t>();
  }
  if (auto TEXCOORD_0 = attributes.Get(u8"TEXCOORD_0")) {
    dst.TEXCOORD_0 = *TEXCOORD_0->Number<uint32_t>();
  }
  if (auto JOINTS_0 = attributes.Get(u8"JOINTS_0")) {
    dst.JOINTS_0 = *JOINTS_0->Number<uint32_t>();
  }
  if (auto WEIGHTS_0 = attributes.Get(u8"WEIGHTS_0")) {
    dst.WEIGHTS_0 = *WEIGHTS_0->Number<uint32_t>();
  }
}
inline void
DeserializeAttribute(const Value& attributes, MeshPrimitiveMorphTarget& dst)
{
  if (auto POSITION = attributes.Get(u8"POSITION")) {
    dst.POSITION = *POSITION->Number<uint32_t>();
  }
  if (auto NORMAL = attributes.Get(u8"NORMAL")) {
    dst.NORMAL = *NORMAL->Number<uint32_t>();
  }
}
inline void
Deserialize(const Value& primitive, MeshPrimitive& dst)
{
  if (auto prop = primitive.Get(u8"attributes")) {
    DeserializeAttribute(*prop, dst.Attributes);
  }

  if (auto prop = primitive.Get(u8"indices")) {
    dst.Indices = *prop->Number<uint32_t>();
  }

  if (auto prop = primitive.Get(u8"material")) {
    dst.Material = *prop->Number<uint32_t>();
  }
  if (auto prop = primitive.Get(u8"mode")) {
    dst.Mode = static_cast<MeshPrimitiveTopology>(*prop->Number<int>());
  }
  if (auto prop = primitive.Get(u8"targets")) {
    if (auto targets = prop->Array()) {
      for (auto& target : *targets) {
        dst.Targets.push_back({});
        DeserializeAttribute(target, dst.Targets.back());
      }
    }
  }
}

inline void
Deserialize(const Value& mesh, Mesh& dst)
{
  DeserializeChildOfRootProp(mesh, dst);
  if (auto prop = mesh.Get(u8"primitives")) {
    if (auto array = prop->Array()) {
      for (auto& item : *array) {
        dst.Primitives.push_back({});
        Deserialize(item, dst.Primitives.back());
      }
    }
  }
}

// node/scene
inline void
Deserialize(const Value& node, Node& dst)
{
  DeserializeChildOfRootProp(node, dst);

  if (auto prop = node.Get(u8"camera")) {
    dst.Camera = prop->Number<uint32_t>();
  }
  if (auto prop = node.Get(u8"children")) {
    DeserializeNumberVector(*prop, dst.Children);
  }
  if (auto prop = node.Get(u8"skin")) {
    dst.Skin = prop->Number<uint32_t>();
  }
  if (auto prop = node.Get(u8"matrix")) {
    dst.Matrix = DeserializeNumberArray<float, 16>(*prop);
  }
  if (auto prop = node.Get(u8"mesh")) {
    dst.Mesh = *prop->Number<uint32_t>();
  }
  if (auto prop = node.Get(u8"rotation")) {
    dst.Rotation = DeserializeNumberArray<float, 4>(*prop);
  }
  if (auto prop = node.Get(u8"scale")) {
    dst.Scale = DeserializeNumberArray<float, 3>(*prop);
  }
  if (auto prop = node.Get(u8"translation")) {
    dst.Translation = DeserializeNumberArray<float, 3>(*prop);
  }
  if (auto prop = node.Get(u8"weights")) {
    DeserializeNumberVector(*prop, dst.Weights);
  }
}

inline void
Deserialize(const Value& scene, Scene& dst)
{
  DeserializeChildOfRootProp(scene, dst);
  if (auto prop = scene.Get(u8"nodes")) {
    DeserializeNumberVector(*prop, dst.Nodes);
  }
}

// array
template<typename T>
inline void
DeserializeRootList(const Value& values, PropertyList<T>& dst)
{
  if (auto array = values.Array()) {
    for (auto& item : *array) {
      auto& value = dst.Push(T{});
      Deserialize(item, value);
    }
  }
}

inline void
Deserialize(const Parser& parser, Root& dst)
{
  auto root = parser.Values[0].Object();

  // buffer/buferView/accessor
  if (auto prop = root->Get(u8"buffers")) {
    DeserializeRootList(*prop, dst.Buffers);
  }
  if (auto prop = root->Get(u8"bufferViews")) {
    DeserializeRootList(*prop, dst.BufferViews);
  }
  if (auto prop = root->Get(u8"accessors")) {
    DeserializeRootList(*prop, dst.Accessors);
  }
  // image/sampler/texture/material/mesh
  if (auto prop = root->Get(u8"images")) {
    DeserializeRootList(*prop, dst.Images);
  }
  if (auto prop = root->Get(u8"samplers")) {
    DeserializeRootList(*prop, dst.Samplers);
  }
  if (auto prop = root->Get(u8"textures")) {
    DeserializeRootList(*prop, dst.Textures);
  }
  if (auto prop = root->Get(u8"materials")) {
    DeserializeRootList(*prop, dst.Materials);
  }
  // skin/mesh
  if (auto prop = root->Get(u8"skins")) {
    DeserializeRootList(*prop, dst.Skins);
  }
  if (auto prop = root->Get(u8"meshes")) {
    DeserializeRootList(*prop, dst.Meshes);
  }
  // node/scene
  if (auto prop = root->Get(u8"nodes")) {
    DeserializeRootList(*prop, dst.Nodes);
  }
  if (auto prop = root->Get(u8"scenes")) {
    DeserializeRootList(*prop, dst.Scenes);
  }

  if (auto prop = root->Get(u8"scene")) {
    dst.Scene = *prop->Number<uint32_t>();
  }
  if (auto prop = root->Get(u8"asset")) {
    Deserialize(*prop, dst.Asset);
  }

  // extensions
  if (auto prop = root->Get(u8"extensions")) {
    Deserialize(*prop, dst.Extensions);
  }
  if (auto prop = root->Get(u8"extras")) {
    Deserialize(*prop, dst.Extras);
  }
}

}
}
