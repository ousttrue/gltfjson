#pragma once
#include "gltf_typing.h"

namespace gltfjson {
namespace vrm1 {

// https://github.com/vrm-c/vrm-specification/blob/master/specification/VRMC_vrm-1.0/schema/VRMC_vrm.meta.schema.json
struct Meta : JsonObject
{
  using JsonObject::JsonObject;

  auto NameString() { return m_string<u8"name">(); }
  auto VersionString() { return m_string<u8"version">(); }
  auto Authors() { return m_ptr<tree::ArrayValue, u8"authors">(); }
  auto CopyrightInformationString()
  {
    return m_string<u8"copyrightInformation">();
  }
  auto ContactInformationString() { return m_string<u8"contactInformation">(); }
  auto References() { return m_ptr<tree::ArrayValue, u8"references">(); }
  auto ThirdPartyLicensesString() { return m_string<u8"thirdPartyLicenses">(); }
  auto ThumbnailImageId() { return m_id<u8"thumbnailImage">(); }
  auto LicenseUrlString() { return m_string<u8"licenseUrl">(); }
  auto AvatarPermissionString() { return m_string<u8"avatarPermission">(); }
  auto AllowExcessivelyViolentUsage()
  {
    return m_ptr<bool, u8"allowExcessivelyViolentUsage">();
  }
  auto AllowExcessivelySexualUsage()
  {
    return m_ptr<bool, u8"allowExcessivelySexualUsage">();
  }
  auto CommercialUsageString() { return m_string<u8"commercialUsage">(); }
  auto AllowPoliticalOrReligiousUsage()
  {
    return m_ptr<bool, u8"allowPoliticalOrReligiousUsage">();
  }
  auto AllowAntisocialOrHateUsage()
  {
    return m_ptr<bool, u8"allowAntisocialOrHateUsage">();
  }
  auto CreditNotationString() { return m_string<u8"creditNotation">(); }
  auto AllowRedistribution() { return m_ptr<bool, u8"allowRedistribution">(); }
  auto ModificationString() { return m_string<u8"modification">(); }
  auto OtherLicenseUrlString() { return m_string<u8"otherLicenseUrl">(); }
};

// https://github.com/vrm-c/vrm-specification/blob/master/specification/VRMC_vrm-1.0/schema/VRMC_vrm.humanoid.humanBones.schema.json
struct HumanBones : JsonObject
{
  using JsonObject::JsonObject;

