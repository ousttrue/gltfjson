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
};

}
}
