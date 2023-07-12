#pragma once
#include "gltf_typing.h"

namespace gltfjson {

// https://github.com/KhronosGroup/glTF/blob/main/extensions/2.0/Khronos/KHR_lights_punctual/schema/light.spot.schema.json
struct PunctualLightSpot : JsonObject
{
  using JsonObject::JsonObject;
};

// https://github.com/KhronosGroup/glTF/blob/main/extensions/2.0/Khronos/KHR_lights_punctual/schema/light.schema.json
struct PunctualLight : JsonObject
{
  using JsonObject::JsonObject;
  auto NameString() const { return m_string<u8"name">(); }
  auto ColorVec3() const { return m_float3<u8"color">(); }
  auto Intensity() const { return m_ptr<float, u8"intensity">(); }
  auto Spot() const { return m_object<PunctualLightSpot, u8"spot">(); }
  auto TypeString() const { return m_string<u8"type">(); }
  auto Range() const { return m_ptr<float, u8"range">(); }
};

// https://github.com/KhronosGroup/glTF/blob/main/extensions/2.0/Khronos/KHR_lights_punctual/schema/glTF.KHR_lights_punctual.schema.json
struct KHR_lights_punctual : Extension<u8"KHR_lights_punctual">
{
  KHR_lights_punctual(const tree::NodePtr& json)
    : Extension(json)
    , Lights(json)
  {
  }
  JsonArray<PunctualLight, u8"lights"> Lights;
};

struct KHR_materials_unlit : Extension<u8"KHR_materials_unlit">
{
  using Extension::Extension;
};

// https://github.com/KhronosGroup/glTF/blob/main/extensions/2.0/Khronos/KHR_texture_basisu/schema/texture.KHR_texture_basisu.schema.json
struct KHR_texture_basisu : Extension<u8"KHR_texture_basisu">
{
  using Extension::Extension;
  auto SourceId() const { return m_id<u8"source">(); }
};

} // namespace gltfjson