  auto Hips() { return m_ptr<tree::ObjectValue, u8"hips">(); }
  auto Spine() { return m_ptr<tree::ObjectValue, u8"spine">(); }
  auto Chest() { return m_ptr<tree::ObjectValue, u8"chest">(); }
  auto UpperChest() { return m_ptr<tree::ObjectValue, u8"upperChest">(); }
  auto Neck() { return m_ptr<tree::ObjectValue, u8"neck">(); }
  auto Head() { return m_ptr<tree::ObjectValue, u8"head">(); }
  auto LeftEye() { return m_ptr<tree::ObjectValue, u8"leftEye">(); }
  auto RightEye() { return m_ptr<tree::ObjectValue, u8"rightEye">(); }
  auto Jaw() { return m_ptr<tree::ObjectValue, u8"jaw">(); }
  auto LeftUpperLeg() { return m_ptr<tree::ObjectValue, u8"leftUpperLeg">(); }
  auto LeftLowerLeg() { return m_ptr<tree::ObjectValue, u8"leftLowerLeg">(); }
  auto LeftFoot() { return m_ptr<tree::ObjectValue, u8"leftFoot">(); }
  auto LeftToes() { return m_ptr<tree::ObjectValue, u8"leftToes">(); }
  auto RightUpperLeg() { return m_ptr<tree::ObjectValue, u8"rightUpperLeg">(); }
  auto RightLowerLeg() { return m_ptr<tree::ObjectValue, u8"rightLowerLeg">(); }
  auto RightFoot() { return m_ptr<tree::ObjectValue, u8"rightFoot">(); }
  auto RightToes() { return m_ptr<tree::ObjectValue, u8"rightToes">(); }
  auto LeftShoulder() { return m_ptr<tree::ObjectValue, u8"leftShoulder">(); }
  auto LeftUpperArm() { return m_ptr<tree::ObjectValue, u8"leftUpperArm">(); }
  auto LeftLowerArm() { return m_ptr<tree::ObjectValue, u8"leftLowerArm">(); }
  auto LeftHand() { return m_ptr<tree::ObjectValue, u8"leftHand">(); }
  auto RightShoulder() { return m_ptr<tree::ObjectValue, u8"rightShoulder">(); }
  auto RightUpperArm() { return m_ptr<tree::ObjectValue, u8"rightUpperArm">(); }
  auto RightLowerArm() { return m_ptr<tree::ObjectValue, u8"rightLowerArm">(); }
  auto RightHand() { return m_ptr<tree::ObjectValue, u8"rightHand">(); }
  auto LeftThumbMetacarpal()
  {
    return m_ptr<tree::ObjectValue, u8"leftThumbMetacarpal">();
  }
  auto LeftThumbProximal()
  {
    return m_ptr<tree::ObjectValue, u8"leftThumbProximal">();
  }
  auto LeftThumbDistal()
  {
    return m_ptr<tree::ObjectValue, u8"leftThumbDistal">();
  }
  auto LeftIndexProximal()
  {
    return m_ptr<tree::ObjectValue, u8"leftIndexProximal">();
  }
  auto LeftIndexIntermediate()
  {
    return m_ptr<tree::ObjectValue, u8"leftIndexIntermediate">();
  }
  auto LeftIndexDistal()
  {
    return m_ptr<tree::ObjectValue, u8"leftIndexDistal">();
  }
  auto LeftMiddleProximal()
  {
    return m_ptr<tree::ObjectValue, u8"leftMiddleProximal">();
  }
  auto LeftMiddleIntermediate()
  {
    return m_ptr<tree::ObjectValue, u8"leftMiddleIntermediate">();
  }
  auto LeftMiddleDistal()
  {
    return m_ptr<tree::ObjectValue, u8"leftMiddleDistal">();
  }
  auto LeftRingProximal()
  {
    return m_ptr<tree::ObjectValue, u8"leftRingProximal">();
  }
  auto LeftRingIntermediate()
  {
    return m_ptr<tree::ObjectValue, u8"leftRingIntermediate">();
  }
  auto LeftRingDistal()
  {
    return m_ptr<tree::ObjectValue, u8"leftRingDistal">();
  }
  auto LeftLittleProximal()
  {
    return m_ptr<tree::ObjectValue, u8"leftLittleProximal">();
  }
  auto LeftLittleIntermediate()
  {
    return m_ptr<tree::ObjectValue, u8"leftLittleIntermediate">();
  }
  auto LeftLittleDistal()
  {
    return m_ptr<tree::ObjectValue, u8"leftLittleDistal">();
  }
  auto RightThumbMetacarpal()
  {
    return m_ptr<tree::ObjectValue, u8"rightThumbMetacarpal">();
  }
  auto RightThumbProximal()
  {
    return m_ptr<tree::ObjectValue, u8"rightThumbProximal">();
  }
  auto RightThumbDistal()
  {
    return m_ptr<tree::ObjectValue, u8"rightThumbDistal">();
  }
  auto rightIndexProximal()
  {
    return m_ptr<tree::ObjectValue, u8"rightIndexProximal">();
  }
  auto RightIndexIntermediate()
  {
    return m_ptr<tree::ObjectValue, u8"rightIndexIntermediate">();
  }
  auto RightIndexDistal()
  {
    return m_ptr<tree::ObjectValue, u8"rightIndexDistal">();
  }
  auto RightMiddleProximal()
  {
    return m_ptr<tree::ObjectValue, u8"rightMiddleProximal">();
  }
  auto RightMiddleIntermediate()
  {
    return m_ptr<tree::ObjectValue, u8"rightMiddleIntermediate">();
  }
  auto RightMiddleDistal()
  {
    return m_ptr<tree::ObjectValue, u8"rightMiddleDistal">();
  }
  auto RightRingProximal()
  {
    return m_ptr<tree::ObjectValue, u8"rightRingProximal">();
  }
  auto RightRingIntermediate()
  {
    return m_ptr<tree::ObjectValue, u8"rightRingIntermediate">();
  }
  auto RightRingDistal()
  {
    return m_ptr<tree::ObjectValue, u8"rightRingDistal">();
  }
  auto RightLittleProximal()
  {
    return m_ptr<tree::ObjectValue, u8"rightLittleProximal">();
  }
  auto RightLittleIntermediate()
  {
    return m_ptr<tree::ObjectValue, u8"rightLittleIntermediate">();
  }
  auto RightLittleDistal()
  {
    return m_ptr<tree::ObjectValue, u8"rightLittleDistal">();
  }
};

// https://github.com/vrm-c/vrm-specification/blob/master/specification/VRMC_vrm-1.0/schema/VRMC_vrm.humanoid.schema.json
struct Humanoid : JsonObject
{
  using JsonObject::JsonObject;
  auto HumanBones() { return m_object<vrm1::HumanBones, u8"humanBones">(); }
};

// https://github.com/vrm-c/vrm-specification/blob/master/specification/VRMC_vrm-1.0/schema/VRMC_vrm.expressions.expression.morphTargetBind.schema.json
struct MorphTargetBind : JsonObject
{
  using JsonObject::JsonObject;
  auto NodeId() { return m_id<u8"node">(); }
  auto IndexId() { return m_id<u8"index">(); }
  auto Weight() { return m_ptr<float, u8"weight">(); }
};

// https://github.com/vrm-c/vrm-specification/blob/master/specification/VRMC_vrm-1.0/schema/VRMC_vrm.expressions.expression.materialColorBind.schema.json
struct MaterialColorBind : JsonObject
{
  using JsonObject::JsonObject;
  auto MaterialId() { return m_id<u8"material">(); }
  auto TypeString() { return m_string<u8"type">(); }
  auto TargetValueVec4() { return m_float4<u8"targetValue">(); }
};

// https://github.com/vrm-c/vrm-specification/blob/master/specification/VRMC_vrm-1.0/schema/VRMC_vrm.expressions.expression.textureTransformBind.schema.json
struct TextureTransformBind : JsonObject
{
  using JsonObject::JsonObject;
  auto MaterialId() { return m_id<u8"material">(); }
  auto ScaleVec2() { return m_float2<u8"scale">(); }
  auto OffsetVec2() { return m_float2<u8"offset">(); }
};

// https://github.com/vrm-c/vrm-specification/blob/master/specification/VRMC_vrm-1.0/schema/VRMC_vrm.expressions.expression.schema.json
struct Expression : JsonObject
{
  Expression(const tree::NodePtr& json)
    : JsonObject(json)
    , MorphTargetBinds(json)
    , MaterialColorBinds(json)
    , TextureTransformBinds(json)
  {
  }
  JsonArray<MorphTargetBind, u8"morphTargetBinds"> MorphTargetBinds;
  JsonArray<MaterialColorBind, u8"materialColorBinds"> MaterialColorBinds;
  JsonArray<TextureTransformBind, u8"textureTransformBinds">
    TextureTransformBinds;
  bool IsBinaryOrFalse() const
  {
    if (auto p = m_ptr<bool, u8"isBinary">()) {
      return *p;
    }
    return false;
  }
  auto OverrideBlinkString() const
  {
    return m_string<u8"overrideBlinkString">();
  }
  auto OverrideLookAtString() const { return m_string<u8"overrideLookAt">(); }
  auto OverrideMouthString() const { return m_string<u8"overrideMouth">(); }
};

struct ExpressionPreset : JsonObject
{
  using JsonObject::JsonObject;

