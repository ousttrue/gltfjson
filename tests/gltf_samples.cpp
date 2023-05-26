#include <cstdlib>
#include <gtest/gtest.h>
#include <gltfjson.h>

std::filesystem::path get_path(std::string_view relative) {
  std::filesystem::path base = std::getenv("GLTF_SAMPLE_MODELS");
  return base / "2.0" / relative;
}

static std::vector<uint8_t>
ReadAllBytes(const std::filesystem::path& filename)
{
  std::ifstream ifs(filename, std::ios::binary | std::ios::ate);
  if (!ifs) {
    return {};
  }
  auto pos = ifs.tellg();
  std::vector<uint8_t> buffer(pos);
  ifs.seekg(0, std::ios::beg);
  ifs.read((char*)buffer.data(), pos);
  return buffer;
}

TEST(GltfSamples, 2CylinderEngine_glTF) {
  auto path = get_path("2CylinderEngine/glTF/2CylinderEngine.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, 2CylinderEngine_glTF_Binary) {
  auto path = get_path("2CylinderEngine/glTF-Binary/2CylinderEngine.glb");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, 2CylinderEngine_glTF_Draco) {
  auto path = get_path("2CylinderEngine/glTF-Draco/2CylinderEngine.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, 2CylinderEngine_glTF_Embedded) {
  auto path = get_path("2CylinderEngine/glTF-Embedded/2CylinderEngine.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, ABeautifulGame_glTF) {
  auto path = get_path("ABeautifulGame/glTF/ABeautifulGame.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, AlphaBlendModeTest_glTF) {
  auto path = get_path("AlphaBlendModeTest/glTF/AlphaBlendModeTest.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, AlphaBlendModeTest_glTF_Binary) {
  auto path = get_path("AlphaBlendModeTest/glTF-Binary/AlphaBlendModeTest.glb");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, AlphaBlendModeTest_glTF_Embedded) {
  auto path = get_path("AlphaBlendModeTest/glTF-Embedded/AlphaBlendModeTest.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, AnimatedCube_glTF) {
  auto path = get_path("AnimatedCube/glTF/AnimatedCube.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, AnimatedMorphCube_glTF) {
  auto path = get_path("AnimatedMorphCube/glTF/AnimatedMorphCube.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, AnimatedMorphCube_glTF_Binary) {
  auto path = get_path("AnimatedMorphCube/glTF-Binary/AnimatedMorphCube.glb");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, AnimatedMorphCube_glTF_Quantized) {
  auto path = get_path("AnimatedMorphCube/glTF-Quantized/AnimatedMorphCube.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, AnimatedMorphSphere_glTF) {
  auto path = get_path("AnimatedMorphSphere/glTF/AnimatedMorphSphere.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, AnimatedMorphSphere_glTF_Binary) {
  auto path = get_path("AnimatedMorphSphere/glTF-Binary/AnimatedMorphSphere.glb");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, AnimatedTriangle_glTF) {
  auto path = get_path("AnimatedTriangle/glTF/AnimatedTriangle.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, AnimatedTriangle_glTF_Embedded) {
  auto path = get_path("AnimatedTriangle/glTF-Embedded/AnimatedTriangle.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, AntiqueCamera_glTF) {
  auto path = get_path("AntiqueCamera/glTF/AntiqueCamera.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, AntiqueCamera_glTF_Binary) {
  auto path = get_path("AntiqueCamera/glTF-Binary/AntiqueCamera.glb");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, AttenuationTest_glTF) {
  auto path = get_path("AttenuationTest/glTF/AttenuationTest.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, AttenuationTest_glTF_Binary) {
  auto path = get_path("AttenuationTest/glTF-Binary/AttenuationTest.glb");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, Avocado_glTF) {
  auto path = get_path("Avocado/glTF/Avocado.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, Avocado_glTF_Binary) {
  auto path = get_path("Avocado/glTF-Binary/Avocado.glb");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, Avocado_glTF_Draco) {
  auto path = get_path("Avocado/glTF-Draco/Avocado.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, Avocado_glTF_Quantized) {
  auto path = get_path("Avocado/glTF-Quantized/Avocado.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, BarramundiFish_glTF) {
  auto path = get_path("BarramundiFish/glTF/BarramundiFish.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, BarramundiFish_glTF_Binary) {
  auto path = get_path("BarramundiFish/glTF-Binary/BarramundiFish.glb");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, BarramundiFish_glTF_Draco) {
  auto path = get_path("BarramundiFish/glTF-Draco/BarramundiFish.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, BoomBox_glTF) {
  auto path = get_path("BoomBox/glTF/BoomBox.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, BoomBox_glTF_Binary) {
  auto path = get_path("BoomBox/glTF-Binary/BoomBox.glb");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, BoomBox_glTF_Draco) {
  auto path = get_path("BoomBox/glTF-Draco/BoomBox.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, BoomBoxWithAxes_glTF) {
  auto path = get_path("BoomBoxWithAxes/glTF/BoomBoxWithAxes.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, Box_glTF) {
  auto path = get_path("Box/glTF/Box.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, Box_glTF_Binary) {
  auto path = get_path("Box/glTF-Binary/Box.glb");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, Box_glTF_Draco) {
  auto path = get_path("Box/glTF-Draco/Box.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, Box_glTF_Embedded) {
  auto path = get_path("Box/glTF-Embedded/Box.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, Box_With_Spaces_glTF) {
  auto path = get_path("Box With Spaces/glTF/Box With Spaces.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, BoxAnimated_glTF) {
  auto path = get_path("BoxAnimated/glTF/BoxAnimated.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, BoxAnimated_glTF_Binary) {
  auto path = get_path("BoxAnimated/glTF-Binary/BoxAnimated.glb");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, BoxAnimated_glTF_Embedded) {
  auto path = get_path("BoxAnimated/glTF-Embedded/BoxAnimated.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, BoxInterleaved_glTF) {
  auto path = get_path("BoxInterleaved/glTF/BoxInterleaved.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, BoxInterleaved_glTF_Binary) {
  auto path = get_path("BoxInterleaved/glTF-Binary/BoxInterleaved.glb");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, BoxInterleaved_glTF_Embedded) {
  auto path = get_path("BoxInterleaved/glTF-Embedded/BoxInterleaved.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, BoxTextured_glTF) {
  auto path = get_path("BoxTextured/glTF/BoxTextured.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, BoxTextured_glTF_Binary) {
  auto path = get_path("BoxTextured/glTF-Binary/BoxTextured.glb");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, BoxTextured_glTF_Embedded) {
  auto path = get_path("BoxTextured/glTF-Embedded/BoxTextured.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, BoxTexturedNonPowerOfTwo_glTF) {
  auto path = get_path("BoxTexturedNonPowerOfTwo/glTF/BoxTexturedNonPowerOfTwo.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, BoxTexturedNonPowerOfTwo_glTF_Binary) {
  auto path = get_path("BoxTexturedNonPowerOfTwo/glTF-Binary/BoxTexturedNonPowerOfTwo.glb");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, BoxTexturedNonPowerOfTwo_glTF_Embedded) {
  auto path = get_path("BoxTexturedNonPowerOfTwo/glTF-Embedded/BoxTexturedNonPowerOfTwo.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, BoxVertexColors_glTF) {
  auto path = get_path("BoxVertexColors/glTF/BoxVertexColors.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, BoxVertexColors_glTF_Binary) {
  auto path = get_path("BoxVertexColors/glTF-Binary/BoxVertexColors.glb");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, BoxVertexColors_glTF_Embedded) {
  auto path = get_path("BoxVertexColors/glTF-Embedded/BoxVertexColors.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, BrainStem_glTF) {
  auto path = get_path("BrainStem/glTF/BrainStem.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, BrainStem_glTF_Binary) {
  auto path = get_path("BrainStem/glTF-Binary/BrainStem.glb");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, BrainStem_glTF_Draco) {
  auto path = get_path("BrainStem/glTF-Draco/BrainStem.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, BrainStem_glTF_Embedded) {
  auto path = get_path("BrainStem/glTF-Embedded/BrainStem.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, BrainStem_glTF_Meshopt) {
  auto path = get_path("BrainStem/glTF-Meshopt/BrainStem.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, Buggy_glTF) {
  auto path = get_path("Buggy/glTF/Buggy.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, Buggy_glTF_Binary) {
  auto path = get_path("Buggy/glTF-Binary/Buggy.glb");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, Buggy_glTF_Draco) {
  auto path = get_path("Buggy/glTF-Draco/Buggy.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, Buggy_glTF_Embedded) {
  auto path = get_path("Buggy/glTF-Embedded/Buggy.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, Cameras_glTF) {
  auto path = get_path("Cameras/glTF/Cameras.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, Cameras_glTF_Embedded) {
  auto path = get_path("Cameras/glTF-Embedded/Cameras.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, CesiumMan_glTF) {
  auto path = get_path("CesiumMan/glTF/CesiumMan.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, CesiumMan_glTF_Binary) {
  auto path = get_path("CesiumMan/glTF-Binary/CesiumMan.glb");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, CesiumMan_glTF_Draco) {
  auto path = get_path("CesiumMan/glTF-Draco/CesiumMan.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, CesiumMan_glTF_Embedded) {
  auto path = get_path("CesiumMan/glTF-Embedded/CesiumMan.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, CesiumMilkTruck_glTF) {
  auto path = get_path("CesiumMilkTruck/glTF/CesiumMilkTruck.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, CesiumMilkTruck_glTF_Binary) {
  auto path = get_path("CesiumMilkTruck/glTF-Binary/CesiumMilkTruck.glb");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, CesiumMilkTruck_glTF_Draco) {
  auto path = get_path("CesiumMilkTruck/glTF-Draco/CesiumMilkTruck.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, CesiumMilkTruck_glTF_Embedded) {
  auto path = get_path("CesiumMilkTruck/glTF-Embedded/CesiumMilkTruck.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, ClearCoatCarPaint_glTF) {
  auto path = get_path("ClearCoatCarPaint/glTF/ClearCoatCarPaint.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, ClearCoatCarPaint_glTF_Binary) {
  auto path = get_path("ClearCoatCarPaint/glTF-Binary/ClearCoatCarPaint.glb");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, ClearCoatTest_glTF) {
  auto path = get_path("ClearCoatTest/glTF/ClearCoatTest.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, ClearCoatTest_glTF_Binary) {
  auto path = get_path("ClearCoatTest/glTF-Binary/ClearCoatTest.glb");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, ClearcoatWicker_glTF) {
  auto path = get_path("ClearcoatWicker/glTF/ClearcoatWicker.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, ClearcoatWicker_glTF_Binary) {
  auto path = get_path("ClearcoatWicker/glTF-Binary/ClearcoatWicker.glb");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, Corset_glTF) {
  auto path = get_path("Corset/glTF/Corset.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, Corset_glTF_Binary) {
  auto path = get_path("Corset/glTF-Binary/Corset.glb");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, Corset_glTF_Draco) {
  auto path = get_path("Corset/glTF-Draco/Corset.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, Cube_glTF) {
  auto path = get_path("Cube/glTF/Cube.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, DamagedHelmet_glTF) {
  auto path = get_path("DamagedHelmet/glTF/DamagedHelmet.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, DamagedHelmet_glTF_Binary) {
  auto path = get_path("DamagedHelmet/glTF-Binary/DamagedHelmet.glb");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, DamagedHelmet_glTF_Embedded) {
  auto path = get_path("DamagedHelmet/glTF-Embedded/DamagedHelmet.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, DragonAttenuation_glTF) {
  auto path = get_path("DragonAttenuation/glTF/DragonAttenuation.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, DragonAttenuation_glTF_Binary) {
  auto path = get_path("DragonAttenuation/glTF-Binary/DragonAttenuation.glb");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, DragonAttenuation_glTF_Meshopt) {
  auto path = get_path("DragonAttenuation/glTF-Meshopt/DragonAttenuation.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, Duck_glTF) {
  auto path = get_path("Duck/glTF/Duck.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, Duck_glTF_Binary) {
  auto path = get_path("Duck/glTF-Binary/Duck.glb");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, Duck_glTF_Draco) {
  auto path = get_path("Duck/glTF-Draco/Duck.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, Duck_glTF_Embedded) {
  auto path = get_path("Duck/glTF-Embedded/Duck.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, Duck_glTF_Quantized) {
  auto path = get_path("Duck/glTF-Quantized/Duck.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, EmissiveStrengthTest_glTF) {
  auto path = get_path("EmissiveStrengthTest/glTF/EmissiveStrengthTest.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, EmissiveStrengthTest_glTF_Binary) {
  auto path = get_path("EmissiveStrengthTest/glTF-Binary/EmissiveStrengthTest.glb");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, EnvironmentTest_glTF) {
  auto path = get_path("EnvironmentTest/glTF/EnvironmentTest.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, EnvironmentTest_glTF_IBL) {
  auto path = get_path("EnvironmentTest/glTF-IBL/EnvironmentTest.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, FlightHelmet_glTF) {
  auto path = get_path("FlightHelmet/glTF/FlightHelmet.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, Fox_glTF) {
  auto path = get_path("Fox/glTF/Fox.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, Fox_glTF_Binary) {
  auto path = get_path("Fox/glTF-Binary/Fox.glb");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, GearboxAssy_glTF) {
  auto path = get_path("GearboxAssy/glTF/GearboxAssy.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, GearboxAssy_glTF_Binary) {
  auto path = get_path("GearboxAssy/glTF-Binary/GearboxAssy.glb");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, GearboxAssy_glTF_Draco) {
  auto path = get_path("GearboxAssy/glTF-Draco/GearboxAssy.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, GearboxAssy_glTF_Embedded) {
  auto path = get_path("GearboxAssy/glTF-Embedded/GearboxAssy.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, GlamVelvetSofa_glTF) {
  auto path = get_path("GlamVelvetSofa/glTF/GlamVelvetSofa.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, GlamVelvetSofa_glTF_Binary) {
  auto path = get_path("GlamVelvetSofa/glTF-Binary/GlamVelvetSofa.glb");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, InterpolationTest_glTF) {
  auto path = get_path("InterpolationTest/glTF/InterpolationTest.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, InterpolationTest_glTF_Binary) {
  auto path = get_path("InterpolationTest/glTF-Binary/InterpolationTest.glb");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, IridescenceDielectricSpheres_glTF) {
  auto path = get_path("IridescenceDielectricSpheres/glTF/IridescenceDielectricSpheres.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, IridescenceLamp_glTF) {
  auto path = get_path("IridescenceLamp/glTF/IridescenceLamp.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, IridescenceLamp_glTF_Binary) {
  auto path = get_path("IridescenceLamp/glTF-Binary/IridescenceLamp.glb");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, IridescenceMetallicSpheres_glTF) {
  auto path = get_path("IridescenceMetallicSpheres/glTF/IridescenceMetallicSpheres.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, IridescenceSuzanne_glTF) {
  auto path = get_path("IridescenceSuzanne/glTF/IridescenceSuzanne.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, IridescenceSuzanne_glTF_Binary) {
  auto path = get_path("IridescenceSuzanne/glTF-Binary/IridescenceSuzanne.glb");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, IridescentDishWithOlives_glTF) {
  auto path = get_path("IridescentDishWithOlives/glTF/IridescentDishWithOlives.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, IridescentDishWithOlives_glTF_Binary) {
  auto path = get_path("IridescentDishWithOlives/glTF-Binary/IridescentDishWithOlives.glb");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, Lantern_glTF) {
  auto path = get_path("Lantern/glTF/Lantern.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, Lantern_glTF_Binary) {
  auto path = get_path("Lantern/glTF-Binary/Lantern.glb");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, Lantern_glTF_Draco) {
  auto path = get_path("Lantern/glTF-Draco/Lantern.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, Lantern_glTF_Quantized) {
  auto path = get_path("Lantern/glTF-Quantized/Lantern.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, LightsPunctualLamp_glTF) {
  auto path = get_path("LightsPunctualLamp/glTF/LightsPunctualLamp.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, LightsPunctualLamp_glTF_Binary) {
  auto path = get_path("LightsPunctualLamp/glTF-Binary/LightsPunctualLamp.glb");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, MaterialsVariantsShoe_glTF) {
  auto path = get_path("MaterialsVariantsShoe/glTF/MaterialsVariantsShoe.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, MaterialsVariantsShoe_glTF_Binary) {
  auto path = get_path("MaterialsVariantsShoe/glTF-Binary/MaterialsVariantsShoe.glb");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, MeshPrimitiveModes_glTF) {
  auto path = get_path("MeshPrimitiveModes/glTF/MeshPrimitiveModes.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, MeshPrimitiveModes_glTF_Embedded) {
  auto path = get_path("MeshPrimitiveModes/glTF-Embedded/MeshPrimitiveModes.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, MetalRoughSpheres_glTF) {
  auto path = get_path("MetalRoughSpheres/glTF/MetalRoughSpheres.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, MetalRoughSpheres_glTF_Binary) {
  auto path = get_path("MetalRoughSpheres/glTF-Binary/MetalRoughSpheres.glb");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, MetalRoughSpheres_glTF_Embedded) {
  auto path = get_path("MetalRoughSpheres/glTF-Embedded/MetalRoughSpheres.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, MetalRoughSpheresNoTextures_glTF) {
  auto path = get_path("MetalRoughSpheresNoTextures/glTF/MetalRoughSpheresNoTextures.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, MetalRoughSpheresNoTextures_glTF_Binary) {
  auto path = get_path("MetalRoughSpheresNoTextures/glTF-Binary/MetalRoughSpheresNoTextures.glb");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, MorphPrimitivesTest_glTF) {
  auto path = get_path("MorphPrimitivesTest/glTF/MorphPrimitivesTest.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, MorphPrimitivesTest_glTF_Binary) {
  auto path = get_path("MorphPrimitivesTest/glTF-Binary/MorphPrimitivesTest.glb");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, MorphPrimitivesTest_glTF_Draco) {
  auto path = get_path("MorphPrimitivesTest/glTF-Draco/MorphPrimitivesTest.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, MorphStressTest_glTF) {
  auto path = get_path("MorphStressTest/glTF/MorphStressTest.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, MorphStressTest_glTF_Binary) {
  auto path = get_path("MorphStressTest/glTF-Binary/MorphStressTest.glb");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, MosquitoInAmber_glTF) {
  auto path = get_path("MosquitoInAmber/glTF/MosquitoInAmber.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, MosquitoInAmber_glTF_Binary) {
  auto path = get_path("MosquitoInAmber/glTF-Binary/MosquitoInAmber.glb");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, MultipleScenes_glTF) {
  auto path = get_path("MultipleScenes/glTF/MultipleScenes.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, MultipleScenes_glTF_Embedded) {
  auto path = get_path("MultipleScenes/glTF-Embedded/MultipleScenes.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, MultiUVTest_glTF) {
  auto path = get_path("MultiUVTest/glTF/MultiUVTest.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, MultiUVTest_glTF_Binary) {
  auto path = get_path("MultiUVTest/glTF-Binary/MultiUVTest.glb");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, MultiUVTest_glTF_Embedded) {
  auto path = get_path("MultiUVTest/glTF-Embedded/MultiUVTest.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, NegativeScaleTest_glTF) {
  auto path = get_path("NegativeScaleTest/glTF/NegativeScaleTest.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, NegativeScaleTest_glTF_Binary) {
  auto path = get_path("NegativeScaleTest/glTF-Binary/NegativeScaleTest.glb");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, NormalTangentMirrorTest_glTF) {
  auto path = get_path("NormalTangentMirrorTest/glTF/NormalTangentMirrorTest.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, NormalTangentMirrorTest_glTF_Binary) {
  auto path = get_path("NormalTangentMirrorTest/glTF-Binary/NormalTangentMirrorTest.glb");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, NormalTangentMirrorTest_glTF_Embedded) {
  auto path = get_path("NormalTangentMirrorTest/glTF-Embedded/NormalTangentMirrorTest.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, NormalTangentTest_glTF) {
  auto path = get_path("NormalTangentTest/glTF/NormalTangentTest.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, NormalTangentTest_glTF_Binary) {
  auto path = get_path("NormalTangentTest/glTF-Binary/NormalTangentTest.glb");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, NormalTangentTest_glTF_Embedded) {
  auto path = get_path("NormalTangentTest/glTF-Embedded/NormalTangentTest.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, OrientationTest_glTF) {
  auto path = get_path("OrientationTest/glTF/OrientationTest.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, OrientationTest_glTF_Binary) {
  auto path = get_path("OrientationTest/glTF-Binary/OrientationTest.glb");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, OrientationTest_glTF_Embedded) {
  auto path = get_path("OrientationTest/glTF-Embedded/OrientationTest.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, ReciprocatingSaw_glTF) {
  auto path = get_path("ReciprocatingSaw/glTF/ReciprocatingSaw.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, ReciprocatingSaw_glTF_Binary) {
  auto path = get_path("ReciprocatingSaw/glTF-Binary/ReciprocatingSaw.glb");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, ReciprocatingSaw_glTF_Draco) {
  auto path = get_path("ReciprocatingSaw/glTF-Draco/ReciprocatingSaw.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, ReciprocatingSaw_glTF_Embedded) {
  auto path = get_path("ReciprocatingSaw/glTF-Embedded/ReciprocatingSaw.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, RecursiveSkeletons_glTF) {
  auto path = get_path("RecursiveSkeletons/glTF/RecursiveSkeletons.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, RecursiveSkeletons_glTF_Binary) {
  auto path = get_path("RecursiveSkeletons/glTF-Binary/RecursiveSkeletons.glb");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, RiggedFigure_glTF) {
  auto path = get_path("RiggedFigure/glTF/RiggedFigure.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, RiggedFigure_glTF_Binary) {
  auto path = get_path("RiggedFigure/glTF-Binary/RiggedFigure.glb");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, RiggedFigure_glTF_Draco) {
  auto path = get_path("RiggedFigure/glTF-Draco/RiggedFigure.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, RiggedFigure_glTF_Embedded) {
  auto path = get_path("RiggedFigure/glTF-Embedded/RiggedFigure.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, RiggedSimple_glTF) {
  auto path = get_path("RiggedSimple/glTF/RiggedSimple.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, RiggedSimple_glTF_Binary) {
  auto path = get_path("RiggedSimple/glTF-Binary/RiggedSimple.glb");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, RiggedSimple_glTF_Draco) {
  auto path = get_path("RiggedSimple/glTF-Draco/RiggedSimple.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, RiggedSimple_glTF_Embedded) {
  auto path = get_path("RiggedSimple/glTF-Embedded/RiggedSimple.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, SciFiHelmet_glTF) {
  auto path = get_path("SciFiHelmet/glTF/SciFiHelmet.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, SheenChair_glTF) {
  auto path = get_path("SheenChair/glTF/SheenChair.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, SheenChair_glTF_Binary) {
  auto path = get_path("SheenChair/glTF-Binary/SheenChair.glb");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, SheenCloth_glTF) {
  auto path = get_path("SheenCloth/glTF/SheenCloth.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, SimpleInstancing_glTF) {
  auto path = get_path("SimpleInstancing/glTF/SimpleInstancing.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, SimpleInstancing_glTF_Binary) {
  auto path = get_path("SimpleInstancing/glTF-Binary/SimpleInstancing.glb");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, SimpleMeshes_glTF) {
  auto path = get_path("SimpleMeshes/glTF/SimpleMeshes.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, SimpleMeshes_glTF_Embedded) {
  auto path = get_path("SimpleMeshes/glTF-Embedded/SimpleMeshes.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, SimpleMorph_glTF) {
  auto path = get_path("SimpleMorph/glTF/SimpleMorph.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, SimpleMorph_glTF_Embedded) {
  auto path = get_path("SimpleMorph/glTF-Embedded/SimpleMorph.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, SimpleSkin_glTF) {
  auto path = get_path("SimpleSkin/glTF/SimpleSkin.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, SimpleSkin_glTF_Embedded) {
  auto path = get_path("SimpleSkin/glTF-Embedded/SimpleSkin.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, SimpleSparseAccessor_glTF) {
  auto path = get_path("SimpleSparseAccessor/glTF/SimpleSparseAccessor.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, SimpleSparseAccessor_glTF_Embedded) {
  auto path = get_path("SimpleSparseAccessor/glTF-Embedded/SimpleSparseAccessor.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, SpecGlossVsMetalRough_glTF) {
  auto path = get_path("SpecGlossVsMetalRough/glTF/SpecGlossVsMetalRough.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, SpecGlossVsMetalRough_glTF_Binary) {
  auto path = get_path("SpecGlossVsMetalRough/glTF-Binary/SpecGlossVsMetalRough.glb");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, SpecularTest_glTF) {
  auto path = get_path("SpecularTest/glTF/SpecularTest.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, SpecularTest_glTF_Binary) {
  auto path = get_path("SpecularTest/glTF-Binary/SpecularTest.glb");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, Sponza_glTF) {
  auto path = get_path("Sponza/glTF/Sponza.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, StainedGlassLamp_glTF) {
  auto path = get_path("StainedGlassLamp/glTF/StainedGlassLamp.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, StainedGlassLamp_glTF_JPG_PNG) {
  auto path = get_path("StainedGlassLamp/glTF-JPG-PNG/StainedGlassLamp.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, StainedGlassLamp_glTF_KTX_BasisU) {
  auto path = get_path("StainedGlassLamp/glTF-KTX-BasisU/StainedGlassLamp.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, Suzanne_glTF) {
  auto path = get_path("Suzanne/glTF/Suzanne.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, TextureCoordinateTest_glTF) {
  auto path = get_path("TextureCoordinateTest/glTF/TextureCoordinateTest.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, TextureCoordinateTest_glTF_Binary) {
  auto path = get_path("TextureCoordinateTest/glTF-Binary/TextureCoordinateTest.glb");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, TextureCoordinateTest_glTF_Embedded) {
  auto path = get_path("TextureCoordinateTest/glTF-Embedded/TextureCoordinateTest.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, TextureEncodingTest_glTF) {
  auto path = get_path("TextureEncodingTest/glTF/TextureEncodingTest.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, TextureEncodingTest_glTF_Binary) {
  auto path = get_path("TextureEncodingTest/glTF-Binary/TextureEncodingTest.glb");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, TextureLinearInterpolationTest_glTF) {
  auto path = get_path("TextureLinearInterpolationTest/glTF/TextureLinearInterpolationTest.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, TextureLinearInterpolationTest_glTF_Binary) {
  auto path = get_path("TextureLinearInterpolationTest/glTF-Binary/TextureLinearInterpolationTest.glb");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, TextureSettingsTest_glTF) {
  auto path = get_path("TextureSettingsTest/glTF/TextureSettingsTest.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, TextureSettingsTest_glTF_Binary) {
  auto path = get_path("TextureSettingsTest/glTF-Binary/TextureSettingsTest.glb");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, TextureSettingsTest_glTF_Embedded) {
  auto path = get_path("TextureSettingsTest/glTF-Embedded/TextureSettingsTest.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, TextureTransformMultiTest_glTF) {
  auto path = get_path("TextureTransformMultiTest/glTF/TextureTransformMultiTest.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, TextureTransformMultiTest_glTF_Binary) {
  auto path = get_path("TextureTransformMultiTest/glTF-Binary/TextureTransformMultiTest.glb");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, TextureTransformTest_glTF) {
  auto path = get_path("TextureTransformTest/glTF/TextureTransformTest.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, ToyCar_glTF) {
  auto path = get_path("ToyCar/glTF/ToyCar.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, ToyCar_glTF_Binary) {
  auto path = get_path("ToyCar/glTF-Binary/ToyCar.glb");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, TransmissionRoughnessTest_glTF) {
  auto path = get_path("TransmissionRoughnessTest/glTF/TransmissionRoughnessTest.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, TransmissionRoughnessTest_glTF_Binary) {
  auto path = get_path("TransmissionRoughnessTest/glTF-Binary/TransmissionRoughnessTest.glb");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, TransmissionTest_glTF) {
  auto path = get_path("TransmissionTest/glTF/TransmissionTest.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, TransmissionTest_glTF_Binary) {
  auto path = get_path("TransmissionTest/glTF-Binary/TransmissionTest.glb");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, Triangle_glTF) {
  auto path = get_path("Triangle/glTF/Triangle.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, Triangle_glTF_Embedded) {
  auto path = get_path("Triangle/glTF-Embedded/Triangle.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, TriangleWithoutIndices_glTF) {
  auto path = get_path("TriangleWithoutIndices/glTF/TriangleWithoutIndices.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, TriangleWithoutIndices_glTF_Embedded) {
  auto path = get_path("TriangleWithoutIndices/glTF-Embedded/TriangleWithoutIndices.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, TwoSidedPlane_glTF) {
  auto path = get_path("TwoSidedPlane/glTF/TwoSidedPlane.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, UnlitTest_glTF) {
  auto path = get_path("UnlitTest/glTF/UnlitTest.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, UnlitTest_glTF_Binary) {
  auto path = get_path("UnlitTest/glTF-Binary/UnlitTest.glb");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, VC_glTF) {
  auto path = get_path("VC/glTF/VC.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, VC_glTF_Binary) {
  auto path = get_path("VC/glTF-Binary/VC.glb");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, VC_glTF_Draco) {
  auto path = get_path("VC/glTF-Draco/VC.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, VC_glTF_Embedded) {
  auto path = get_path("VC/glTF-Embedded/VC.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, VertexColorTest_glTF) {
  auto path = get_path("VertexColorTest/glTF/VertexColorTest.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, VertexColorTest_glTF_Binary) {
  auto path = get_path("VertexColorTest/glTF-Binary/VertexColorTest.glb");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, VertexColorTest_glTF_Embedded) {
  auto path = get_path("VertexColorTest/glTF-Embedded/VertexColorTest.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, WaterBottle_glTF) {
  auto path = get_path("WaterBottle/glTF/WaterBottle.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, WaterBottle_glTF_Binary) {
  auto path = get_path("WaterBottle/glTF-Binary/WaterBottle.glb");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, WaterBottle_glTF_Draco) {
  auto path = get_path("WaterBottle/glTF-Draco/WaterBottle.gltf");
  auto bytes = ReadAllBytes(path);
  if(path.extension()==".glb")
  {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  else{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}
