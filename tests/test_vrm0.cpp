#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <gltfjson.h>
#include <gltfjson/gltf_typing_vrm0.h>
#include <gtest/gtest.h>
#include <iostream>

TEST(Vrm0, Alicia)
{
  std::filesystem::path path(
    "../UniVRM/Tests/Models/Alicia_vrm-0.51/AliciaSolid_vrm-0.51.vrm");

  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
    return;
  }

  auto parsed = gltfjson::FromPath(path);
  EXPECT_TRUE(parsed);

  auto &root = parsed->Root;
  auto extensions = root.Extensions();
  EXPECT_TRUE(extensions);
  auto extension = extensions->Get(u8"VRM");
  EXPECT_TRUE(extension);

  gltfjson::vrm0::VRM vrm(extension);
  EXPECT_EQ(u8"UniVRM-0.51.0", vrm.ExporterVersionString());

  // meta
  auto meta = vrm.Meta();
  EXPECT_TRUE(meta);
  EXPECT_EQ(u8"Alicia Solid", meta->TitleString());

  // humanoid
  auto humanoid = vrm.Humanoid();
  EXPECT_TRUE(humanoid);
  auto& humanBones = humanoid->HumanBones;
  EXPECT_EQ(55, humanBones.size());
  auto hips = humanBones[0];
  EXPECT_EQ(u8"hips", hips.BoneString());

  // mtoon
  auto& mtoons = vrm.MaterialProperties;
  EXPECT_EQ(12, mtoons.size());
  auto mtoon = mtoons[0];
  EXPECT_EQ(u8"Alicia_body", mtoon.NameString());

  // blendshape
  auto blendShapeMaster = vrm.BlendShapeMaster();
  EXPECT_TRUE(blendShapeMaster);
  auto& blendshapes = blendShapeMaster->BlendShapeGroups;
  EXPECT_EQ(17, blendshapes.size());

  // spring
  auto springMaster = vrm.Spring();
  auto& springs = springMaster->Springs;
  EXPECT_EQ(3, springs.size());
  auto& colliderGroups = springMaster->ColliderGroups;
  EXPECT_EQ(6, colliderGroups.size());

  // lookat / firstperson
  auto firstPerson = vrm.FirstPerson();
  EXPECT_TRUE(firstPerson);
  EXPECT_EQ(u8"Bone", firstPerson->LookAtTypeString());
  auto& annotations = firstPerson->MeshAnnotations;
  EXPECT_EQ(12, annotations.size());
}
