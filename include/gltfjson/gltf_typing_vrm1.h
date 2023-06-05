#pragma once
#include "gltf_typing.h"

namespace gltfjson {
namespace vrm1 {

// https://github.com/vrm-c/vrm-specification/blob/master/specification/VRMC_vrm-1.0/schema/VRMC_vrm.meta.schema.json
struct Meta : JsonObject
{
  using JsonObject::JsonObject;

  auto Name() { return m_string<u8"name">(); }
  auto Version() { return m_string<u8"version">(); }
  auto Authors() { return m_ptr<tree::ArrayValue, u8"authors">(); }
  auto CopyrightInformation() { return m_string<u8"copyrightInformation">(); }
  auto ContactInformation() { return m_string<u8"contactInformation">(); }
  auto References() { return m_ptr<tree::ArrayValue, u8"references">(); }
  auto ThirdPartyLicenses() { return m_string<u8"thirdPartyLicenses">(); }
  auto ThumbnailImage() { return m_id<u8"thumbnailImage">(); }
  auto LicenseUrl() { return m_string<u8"licenseUrl">(); }
  auto AvatarPermission() { return m_string<u8"avatarPermission">(); }
  auto AllowExcessivelyViolentUsage()
  {
    return m_ptr<bool, u8"allowExcessivelyViolentUsage">();
  }
  auto AllowExcessivelySexualUsage()
  {
    return m_ptr<bool, u8"allowExcessivelySexualUsage">();
  }
  auto CommercialUsage() { return m_string<u8"commercialUsage">(); }
  auto AllowPoliticalOrReligiousUsage()
  {
    return m_ptr<bool, u8"allowPoliticalOrReligiousUsage">();
  }
  auto AllowAntisocialOrHateUsage()
  {
    return m_ptr<bool, u8"allowAntisocialOrHateUsage">();
  }
  auto CreditNotation() { return m_string<u8"creditNotation">(); }
  auto AllowRedistribution() { return m_ptr<bool, u8"allowRedistribution">(); }
  auto Modification() { return m_string<u8"modification">(); }
  auto OtherLicenseUrl() { return m_string<u8"otherLicenseUrl">(); }
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

struct ExpressionPreset : JsonObject
{
  using JsonObject::JsonObject;

  auto Happy() { return m_ptr<tree::ObjectValue, u8"happy">(); }
  auto Angry() { return m_ptr<tree::ObjectValue, u8"angry">(); }
  auto Sad() { return m_ptr<tree::ObjectValue, u8"sad">(); }
  auto Relaxed() { return m_ptr<tree::ObjectValue, u8"relaxed">(); }
  auto Surprised() { return m_ptr<tree::ObjectValue, u8"surprised">(); }
  auto Aa() { return m_ptr<tree::ObjectValue, u8"aa">(); }
  auto Ih() { return m_ptr<tree::ObjectValue, u8"ih">(); }
  auto Ou() { return m_ptr<tree::ObjectValue, u8"ou">(); }
  auto Ee() { return m_ptr<tree::ObjectValue, u8"ee">(); }
  auto Oh() { return m_ptr<tree::ObjectValue, u8"oh">(); }
  auto Blink() { return m_ptr<tree::ObjectValue, u8"blink">(); }
  auto BlinkLeft() { return m_ptr<tree::ObjectValue, u8"blinkLeft">(); }
  auto BlinkRight() { return m_ptr<tree::ObjectValue, u8"blinkRight">(); }
  auto LookUp() { return m_ptr<tree::ObjectValue, u8"lookUp">(); }
  auto LookDown() { return m_ptr<tree::ObjectValue, u8"lookDown">(); }
  auto LookLeft() { return m_ptr<tree::ObjectValue, u8"lookLeft">(); }
  auto LookRight() { return m_ptr<tree::ObjectValue, u8"lookRight">(); }
  auto Neutral() { return m_ptr<tree::ObjectValue, u8"neutral">(); }
};

// https://github.com/vrm-c/vrm-specification/blob/master/specification/VRMC_vrm-1.0/schema/VRMC_vrm.lookAt.schema.json
struct LookAt : JsonObject
{
  auto Type() { return m_string<u8"type">(); }
};

// https://github.com/vrm-c/vrm-specification/blob/master/specification/VRMC_vrm-1.0/schema/VRMC_vrm.firstPerson.meshAnnotation.schema.json
struct MeshAnnotation : JsonObject
{
  using JsonObject::JsonObject;

  auto Node() { return m_id<u8"node">(); }
  auto Type() { return m_string<u8"type">(); }
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

  auto SpecVersion() { return m_string<u8"specVersion">(); }
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

// https://github.com/vrm-c/vrm-specification/blob/master/specification/VRMC_springBone-1.0/schema/VRMC_springBone.schema.json
struct VRMC_springBone : Extension<u8"VRMC_springBone">
{
  using Extension::Extension;

  auto SpecVersion() { return m_string<u8"specVersion">(); }
};

// https://github.com/vrm-c/vrm-specification/blob/master/specification/VRMC_node_constraint-1.0/schema/VRMC_node_constraint.schema.json
struct VRMC_node_constraint : Extension<u8"VRMC_node_constraint">
{
  using Extension::Extension;
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

} // namespace
} // namespace