  auto Happy() { return m_object<Expression, u8"happy">(); }
  auto Angry() { return m_object<Expression, u8"angry">(); }
  auto Sad() { return m_object<Expression, u8"sad">(); }
  auto Relaxed() { return m_object<Expression, u8"relaxed">(); }
  auto Surprised() { return m_object<Expression, u8"surprised">(); }
  auto Aa() { return m_object<Expression, u8"aa">(); }
  auto Ih() { return m_object<Expression, u8"ih">(); }
  auto Ou() { return m_object<Expression, u8"ou">(); }
  auto Ee() { return m_object<Expression, u8"ee">(); }
  auto Oh() { return m_object<Expression, u8"oh">(); }
  auto Blink() { return m_object<Expression, u8"blink">(); }
  auto BlinkLeft() { return m_object<Expression, u8"blinkLeft">(); }
  auto BlinkRight() { return m_object<Expression, u8"blinkRight">(); }
  auto LookUp() { return m_object<Expression, u8"lookUp">(); }
  auto LookDown() { return m_object<Expression, u8"lookDown">(); }
  auto LookLeft() { return m_object<Expression, u8"lookLeft">(); }
  auto LookRight() { return m_object<Expression, u8"lookRight">(); }
  auto Neutral() { return m_object<Expression, u8"neutral">(); }
};

// https://github.com/vrm-c/vrm-specification/blob/master/specification/VRMC_vrm-1.0/schema/VRMC_vrm.lookAt.schema.json
struct LookAt : JsonObject
{
  auto TypeString() { return m_string<u8"type">(); }
};

// https://github.com/vrm-c/vrm-specification/blob/master/specification/VRMC_vrm-1.0/schema/VRMC_vrm.firstPerson.meshAnnotation.schema.json
struct MeshAnnotation : JsonObject
{
  using JsonObject::JsonObject;

