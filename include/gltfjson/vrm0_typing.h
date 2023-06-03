#pragma once
#include "gltf_typing.h"
#include <array>

namespace gltfjson {
namespace typing {

inline std::array<float, 3>
Vec3(const gltfjson::tree::NodePtr& json,
     const std::array<float, 3>& defaultValue)
{
  if (json) {
    if (auto a = json->Array()) {
      if (a->size() == 3) {
        if (auto a0 = (*a)[0]) {
          if (auto p0 = a0->Ptr<float>()) {
            if (auto a1 = (*a)[1]) {
              if (auto p1 = a1->Ptr<float>()) {
                if (auto a2 = (*a)[2]) {
                  if (auto p2 = a2->Ptr<float>()) {
                    return { *p0, *p1, *p2 };
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  return defaultValue;
}

inline std::array<float, 4>
Vec4(const gltfjson::tree::NodePtr& json,
     const std::array<float, 4>& defaultValue)
{
  if (json) {
    if (auto a = json->Array()) {
      if (a->size() == 4) {
        if (auto a0 = (*a)[0]) {
          if (auto p0 = a0->Ptr<float>()) {
            if (auto a1 = (*a)[1]) {
              if (auto p1 = a1->Ptr<float>()) {
                if (auto a2 = (*a)[2]) {
                  if (auto p2 = a2->Ptr<float>()) {
                    if (auto a3 = (*a)[3]) {
                      if (auto p3 = a3->Ptr<float>()) {
                        return { *p0, *p1, *p2, *p3 };
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  return defaultValue;
}

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

  std::array<float, 4> Color()
  {
    if (auto vectors = m_json->Get(u8"vectorProperties")) {
      return Vec4(vectors->Get(u8"_Color"), { 1, 1, 1, 1 });
    }
    return { 1, 1, 1, 1 };
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

  std::array<float, 3> ShadeColor()
  {
    {
      if (auto vectors = m_json->Get(u8"vectorProperties")) {
        auto c = Vec4(vectors->Get(u8"_ShadeColor"), { 1, 1, 1 });
        return { c[0], c[1], c[2] };
      }
      return { 1, 1, 1 };
    }
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
