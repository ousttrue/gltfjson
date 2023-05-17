#pragma once
#include "gltf.h"
#include "json.h"
#include <iostream>
#include <optional>

namespace gltfjson {

template<typename T>
inline void
DeserializeNumberArray(const Value& value, std::vector<T>& values)
{
  if (auto array = value.Array()) {
    for (auto& item : *array) {
      values.push_back(*item.Number<T>());
    }
  }
}

inline void
Deserialize(const Value* asset, format::Asset& dst)
{
  if (!asset) {
    return;
  }
  if (auto value = asset->Get("version")) {
    dst.Version = *value->String();
  }
}

// buffer/bufferview/accessor
inline void
Deserialize(const Value& buffer, format::Buffer& dst)
{
}

inline void
Deserialize(const Value& bufferView, format::BufferView& dst)
{
  if (auto prop = bufferView.Get(u8"buffer")) {
    dst.Buffer = *prop->Number<uint32_t>();
  }
  if (auto prop = bufferView.Get(u8"byteOffset")) {
    dst.ByteOffset = *prop->Number<uint32_t>();
  }
  if (auto prop = bufferView.Get(u8"byteLength")) {
    dst.ByteLength = *prop->Number<uint32_t>();
  }
  if (auto prop = bufferView.Get(u8"byteStride")) {
    dst.ByteStride = *prop->Number<uint32_t>();
  }
  if (auto prop = bufferView.Get(u8"target")) {
    dst.Target = static_cast<format::Targets>(*prop->Number<int>());
  }
}

inline void
Deserialize(const Value& accessor, format::Accessor& dst)
{
  if (auto prop = accessor.Get(u8"bufferView")) {
    dst.BufferView = *prop->Number<int>();
  }
  if (auto prop = accessor.Get(u8"byteOffset")) {
    dst.ByteOffset = *prop->Number<uint32_t>();
  }
  if (auto prop = accessor.Get(u8"componentType")) {
    dst.ComponentType =
      static_cast<format::ComponentTypes>(*prop->Number<int>());
  }
  if (auto prop = accessor.Get(u8"normalized")) {
    dst.Normalized = prop->IsTrue();
  }
  if (auto prop = accessor.Get(u8"count")) {
    dst.Count = *prop->Number<uint32_t>();
  }
  if (auto prop = accessor.Get(u8"type")) {
    auto type = *prop->String();
    if (type == u8"SCALAR") {
      dst.Type = format::Types::SCALAR;
    } else if (type == u8"VEC2") {
      dst.Type = format::Types::VEC2;
    } else if (type == u8"VEC3") {
      dst.Type = format::Types::VEC3;
    } else if (type == u8"VEC4") {
      dst.Type = format::Types::VEC4;
    } else if (type == u8"MAT2") {
      dst.Type = format::Types::MAT2;
    } else if (type == u8"MAT3") {
      dst.Type = format::Types::MAT3;
    } else if (type == u8"MAT4") {
      dst.Type = format::Types::MAT4;
    } else {
      std::cout << "unknown type: " << type << std::endl;
    }
  }
  if (auto prop = accessor.Get(u8"max")) {
    DeserializeNumberArray(*prop, dst.Max);
  }
  if (auto prop = accessor.Get(u8"min")) {
    DeserializeNumberArray(*prop, dst.Min);
  }
  if (auto prop = accessor.Get(u8"sparse")) {
  }
}

// image/sampler/texture/material
inline void
Deserialize(const Value& image, format::Image& dst)
{
}
inline void
Deserialize(const Value& sampler, format::Sampler& dst)
{
}

inline void
Deserialize(const Value& texture, format::Texture& dst)
{
}

inline void
Deserialize(const Value& material, format::Material& dst)
{
}

// skin/mesh
inline void
Deserialize(const Value& skin, format::Skin& dst)
{
}

inline void
Deserialize(const Value& primitive, format::MeshPrimitive& dst)
{
  if (auto prop = primitive.Get(u8"attributes")) {
    if (auto POSITION = prop->Get(u8"POSITION")) {
      dst.Attributes.POSITION = *POSITION->Number<uint32_t>();
    }
  }

  if (auto prop = primitive.Get(u8"indices")) {
    dst.Indices = *prop->Number<uint32_t>();
  }
}

inline void
Deserialize(const Value& mesh, format::Mesh& dst)
{
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
Deserialize(const Value& node, format::Node& dst)
{
  if (auto prop = node.Get(u8"mesh")) {
    dst.Mesh = *prop->Number<uint32_t>();
  }
}

inline void
Deserialize(const Value& node, format::Scene& dst)
{
  if (auto prop = node.Get(u8"nodes")) {
    DeserializeNumberArray(*prop, dst.Nodes);
  }
}

// array
template<typename T>
inline void
DeserializeArray(const Value& values, format::PropertyList<T>& dst)
{
  if (auto array = values.Array()) {
    for (auto& item : *array) {
      auto& value = dst.Push(T{});
      Deserialize(item, value);
    }
  }
}

inline void
Deserialize(const Parser& parser, format::Root& dst)
{
  auto root = parser.Values[0].Object();

  // buffer/buferView/accessor
  if (auto prop = root->Get(u8"buffers")) {
    DeserializeArray(*prop, dst.Buffers);
  }
  if (auto prop = root->Get(u8"bufferViews")) {
    DeserializeArray(*prop, dst.BufferViews);
  }
  if (auto prop = root->Get(u8"accessors")) {
    DeserializeArray(*prop, dst.Accessors);
  }
  // image/sampler/texture/material/mesh
  if (auto prop = root->Get(u8"images")) {
    DeserializeArray(*prop, dst.Images);
  }
  if (auto prop = root->Get(u8"sampler")) {
    DeserializeArray(*prop, dst.Samplers);
  }
  if (auto prop = root->Get(u8"textures")) {
    DeserializeArray(*prop, dst.Textures);
  }
  if (auto prop = root->Get(u8"materials")) {
    DeserializeArray(*prop, dst.Materials);
  }
  // skin/mesh
  if (auto prop = root->Get(u8"skins")) {
    DeserializeArray(*prop, dst.Skins);
  }
  if (auto prop = root->Get(u8"meshes")) {
    DeserializeArray(*prop, dst.Meshes);
  }
  // node/scene
  if (auto prop = root->Get(u8"nodes")) {
    DeserializeArray(*prop, dst.Nodes);
  }
  if (auto prop = root->Get(u8"scenes")) {
    DeserializeArray(*prop, dst.Scenes);
  }

  if (auto prop = root->Get(u8"scene")) {
    dst.Scene = *prop->Number<uint32_t>();
  }
  if (auto asset = root->Get(u8"asset")) {
    Deserialize(asset, dst.Asset);
  }
}
}
