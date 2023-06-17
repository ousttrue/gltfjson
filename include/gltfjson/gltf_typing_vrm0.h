#pragma once
#include "gltf_typing.h"

namespace gltfjson {
namespace vrm0 {

// https://github.com/vrm-c/vrm-specification/blob/master/specification/0.0/schema/vrm.meta.schema.json
struct Meta : JsonObject
{
  using JsonObject::JsonObject;

  auto TitleString() const { return m_string<u8"title">(); }
  auto VersionString() const { return m_string<u8"version">(); }
  auto AuthorString() const { return m_string<u8"author">(); }
  auto ContactInformationString() const { return m_string<u8"contactInformation">(); }
  auto ReferenceString() const { return m_string<u8"reference">(); }
  auto TextureId() const { return m_id<u8"texture">(); }
  auto AllowedUserString() const { return m_string<u8"allowedUserName">(); }
  auto ViolentUsageString() const { return m_string<u8"violentUssageName">(); }
  auto SexualUsageString() const { return m_string<u8"sexualUssageName">(); }
  auto CommercialUsageString() const { return m_string<u8"commercialUssageName">(); }
  auto OtherPermissionUrlString() const { return m_string<u8"otherPermissionUrl">(); }
  auto LicenseString() const { return m_string<u8"licenseName">(); }
  auto OtherLicenseUrlString() const { return m_string<u8"otherLicenseUrl">(); }
};

// https://github.com/vrm-c/vrm-specification/blob/master/specification/0.0/schema/vrm.humanoid.bone.schema.json
struct HumanBone : JsonObject
{
  auto BoneString() const { return m_string<u8"bone">(); }
  auto NodeId() const { return m_id<u8"node">(); }
  auto Center() const
  {
    return m_ptr<gltfjson::tree::ObjectValue, u8"center">();
  }
};

// https://github.com/vrm-c/vrm-specification/blob/master/specification/0.0/schema/vrm.humanoid.schema.json
struct Humanoid : JsonObject
{
  Humanoid(const gltfjson::tree::NodePtr& json)
    : JsonObject(json)
    , HumanBones(json)
  {
  }
  JsonArray<HumanBone, u8"humanBones"> HumanBones;
};

struct MeshAnnotation : JsonObject
{};

struct DegreeMap : JsonObject
{};

// https://github.com/vrm-c/vrm-specification/blob/master/specification/0.0/schema/vrm.firstperson.schema.json
struct FirstPerson : JsonObject
{
  FirstPerson(const gltfjson::tree::NodePtr& json)
    : JsonObject(json)
    , MeshAnnotations(json)
  {
  }

  auto FirstPersonBoneId() const { return m_id<u8"firstPersonBone">(); }
  auto FirstPersonBoneOffset() const
  {
    return m_ptr<gltfjson::tree::ObjectValue, u8"firstPersonBoneOffset">();
  }
  JsonArray<MeshAnnotation, u8"meshAnnotations"> MeshAnnotations;
  auto LookAtTypeString() const { return m_string<u8"lookAtTypeName">(); }
  auto lookAtHorizontalInner() const
  {
    return m_object<DegreeMap, u8"lookAtHorizontalInner">();
  }
  auto lookAtHorizontalOuter() const
  {
    return m_object<DegreeMap, u8"lookAtHorizontalOuter">();
  }
  auto lookAtVerticalDown() const
  {
    return m_object<DegreeMap, u8"lookAtVerticalDown">();
  }
  auto lookAtVerticalUp() const
  {
    return m_object<DegreeMap, u8"lookAtVerticalUp">();
  }
};

// https://github.com/vrm-c/vrm-specification/blob/master/specification/0.0/schema/vrm.blendshape.bind.schema.json
struct MorphBind : JsonObject
{
  using JsonObject::JsonObject;
  auto MeshId() const { return m_id<u8"mesh">(); }
  auto MorphIndexId() const { return m_id<u8"index">(); }
  auto Weight() const { return m_ptr<float, u8"weight">(); }
};

// https://github.com/vrm-c/vrm-specification/blob/master/specification/0.0/schema/vrm.blendshape.materialbind.schema.json
struct MaterialBind : JsonObject
{
  using JsonObject::JsonObject;
  auto MaterialNameString() const { return m_string<u8"materialName">(); }
  auto PropertyNameString() const { return m_string<u8"propertyName">(); }
  auto TargetValue() const
  {
    return m_ptr<gltfjson::tree::ObjectValue, u8"targetValue">();
  }
};

// https://github.com/vrm-c/vrm-specification/blob/master/specification/0.0/schema/vrm.blendshape.group.schema.json
struct BlendShapeGroup : JsonObject
{
  BlendShapeGroup(const gltfjson::tree::NodePtr& json)
    : JsonObject(json)
    , MorphBinds(json)
    , MaterialBinds(json)
  {
  }
  const auto NameString() const { return m_string<u8"name">(); }
  const auto PresetString() const { return m_string<u8"presetName">(); }
  JsonArray<MorphBind, u8"binds"> MorphBinds;
  JsonArray<MaterialBind, u8"materialValues"> MaterialBinds;
  const auto IsBinary() const { return m_ptr<bool, u8"isBinary">(); }
};

// https://github.com/vrm-c/vrm-specification/blob/master/specification/0.0/schema/vrm.blendshape.schema.json
struct BlendShapeMaster : JsonObject
{
  using JsonObject::JsonObject;
  BlendShapeMaster(const gltfjson::tree::NodePtr& json)
    : JsonObject(json)
    , BlendShapeGroups(json)
  {
  }

  JsonArray<BlendShapeGroup, u8"blendShapeGroups"> BlendShapeGroups;
};

struct Spring : JsonObject
{
  using JsonObject::JsonObject;