  auto NodeId() { return m_id<u8"node">(); }
  auto TypeString() { return m_string<u8"type">(); }
};

// https://github.com/vrm-c/vrm-specification/blob/master/specification/VRMC_vrm-1.0/schema/VRMC_vrm.firstPerson.schema.json
struct FirstPerson : JsonObject
{
  FirstPerson(const gltfjson::tree::NodePtr& json)
    : JsonObject(json)
    , MeshAnnotations(json)
  {
  }
  JsonArray<MeshAnnotation, u8"meshAnnotations"> MeshAnnotations;
};

struct Expressions : JsonObject
{
  using JsonObject::JsonObject;

  auto Preset() { return m_object<ExpressionPreset, u8"preset">(); }
  auto Custom() { return m_ptr<tree::ObjectValue, u8"custom">(); }
};

// https://github.com/vrm-c/vrm-specification/blob/master/specification/VRMC_vrm-1.0/schema/VRMC_vrm.schema.json
struct VRMC_vrm : Extension<u8"VRMC_vrm">
{
  using Extension::Extension;

  auto SpecVersionString() { return m_string<u8"specVersion">(); }
  auto Meta() { return m_object<vrm1::Meta, u8"meta">(); }
  auto Humanoid() { return m_object<vrm1::Humanoid, u8"humanoid">(); }
  auto LookAt() { return m_object<vrm1::LookAt, u8"lookAt">(); }
  auto FirstPerson() { return m_object<vrm1::FirstPerson, u8"firstPerson">(); }
  auto Expressions() { return m_object<vrm1::Expressions, u8"expressions">(); }
};

// https://github.com/vrm-c/vrm-specification/blob/master/specification/VRMC_materials_mtoon-1.0/schema/VRMC_materials_mtoon.schema.json
struct VRMC_materials_mtoon : Extension<u8"VRMC_materials_mtoon">
{
  using Extension::Extension;

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
using MToon = VRMC_materials_mtoon;

struct SpringColliderShapeSphere : JsonObject
{
  using JsonObject::JsonObject;
  auto Offset() { return m_ptr<tree::ObjectValue, u8"offset">(); }
  auto Radius() { return m_ptr<float, u8"radius">(); }
};

struct SpringColliderShapeCapsule : JsonObject
{
  using JsonObject::JsonObject;
  auto Offset() { return m_ptr<tree::ObjectValue, u8"offset">(); }
  auto Radius() { return m_ptr<float, u8"radius">(); }
  auto Tail() { return m_ptr<tree::ObjectValue, u8"tail">(); }
};

// https://github.com/vrm-c/vrm-specification/blob/master/specification/VRMC_springBone-1.0/schema/VRMC_springBone.shape.schema.json
struct SpringColliderShape : JsonObject
{
  using JsonObject::JsonObject;
  auto Sphere() { return m_object<SpringColliderShapeSphere, u8"sphere">(); }
  auto Capsule() { return m_object<SpringColliderShapeSphere, u8"capsule">(); }
};

// https://github.com/vrm-c/vrm-specification/blob/master/specification/VRMC_springBone-1.0/schema/VRMC_springBone.collider.schema.json
struct SpringCollider : JsonObject
{
  using JsonObject::JsonObject;
  auto NodeId() { return m_id<u8"node">(); }
  auto Shape() { return m_object<SpringColliderShape, u8"shape">(); }
};

// https://github.com/vrm-c/vrm-specification/blob/master/specification/VRMC_springBone-1.0/schema/VRMC_springBone.colliderGroup.schema.json
struct SpringColliderGroup : JsonObject
{
  using JsonObject::JsonObject;
  auto NameString() { return m_string<u8"name">(); }
  JsonArray<SpringCollider, u8"colliders"> Colliders;
};

// https://github.com/vrm-c/vrm-specification/blob/master/specification/VRMC_springBone-1.0/schema/VRMC_springBone.joint.schema.json
struct SpringJoint : JsonObject
{
  using JsonObject::JsonObject;
  auto NodeId() { return m_id<u8"node">(); }
  auto HitRadius() { return m_ptr<float, u8"hitRadius">(); }
  auto Stiffness() { return m_ptr<float, u8"stiffness">(); }
  auto GravityPower() { return m_ptr<float, u8"gravityPower">(); }
  auto GravityDir() { return m_ptr<tree::ArrayValue, u8"gravityDir">(); }
  auto DragForce() { return m_ptr<float, u8"dragForce">(); }
};

// https://github.com/vrm-c/vrm-specification/blob/master/specification/VRMC_springBone-1.0/schema/VRMC_springBone.spring.schema.json
struct Spring : JsonObject
{
  Spring(const tree::NodePtr& json)
    : JsonObject(json)
    , Joints(json)
  {
  }
  auto NameString() { return m_string<u8"name">(); }
  JsonArray<SpringJoint, u8"joints"> Joints;
  auto ColliderGroups()
  {
    return m_ptr<tree::ArrayValue, u8"colliderGroups">();
  }
  auto CenterId() { return m_id<u8"center">(); }
};

// https://github.com/vrm-c/vrm-specification/blob/master/specification/VRMC_springBone-1.0/schema/VRMC_springBone.schema.json
struct VRMC_springBone : Extension<u8"VRMC_springBone">
{
  VRMC_springBone(const tree::NodePtr& json)
    : Extension(json)
    , Colliders(json)
    , ColliderGroups(json)
    , Springs(json)
  {
  }
  auto SpecVersionString() { return m_string<u8"specVersion">(); }
  JsonArray<SpringCollider, u8"colliders"> Colliders;
  JsonArray<SpringColliderGroup, u8"colliderGroups"> ColliderGroups;
  JsonArray<Spring, u8"springs"> Springs;
};

// https://github.com/vrm-c/vrm-specification/blob/master/specification/VRMC_node_constraint-1.0/schema/VRMC_node_constraint.rollConstraint.schema.json
struct ConstraintRoll : JsonObject
{
  using JsonObject::JsonObject;
  auto SourceId() { return m_id<u8"source">(); }
  auto RollAxisString() { return m_string<u8"rollAxis">(); }
  auto Weight() { return m_ptr<float, u8"weight">(); }
};

// https://github.com/vrm-c/vrm-specification/blob/master/specification/VRMC_node_constraint-1.0/schema/VRMC_node_constraint.aimConstraint.schema.json
struct ConstraintAim : JsonObject
{
  using JsonObject::JsonObject;
  auto SourceId() { return m_id<u8"source">(); }
  auto AimAxisString() { return m_string<u8"AimAxis">(); }
  auto Weight() { return m_ptr<float, u8"weight">(); }
};

// https://github.com/vrm-c/vrm-specification/blob/master/specification/VRMC_node_constraint-1.0/schema/VRMC_node_constraint.rotationConstraint.schema.json
struct ConstraintRotation : JsonObject
{
  using JsonObject::JsonObject;
  auto SourceId() { return m_id<u8"source">(); }
  auto Weight() { return m_ptr<float, u8"weight">(); }
};

// https://github.com/vrm-c/vrm-specification/blob/master/specification/VRMC_node_constraint-1.0/schema/VRMC_node_constraint.constraint.schema.json
struct Constraint : JsonObject
{
  using JsonObject::JsonObject;
  auto Roll() { return m_object<ConstraintRoll, u8"roll">(); }
  auto Aim() { return m_object<ConstraintAim, u8"aim">(); }
  auto Rotation() { return m_object<ConstraintRotation, u8"rotation">(); }
};

// https://github.com/vrm-c/vrm-specification/blob/master/specification/VRMC_node_constraint-1.0/schema/VRMC_node_constraint.schema.json
struct VRMC_node_constraint : Extension<u8"VRMC_node_constraint">
{
  using Extension::Extension;
  auto SpecVersionString() { return m_string<u8"specVersion">(); }
  auto Constraint() { return m_object<vrm1::Constraint, u8"constraint">(); }
};

inline std::u8string
GetHumanBoneName(Root root, uint32_t i)
{
  if (auto vrm = root.GetExtension<VRMC_vrm>()) {
    if (auto humanoid = vrm->Humanoid()) {
      if (auto humanbones = humanoid->HumanBones()) {
        if (auto obj = humanbones->m_json->Object()) {
          for (auto kv : *obj) {
            if (auto node = kv.second->Get(u8"node")) {
              if (auto p = node->Ptr<float>()) {
                if (*p == i) {
                  return kv.first;
                }
              }
            }
          }
        }
      }
    }
  }
  return {};
}

// https://github.com/vrm-c/vrm-specification/blob/master/specification/VRMC_vrm_animation-1.0/schema/VRMC_vrm_animation.schema.json
struct VRMC_vrm_animation : Extension<u8"VRMC_vrm_animation">
{
  using Extension::Extension;

  auto SpecVersionString() { return m_string<u8"specVersion">(); }
  auto Humanoid() { return m_object<vrm1::Humanoid, u8"humanoid">(); }
  auto Expressions() { return m_ptr<tree::ObjectValue, u8"expressions">(); }
  auto LookAt() { return m_ptr<tree::ObjectValue, u8"lookAt">(); }
};

} // namespace
} // namespace
