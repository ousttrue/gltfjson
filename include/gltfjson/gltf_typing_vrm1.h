#pragma once
#include "gltf_typing.h"

namespace gltfjson {
namespace vrm1 {

// https://github.com/vrm-c/vrm-specification/blob/master/specification/VRMC_materials_mtoon-1.0/schema/VRMC_materials_mtoon.schema.json
struct MToon : JsonObject
{
  using JsonObject::JsonObject;

  auto ShadeMultiplyTexture()
  {
    return m_object<TextureInfo, u8"shadeMultiplyTexture">();
  }
  auto ShadeColorFactor()
  {
    return Vec3(m_json->Get(u8"shadeColorFactor"), { 0, 0, 0 });
  }

  auto MatcapTexture() { return m_object<TextureInfo, u8"matcapTexture">(); }
};

} // namespace
} // namespace
