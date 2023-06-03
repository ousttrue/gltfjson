#pragma once

namespace gltfjson {
namespace typing {

struct Vrm0Material : GltfProperty
{
  using GltfProperty::GltfProperty;

  auto MainTexture()
  {
    if (auto textures = m_json->Get(u8"textureProperties")) {
      if (auto texture = textures->Get(u8"_MainTex")) {
        return texture->Ptr<float>();
      }
    }
    return (float*)nullptr;
  }
  auto ShadeTexture()
  {
    if (auto textures = m_json->Get(u8"textureProperties")) {
      if (auto texture = textures->Get(u8"_ShadeTexture")) {
        return texture->Ptr<float>();
      }
    }
    return (float*)nullptr;
  }
  auto SphereAddTexture()
  {
    if (auto textures = m_json->Get(u8"textureProperties")) {
      if (auto texture = textures->Get(u8"_SphereAdd")) {
        return texture->Ptr<float>();
      }
    }
    return (float*)nullptr;
  }

  std::u8string RenderType()
  {
    if (auto tagMap = m_json->Get(u8"tagMap")) {
      if (auto renderType = tagMap->Get(u8"RenderType")) {
        return renderType->U8String();
      }
    }
    return u8"";
  }
};

}
}
