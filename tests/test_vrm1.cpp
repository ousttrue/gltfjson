#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <gltfjson.h>
#include <gltfjson/gltf_typing_vrm1.h>
#include <gtest/gtest.h>
#include <iostream>

std::filesystem::path static get_path(std::string_view relative)
{
  std::filesystem::path base = std::getenv("VRM_SAMPLES");
  return base / relative;
}

TEST(Vrm1, SeedSan)
{
  auto path = get_path("Seed-san/vrm/Seed-san.vrm");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
    return;
  }

  auto glb = gltfjson::FromPath(path);
  EXPECT_TRUE(glb);

  auto &root = glb->Root;
  auto extensions = root.Extensions();
  EXPECT_TRUE(extensions);
  auto extension = extensions->Get(u8"VRMC_vrm");
  EXPECT_TRUE(extension);

  {
    // VRMC_vrm
    gltfjson::vrm1::VRMC_vrm vrm(extension);
    EXPECT_EQ(u8"1.0-beta", vrm.SpecVersionString());

    // meta
    auto meta = vrm.Meta();
    EXPECT_TRUE(meta);
    EXPECT_EQ(u8"Seed-san", meta->NameString());

    // humanoid
    auto humanoid = vrm.Humanoid();
    EXPECT_TRUE(humanoid);
    auto humanBones = humanoid->HumanBones();
    EXPECT_TRUE(humanBones);
    EXPECT_TRUE(humanBones->Hips());

    // lookat
    auto lookat = vrm.LookAt();
    EXPECT_TRUE(lookat);
    EXPECT_EQ(u8"expression", lookat->TypeString());

    // firstperson
    auto firstPerson = vrm.FirstPerson();
    EXPECT_TRUE(firstPerson);
    auto& annotations = firstPerson->MeshAnnotations;
    EXPECT_EQ(5, annotations.size());

    // expression
    auto expressions = vrm.Expressions();
    EXPECT_TRUE(expressions);
    auto preset = expressions->Preset();
    EXPECT_TRUE(preset);
    EXPECT_TRUE(preset->Happy());
  }

  {
    // VRMC_materials_mtoon
    EXPECT_EQ(17, root.Materials.size());
    auto material = root.Materials[0];
    auto mtoon = material.GetExtension<gltfjson::vrm1::VRMC_materials_mtoon>();
    EXPECT_TRUE(mtoon);
    EXPECT_TRUE(mtoon->ShadeMultiplyTexture());
  }

  {
    // spring
    auto spring = root.GetExtension<gltfjson::vrm1::VRMC_springBone>();
    EXPECT_TRUE(spring);
    // auto springMaster = vrm.Spring();
    // auto& springs = springMaster->Springs;
    // EXPECT_EQ(3, springs.size());
    // auto& colliderGroups = springMaster->ColliderGroups;
    // EXPECT_EQ(6, colliderGroups.size());
  }

  {
    // constraint
    EXPECT_EQ(147, root.Nodes.size());
    auto node = root.Nodes[21];
    auto constraint = node.GetExtension<gltfjson::vrm1::VRMC_node_constraint>();
    EXPECT_TRUE(constraint);
  }
}