  auto CommentString() const { return m_string<u8"comment">(); }
  auto Stifness() const { return m_ptr<float, u8"stiffiness">(); }
  auto GravityPower() const { return m_ptr<float, u8"gravityPower">(); }
  auto GravityDir() const
  {
    return m_ptr<gltfjson::tree::ObjectValue, u8"gravityDir">();
  }
  auto DragForce() const { return m_ptr<float, u8"dragForce">(); }
  auto CenterId() const { return m_id<u8"center">(); }
  auto HitRadius() const { return m_ptr<float, u8"hitRadius">(); }
  auto Bones() const { return m_ptr<gltfjson::tree::ArrayValue, u8"bones">(); }
  auto ColliderGroups() const
  {
    return m_ptr<gltfjson::tree::ArrayValue, u8"colliderGroups">();
  }
};

struct Collider : JsonObject
{
  using JsonObject::JsonObject;
  auto Offset() const
  {
    return m_ptr<gltfjson::tree::ObjectValue, u8"offset">();
  }
  auto Radius() const { return m_ptr<float, u8"radius">(); }
};

// https://github.com/vrm-c/vrm-specification/blob/master/specification/0.0/schema/vrm.secondaryanimation.collidergroup.schema.json
struct ColliderGroup : JsonObject
{
  ColliderGroup(const gltfjson::tree::NodePtr& json)
    : JsonObject(json)
    , Colliders(json)
  {
  }
  auto NodeId() const { return m_id<u8"node">(); }
  JsonArray<Collider, u8"colliders"> Colliders;
};

// https://github.com/vrm-c/vrm-specification/blob/master/specification/0.0/schema/vrm.secondaryanimation.schema.json
struct SecondaryAnimation : JsonObject
{
  SecondaryAnimation(const gltfjson::tree::NodePtr& json)
    : JsonObject(json)
    , Springs(json)
    , ColliderGroups(json)
  {
  }
  JsonArray<Spring, u8"boneGroups"> Springs;
  JsonArray<ColliderGroup, u8"colliderGroups"> ColliderGroups;
};

enum RenderMode
{
  Opaque = 0,
  Cutout = 1,
  Transparent = 2,
  TransparentWithZWrite = 3,
};

// https://github.com/vrm-c/vrm-specification/blob/master/specification/0.0/schema/vrm.material.schema.json
struct Material : JsonObject
{
  using JsonObject::JsonObject;

  auto NameString() const { return m_string<u8"name">(); }
  auto ShaderString() const { return m_string<u8"shader">(); }
  auto RenderQueue() const { return m_ptr<float, u8"renderQueue">(); }
  auto FloatProperties() const
  {
    return m_ptr<gltfjson::tree::ObjectValue, u8"floatProperties">();
  }
  auto vectorProperties() const
  {
    return m_ptr<gltfjson::tree::ObjectValue, u8"vectorProperties">();
  }
  auto textureProperties() const
  {
    return m_ptr<gltfjson::tree::ObjectValue, u8"textureProperties">();
  }
  auto keywordMap() const
  {
    return m_ptr<gltfjson::tree::ObjectValue, u8"keywordMap">();
  }
  auto tagMap() const
  {
    return m_ptr<gltfjson::tree::ObjectValue, u8"tagMap">();
  }

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

  float* BlendMode()
  {
    if (auto props = m_json->Get(u8"floatProperties")) {
      if (auto mode = props->Get(u8"_BlendMode")) {
        return mode->Ptr<float>();
      }
    }
    return {};
  }

  float* Cutoff()
  {
    if (auto props = m_json->Get(u8"floatProperties")) {
      if (auto mode = props->Get(u8"_Cutoff")) {
        return mode->Ptr<float>();
      }
    }
    return {};
  }
};

// https://github.com/vrm-c/vrm-specification/blob/master/specification/0.0/schema/vrm.schema.json
struct VRM : Extension<u8"VRM">
{
  VRM(const gltfjson::tree::NodePtr& json)
    : Extension(json)
    , MaterialProperties(json)
  {
  }

  auto ExporterVersionString() const { return m_string<u8"exporterVersion">(); }
  auto SpecVersionString() const { return m_string<u8"specVersion">(); }
  auto Meta() const { return m_object<vrm0::Meta, u8"meta">(); }
  auto Humanoid() const { return m_object<vrm0::Humanoid, u8"humanoid">(); }
  auto FirstPerson() const
  {
    return m_object<vrm0::FirstPerson, u8"firstPerson">();
  }
  auto BlendShapeMaster() const
  {
    return m_object<vrm0::BlendShapeMaster, u8"blendShapeMaster">();
  }
  auto SecondaryAnimation() const
  {
    return m_object<vrm0::SecondaryAnimation, u8"secondaryAnimation">();
  }
  auto Spring() const
  {
    return m_object<vrm0::SecondaryAnimation, u8"secondaryAnimation">();
  }
  JsonArray<Material, u8"materialProperties"> MaterialProperties;
};

inline std::u8string
GetHumanBoneName(Root root, uint32_t i)
{
  if (auto vrm = root.GetExtension<VRM>()) {
    if (auto humanoid = vrm->Humanoid()) {
      for (auto bone : humanoid->HumanBones) {
        if (bone.NodeId() == i) {
          return bone.BoneString();
        }
      }
    }
  }
  return {};
}

inline tree::NodePtr
GetVrmMaterial(Root root, uint32_t i)
{
  if (auto vrm = root.GetExtension<VRM>()) {
    {
      if (i < vrm->MaterialProperties.size()) {
        return vrm->MaterialProperties[i].m_json;
      }
    }
  }
  return {};
}

} // namespace
} // namespace
