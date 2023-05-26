#pragma once
#include "gltf_typing.h"

namespace gltfjson {
namespace typing {
namespace vrm0 {

// https://github.com/vrm-c/vrm-specification/blob/master/specification/0.0/schema/vrm.meta.schema.json
struct Meta : JsonObject
{
  using JsonObject::JsonObject;

  auto Title() const { return m_string<u8"title">(); }
  auto Version() const { return m_string<u8"version">(); }
  auto Author() const { return m_string<u8"author">(); }
  auto ContactInformation() const { return m_string<u8"contactInformation">(); }
  auto Reference() const { return m_string<u8"reference">(); }
  auto Texture() const { return m_id<u8"texture">(); }
  auto AllowedUser() const { return m_string<u8"allowedUserName">(); }
  auto ViolentUsage() const { return m_string<u8"violentUssageName">(); }
  auto SexualUsage() const { return m_string<u8"sexualUssageName">(); }
  auto CommercialUsage() const { return m_string<u8"commercialUssageName">(); }
  auto OtherPermissionUrl() const { return m_string<u8"otherPermissionUrl">(); }
  auto License() const { return m_string<u8"licenseName">(); }
  auto OtherLicenseUrl() const { return m_string<u8"otherLicenseUrl">(); }
};

// https://github.com/vrm-c/vrm-specification/blob/master/specification/0.0/schema/vrm.humanoid.bone.schema.json
struct HumanBone : JsonObject
{
  auto Bone() const { return m_string<u8"bone">(); }
  auto Node() const { return m_id<u8"node">(); }
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

  auto FirstPersonBone() const { return m_id<u8"firstPersonBone">(); }
  auto FirstPersonBoneOffset() const
  {
    return m_ptr<gltfjson::tree::ObjectValue, u8"firstPersonBoneOffset">();
  }
  JsonArray<MeshAnnotation, u8"meshAnnotations"> MeshAnnotations;
  auto LookAtType() const { return m_string<u8"lookAtTypeName">(); }
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
  auto Mesh() const { return m_id<u8"mesh">(); }
  auto MorphIndex() const { return m_id<u8"index">(); }
  auto Weight() const { return m_ptr<float, u8"weight">(); }
};

// https://github.com/vrm-c/vrm-specification/blob/master/specification/0.0/schema/vrm.blendshape.materialbind.schema.json
struct MaterialBind : JsonObject
{
  using JsonObject::JsonObject;
  auto MaterialName() const { return m_string<u8"materialName">(); }
  auto PropertyName() const { return m_string<u8"propertyName">(); }
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
  const auto Name() const { return m_string<u8"name">(); }
  const auto Preset() const { return m_string<u8"presetName">(); }
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

  auto Comment() const { return m_string<u8"comment">(); }
  auto Stifness() const { return m_ptr<float, u8"stiffiness">(); }
  auto GravityPower() const { return m_ptr<float, u8"gravityPower">(); }
  auto GravityDir() const
  {
    return m_ptr<gltfjson::tree::ObjectValue, u8"gravityDir">();
  }
  auto DragForce() const { return m_ptr<float, u8"dragForce">(); }
  auto Center() const { return m_id<u8"center">(); }
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
  auto Node() const { return m_id<u8"node">(); }
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

// https://github.com/vrm-c/vrm-specification/blob/master/specification/0.0/schema/vrm.material.schema.json
struct Material : JsonObject
{
  using JsonObject::JsonObject;

  auto Name() const { return m_string<u8"name">(); }
  auto Shader() const { return m_string<u8"shader">(); }
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
};

struct VRM : JsonObject
{
  VRM(const gltfjson::tree::NodePtr& json)
    : JsonObject(json)
    , MaterialProperties(json)
  {
  }

  auto ExporterVersion() const { return m_string<u8"exporterVersion">(); }
  auto SpecVersion() const { return m_string<u8"specVersion">(); }
  auto Meta() const { return m_object<vrm0::Meta, u8"meta">(); }
  auto Humanoid() const { return m_object<vrm0::Humanoid, u8"humanoid">(); }
  auto FirstPerson() const
  {
    return m_object<vrm0::FirstPerson, u8"FirstPerson">();
  }
  auto BlendShapeMaster() const
  {
    return m_object<vrm0::BlendShapeMaster, u8"blendShapeMaster">();
  }
  auto SecondaryAnimation() const
  {
    return m_object<vrm0::SecondaryAnimation, u8"secondaryAnimation">();
  }
  JsonArray<Material, u8"materialProperties"> MaterialProperties;
};

}
}
}
