#pragma once
#include "gltf.h"
#include "json.h"
#include <iostream>
#include <optional>

namespace gltfjson {

inline void
Deserialize(const Value& value, std::vector<float>& values)
{
  if (auto array = value.Array()) {
    for (auto& item : *array) {
      values.push_back(*item.Number<float>());
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

inline void
Deserialize(const Value& accessor, format::Accessor& dst)
{
  if (auto prop = accessor.Get(u8"bufferView")) {
    dst.BufferView.Index = *prop->Number<int>();
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
    Deserialize(*prop, dst.Max);
  }
  if (auto prop = accessor.Get(u8"min")) {
    Deserialize(*prop, dst.Min);
  }
  if (auto prop = accessor.Get(u8"sparse")) {
  }
}

inline void
Deserialize(const Value& bufferView, format::BufferView& dst)
{
  if (auto prop = bufferView.Get(u8"buffer")) {
    dst.Buffer.Index = *prop->Number<uint32_t>();
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

template<typename T>
inline void
DeserializeArray(const Value* prop, format::PropertyList<T>& dst)
{
  if (!prop) {
    return;
  }
  if (auto array = prop->Array()) {
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
  if (auto prop = root->Get(u8"accessors")) {
    DeserializeArray(prop, dst.Accessors);
  }
  if (auto prop = root->Get(u8"bufferViews")) {
    DeserializeArray(prop, dst.BufferViews);
  }
  if (auto asset = root->Get(u8"asset")) {
    Deserialize(asset, dst.Asset);
  }
}
}
