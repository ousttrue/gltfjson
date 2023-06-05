#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <gltfjson.h>
#include <gtest/gtest.h>

static std::filesystem::path
get_path(std::string_view relative)
{
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

TEST(GltfSamples, 2CylinderEngine_glTF)
{
  auto path = get_path("2CylinderEngine/glTF/2CylinderEngine.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, 2CylinderEngine_glTF_Binary)
{
  auto path = get_path("2CylinderEngine/glTF-Binary/2CylinderEngine.glb");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, 2CylinderEngine_glTF_Draco)
{
  auto path = get_path("2CylinderEngine/glTF-Draco/2CylinderEngine.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, 2CylinderEngine_glTF_Embedded)
{
  auto path = get_path("2CylinderEngine/glTF-Embedded/2CylinderEngine.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, ABeautifulGame_glTF)
{
  auto path = get_path("ABeautifulGame/glTF/ABeautifulGame.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, AlphaBlendModeTest_glTF)
{
  auto path = get_path("AlphaBlendModeTest/glTF/AlphaBlendModeTest.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, AlphaBlendModeTest_glTF_Binary)
{
  auto path = get_path("AlphaBlendModeTest/glTF-Binary/AlphaBlendModeTest.glb");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, AlphaBlendModeTest_glTF_Embedded)
{
  auto path =
    get_path("AlphaBlendModeTest/glTF-Embedded/AlphaBlendModeTest.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, AnimatedCube_glTF)
{
  auto path = get_path("AnimatedCube/glTF/AnimatedCube.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, AnimatedMorphCube_glTF)
{
  auto path = get_path("AnimatedMorphCube/glTF/AnimatedMorphCube.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, AnimatedMorphCube_glTF_Binary)
{
  auto path = get_path("AnimatedMorphCube/glTF-Binary/AnimatedMorphCube.glb");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, AnimatedMorphCube_glTF_Quantized)
{
  auto path =
    get_path("AnimatedMorphCube/glTF-Quantized/AnimatedMorphCube.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, AnimatedMorphSphere_glTF)
{
  auto path = get_path("AnimatedMorphSphere/glTF/AnimatedMorphSphere.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, AnimatedMorphSphere_glTF_Binary)
{
  auto path =
    get_path("AnimatedMorphSphere/glTF-Binary/AnimatedMorphSphere.glb");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, AnimatedTriangle_glTF)
{
  auto path = get_path("AnimatedTriangle/glTF/AnimatedTriangle.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, AnimatedTriangle_glTF_Embedded)
{
  auto path = get_path("AnimatedTriangle/glTF-Embedded/AnimatedTriangle.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, AntiqueCamera_glTF)
{
  auto path = get_path("AntiqueCamera/glTF/AntiqueCamera.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, AntiqueCamera_glTF_Binary)
{
  auto path = get_path("AntiqueCamera/glTF-Binary/AntiqueCamera.glb");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, AttenuationTest_glTF)
{
  auto path = get_path("AttenuationTest/glTF/AttenuationTest.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, AttenuationTest_glTF_Binary)
{
  auto path = get_path("AttenuationTest/glTF-Binary/AttenuationTest.glb");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, Avocado_glTF)
{
  auto path = get_path("Avocado/glTF/Avocado.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, Avocado_glTF_Binary)
{
  auto path = get_path("Avocado/glTF-Binary/Avocado.glb");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, Avocado_glTF_Draco)
{
  auto path = get_path("Avocado/glTF-Draco/Avocado.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, Avocado_glTF_Quantized)
{
  auto path = get_path("Avocado/glTF-Quantized/Avocado.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, BarramundiFish_glTF)
{
  auto path = get_path("BarramundiFish/glTF/BarramundiFish.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, BarramundiFish_glTF_Binary)
{
  auto path = get_path("BarramundiFish/glTF-Binary/BarramundiFish.glb");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, BarramundiFish_glTF_Draco)
{
  auto path = get_path("BarramundiFish/glTF-Draco/BarramundiFish.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, BoomBox_glTF)
{
  auto path = get_path("BoomBox/glTF/BoomBox.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, BoomBox_glTF_Binary)
{
  auto path = get_path("BoomBox/glTF-Binary/BoomBox.glb");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, BoomBox_glTF_Draco)
{
  auto path = get_path("BoomBox/glTF-Draco/BoomBox.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, BoomBoxWithAxes_glTF)
{
  auto path = get_path("BoomBoxWithAxes/glTF/BoomBoxWithAxes.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, Box_glTF)
{
  auto path = get_path("Box/glTF/Box.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, Box_glTF_Binary)
{
  auto path = get_path("Box/glTF-Binary/Box.glb");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, Box_glTF_Draco)
{
  auto path = get_path("Box/glTF-Draco/Box.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, Box_glTF_Embedded)
{
  auto path = get_path("Box/glTF-Embedded/Box.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, Box_With_Spaces_glTF)
{
  auto path = get_path("Box With Spaces/glTF/Box With Spaces.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, BoxAnimated_glTF)
{
  auto path = get_path("BoxAnimated/glTF/BoxAnimated.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, BoxAnimated_glTF_Binary)
{
  auto path = get_path("BoxAnimated/glTF-Binary/BoxAnimated.glb");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, BoxAnimated_glTF_Embedded)
{
  auto path = get_path("BoxAnimated/glTF-Embedded/BoxAnimated.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, BoxInterleaved_glTF)
{
  auto path = get_path("BoxInterleaved/glTF/BoxInterleaved.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, BoxInterleaved_glTF_Binary)
{
  auto path = get_path("BoxInterleaved/glTF-Binary/BoxInterleaved.glb");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, BoxInterleaved_glTF_Embedded)
{
  auto path = get_path("BoxInterleaved/glTF-Embedded/BoxInterleaved.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, BoxTextured_glTF)
{
  auto path = get_path("BoxTextured/glTF/BoxTextured.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, BoxTextured_glTF_Binary)
{
  auto path = get_path("BoxTextured/glTF-Binary/BoxTextured.glb");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, BoxTextured_glTF_Embedded)
{
  auto path = get_path("BoxTextured/glTF-Embedded/BoxTextured.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, BoxTexturedNonPowerOfTwo_glTF)
{
  auto path =
    get_path("BoxTexturedNonPowerOfTwo/glTF/BoxTexturedNonPowerOfTwo.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, BoxTexturedNonPowerOfTwo_glTF_Binary)
{
  auto path = get_path(
    "BoxTexturedNonPowerOfTwo/glTF-Binary/BoxTexturedNonPowerOfTwo.glb");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, BoxTexturedNonPowerOfTwo_glTF_Embedded)
{
  auto path = get_path(
    "BoxTexturedNonPowerOfTwo/glTF-Embedded/BoxTexturedNonPowerOfTwo.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, BoxVertexColors_glTF)
{
  auto path = get_path("BoxVertexColors/glTF/BoxVertexColors.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, BoxVertexColors_glTF_Binary)
{
  auto path = get_path("BoxVertexColors/glTF-Binary/BoxVertexColors.glb");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, BoxVertexColors_glTF_Embedded)
{
  auto path = get_path("BoxVertexColors/glTF-Embedded/BoxVertexColors.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, BrainStem_glTF)
{
  auto path = get_path("BrainStem/glTF/BrainStem.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, BrainStem_glTF_Binary)
{
  auto path = get_path("BrainStem/glTF-Binary/BrainStem.glb");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, BrainStem_glTF_Draco)
{
  auto path = get_path("BrainStem/glTF-Draco/BrainStem.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, BrainStem_glTF_Embedded)
{
  auto path = get_path("BrainStem/glTF-Embedded/BrainStem.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, BrainStem_glTF_Meshopt)
{
  auto path = get_path("BrainStem/glTF-Meshopt/BrainStem.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, Buggy_glTF)
{
  auto path = get_path("Buggy/glTF/Buggy.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, Buggy_glTF_Binary)
{
  auto path = get_path("Buggy/glTF-Binary/Buggy.glb");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, Buggy_glTF_Draco)
{
  auto path = get_path("Buggy/glTF-Draco/Buggy.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, Buggy_glTF_Embedded)
{
  auto path = get_path("Buggy/glTF-Embedded/Buggy.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, Cameras_glTF)
{
  auto path = get_path("Cameras/glTF/Cameras.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, Cameras_glTF_Embedded)
{
  auto path = get_path("Cameras/glTF-Embedded/Cameras.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, CesiumMan_glTF)
{
  auto path = get_path("CesiumMan/glTF/CesiumMan.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, CesiumMan_glTF_Binary)
{
  auto path = get_path("CesiumMan/glTF-Binary/CesiumMan.glb");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, CesiumMan_glTF_Draco)
{
  auto path = get_path("CesiumMan/glTF-Draco/CesiumMan.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, CesiumMan_glTF_Embedded)
{
  auto path = get_path("CesiumMan/glTF-Embedded/CesiumMan.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, CesiumMilkTruck_glTF)
{
  auto path = get_path("CesiumMilkTruck/glTF/CesiumMilkTruck.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, CesiumMilkTruck_glTF_Binary)
{
  auto path = get_path("CesiumMilkTruck/glTF-Binary/CesiumMilkTruck.glb");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, CesiumMilkTruck_glTF_Draco)
{
  auto path = get_path("CesiumMilkTruck/glTF-Draco/CesiumMilkTruck.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, CesiumMilkTruck_glTF_Embedded)
{
  auto path = get_path("CesiumMilkTruck/glTF-Embedded/CesiumMilkTruck.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, ClearCoatCarPaint_glTF)
{
  auto path = get_path("ClearCoatCarPaint/glTF/ClearCoatCarPaint.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, ClearCoatCarPaint_glTF_Binary)
{
  auto path = get_path("ClearCoatCarPaint/glTF-Binary/ClearCoatCarPaint.glb");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, ClearCoatTest_glTF)
{
  auto path = get_path("ClearCoatTest/glTF/ClearCoatTest.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, ClearCoatTest_glTF_Binary)
{
  auto path = get_path("ClearCoatTest/glTF-Binary/ClearCoatTest.glb");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, ClearcoatWicker_glTF)
{
  auto path = get_path("ClearcoatWicker/glTF/ClearcoatWicker.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, ClearcoatWicker_glTF_Binary)
{
  auto path = get_path("ClearcoatWicker/glTF-Binary/ClearcoatWicker.glb");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, Corset_glTF)
{
  auto path = get_path("Corset/glTF/Corset.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, Corset_glTF_Binary)
{
  auto path = get_path("Corset/glTF-Binary/Corset.glb");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, Corset_glTF_Draco)
{
  auto path = get_path("Corset/glTF-Draco/Corset.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, Cube_glTF)
{
  auto path = get_path("Cube/glTF/Cube.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, DamagedHelmet_glTF)
{
  auto path = get_path("DamagedHelmet/glTF/DamagedHelmet.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, DamagedHelmet_glTF_Binary)
{
  auto path = get_path("DamagedHelmet/glTF-Binary/DamagedHelmet.glb");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, DamagedHelmet_glTF_Embedded)
{
  auto path = get_path("DamagedHelmet/glTF-Embedded/DamagedHelmet.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, DragonAttenuation_glTF)
{
  auto path = get_path("DragonAttenuation/glTF/DragonAttenuation.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, DragonAttenuation_glTF_Binary)
{
  auto path = get_path("DragonAttenuation/glTF-Binary/DragonAttenuation.glb");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, DragonAttenuation_glTF_Meshopt)
{
  auto path = get_path("DragonAttenuation/glTF-Meshopt/DragonAttenuation.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, Duck_glTF)
{
  auto path = get_path("Duck/glTF/Duck.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, Duck_glTF_Binary)
{
  auto path = get_path("Duck/glTF-Binary/Duck.glb");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, Duck_glTF_Draco)
{
  auto path = get_path("Duck/glTF-Draco/Duck.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, Duck_glTF_Embedded)
{
  auto path = get_path("Duck/glTF-Embedded/Duck.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, Duck_glTF_Quantized)
{
  auto path = get_path("Duck/glTF-Quantized/Duck.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, EmissiveStrengthTest_glTF)
{
  auto path = get_path("EmissiveStrengthTest/glTF/EmissiveStrengthTest.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, EmissiveStrengthTest_glTF_Binary)
{
  auto path =
    get_path("EmissiveStrengthTest/glTF-Binary/EmissiveStrengthTest.glb");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, EnvironmentTest_glTF)
{
  auto path = get_path("EnvironmentTest/glTF/EnvironmentTest.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, EnvironmentTest_glTF_IBL)
{
  auto path = get_path("EnvironmentTest/glTF-IBL/EnvironmentTest.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, FlightHelmet_glTF)
{
  auto path = get_path("FlightHelmet/glTF/FlightHelmet.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, FlightHelmet_glTF_KTX_BasisU)
{
  auto path = get_path("FlightHelmet/glTF-KTX-BasisU/FlightHelmet.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, Fox_glTF)
{
  auto path = get_path("Fox/glTF/Fox.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, Fox_glTF_Binary)
{
  auto path = get_path("Fox/glTF-Binary/Fox.glb");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, GearboxAssy_glTF)
{
  auto path = get_path("GearboxAssy/glTF/GearboxAssy.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, GearboxAssy_glTF_Binary)
{
  auto path = get_path("GearboxAssy/glTF-Binary/GearboxAssy.glb");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, GearboxAssy_glTF_Draco)
{
  auto path = get_path("GearboxAssy/glTF-Draco/GearboxAssy.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, GearboxAssy_glTF_Embedded)
{
  auto path = get_path("GearboxAssy/glTF-Embedded/GearboxAssy.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, GlamVelvetSofa_glTF)
{
  auto path = get_path("GlamVelvetSofa/glTF/GlamVelvetSofa.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, GlamVelvetSofa_glTF_Binary)
{
  auto path = get_path("GlamVelvetSofa/glTF-Binary/GlamVelvetSofa.glb");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, InterpolationTest_glTF)
{
  auto path = get_path("InterpolationTest/glTF/InterpolationTest.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, InterpolationTest_glTF_Binary)
{
  auto path = get_path("InterpolationTest/glTF-Binary/InterpolationTest.glb");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, IridescenceDielectricSpheres_glTF)
{
  auto path = get_path(
    "IridescenceDielectricSpheres/glTF/IridescenceDielectricSpheres.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, IridescenceLamp_glTF)
{
  auto path = get_path("IridescenceLamp/glTF/IridescenceLamp.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, IridescenceLamp_glTF_Binary)
{
  auto path = get_path("IridescenceLamp/glTF-Binary/IridescenceLamp.glb");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, IridescenceMetallicSpheres_glTF)
{
  auto path =
    get_path("IridescenceMetallicSpheres/glTF/IridescenceMetallicSpheres.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, IridescenceSuzanne_glTF)
{
  auto path = get_path("IridescenceSuzanne/glTF/IridescenceSuzanne.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, IridescenceSuzanne_glTF_Binary)
{
  auto path = get_path("IridescenceSuzanne/glTF-Binary/IridescenceSuzanne.glb");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, IridescentDishWithOlives_glTF)
{
  auto path =
    get_path("IridescentDishWithOlives/glTF/IridescentDishWithOlives.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, IridescentDishWithOlives_glTF_Binary)
{
  auto path = get_path(
    "IridescentDishWithOlives/glTF-Binary/IridescentDishWithOlives.glb");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, Lantern_glTF)
{
  auto path = get_path("Lantern/glTF/Lantern.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, Lantern_glTF_Binary)
{
  auto path = get_path("Lantern/glTF-Binary/Lantern.glb");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, Lantern_glTF_Draco)
{
  auto path = get_path("Lantern/glTF-Draco/Lantern.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, Lantern_glTF_Quantized)
{
  auto path = get_path("Lantern/glTF-Quantized/Lantern.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, LightsPunctualLamp_glTF)
{
  auto path = get_path("LightsPunctualLamp/glTF/LightsPunctualLamp.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, LightsPunctualLamp_glTF_Binary)
{
  auto path = get_path("LightsPunctualLamp/glTF-Binary/LightsPunctualLamp.glb");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, MaterialsVariantsShoe_glTF)
{
  auto path = get_path("MaterialsVariantsShoe/glTF/MaterialsVariantsShoe.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, MaterialsVariantsShoe_glTF_Binary)
{
  auto path =
    get_path("MaterialsVariantsShoe/glTF-Binary/MaterialsVariantsShoe.glb");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, MeshPrimitiveModes_glTF)
{
  auto path = get_path("MeshPrimitiveModes/glTF/MeshPrimitiveModes.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, MeshPrimitiveModes_glTF_Embedded)
{
  auto path =
    get_path("MeshPrimitiveModes/glTF-Embedded/MeshPrimitiveModes.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, MetalRoughSpheres_glTF)
{
  auto path = get_path("MetalRoughSpheres/glTF/MetalRoughSpheres.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, MetalRoughSpheres_glTF_Binary)
{
  auto path = get_path("MetalRoughSpheres/glTF-Binary/MetalRoughSpheres.glb");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, MetalRoughSpheres_glTF_Embedded)
{
  auto path =
    get_path("MetalRoughSpheres/glTF-Embedded/MetalRoughSpheres.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, MetalRoughSpheresNoTextures_glTF)
{
  auto path = get_path(
    "MetalRoughSpheresNoTextures/glTF/MetalRoughSpheresNoTextures.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, MetalRoughSpheresNoTextures_glTF_Binary)
{
  auto path = get_path(
    "MetalRoughSpheresNoTextures/glTF-Binary/MetalRoughSpheresNoTextures.glb");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, MorphPrimitivesTest_glTF)
{
  auto path = get_path("MorphPrimitivesTest/glTF/MorphPrimitivesTest.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, MorphPrimitivesTest_glTF_Binary)
{
  auto path =
    get_path("MorphPrimitivesTest/glTF-Binary/MorphPrimitivesTest.glb");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, MorphPrimitivesTest_glTF_Draco)
{
  auto path =
    get_path("MorphPrimitivesTest/glTF-Draco/MorphPrimitivesTest.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, MorphStressTest_glTF)
{
  auto path = get_path("MorphStressTest/glTF/MorphStressTest.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, MorphStressTest_glTF_Binary)
{
  auto path = get_path("MorphStressTest/glTF-Binary/MorphStressTest.glb");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, MosquitoInAmber_glTF)
{
  auto path = get_path("MosquitoInAmber/glTF/MosquitoInAmber.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, MosquitoInAmber_glTF_Binary)
{
  auto path = get_path("MosquitoInAmber/glTF-Binary/MosquitoInAmber.glb");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, MultipleScenes_glTF)
{
  auto path = get_path("MultipleScenes/glTF/MultipleScenes.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, MultipleScenes_glTF_Embedded)
{
  auto path = get_path("MultipleScenes/glTF-Embedded/MultipleScenes.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, MultiUVTest_glTF)
{
  auto path = get_path("MultiUVTest/glTF/MultiUVTest.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, MultiUVTest_glTF_Binary)
{
  auto path = get_path("MultiUVTest/glTF-Binary/MultiUVTest.glb");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, MultiUVTest_glTF_Embedded)
{
  auto path = get_path("MultiUVTest/glTF-Embedded/MultiUVTest.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, NegativeScaleTest_glTF)
{
  auto path = get_path("NegativeScaleTest/glTF/NegativeScaleTest.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, NegativeScaleTest_glTF_Binary)
{
  auto path = get_path("NegativeScaleTest/glTF-Binary/NegativeScaleTest.glb");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, NormalTangentMirrorTest_glTF)
{
  auto path =
    get_path("NormalTangentMirrorTest/glTF/NormalTangentMirrorTest.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, NormalTangentMirrorTest_glTF_Binary)
{
  auto path =
    get_path("NormalTangentMirrorTest/glTF-Binary/NormalTangentMirrorTest.glb");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, NormalTangentMirrorTest_glTF_Embedded)
{
  auto path = get_path(
    "NormalTangentMirrorTest/glTF-Embedded/NormalTangentMirrorTest.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, NormalTangentTest_glTF)
{
  auto path = get_path("NormalTangentTest/glTF/NormalTangentTest.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, NormalTangentTest_glTF_Binary)
{
  auto path = get_path("NormalTangentTest/glTF-Binary/NormalTangentTest.glb");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, NormalTangentTest_glTF_Embedded)
{
  auto path =
    get_path("NormalTangentTest/glTF-Embedded/NormalTangentTest.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, OrientationTest_glTF)
{
  auto path = get_path("OrientationTest/glTF/OrientationTest.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, OrientationTest_glTF_Binary)
{
  auto path = get_path("OrientationTest/glTF-Binary/OrientationTest.glb");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, OrientationTest_glTF_Embedded)
{
  auto path = get_path("OrientationTest/glTF-Embedded/OrientationTest.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, ReciprocatingSaw_glTF)
{
  auto path = get_path("ReciprocatingSaw/glTF/ReciprocatingSaw.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, ReciprocatingSaw_glTF_Binary)
{
  auto path = get_path("ReciprocatingSaw/glTF-Binary/ReciprocatingSaw.glb");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, ReciprocatingSaw_glTF_Draco)
{
  auto path = get_path("ReciprocatingSaw/glTF-Draco/ReciprocatingSaw.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, ReciprocatingSaw_glTF_Embedded)
{
  auto path = get_path("ReciprocatingSaw/glTF-Embedded/ReciprocatingSaw.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, RecursiveSkeletons_glTF)
{
  auto path = get_path("RecursiveSkeletons/glTF/RecursiveSkeletons.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, RecursiveSkeletons_glTF_Binary)
{
  auto path = get_path("RecursiveSkeletons/glTF-Binary/RecursiveSkeletons.glb");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, RiggedFigure_glTF)
{
  auto path = get_path("RiggedFigure/glTF/RiggedFigure.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, RiggedFigure_glTF_Binary)
{
  auto path = get_path("RiggedFigure/glTF-Binary/RiggedFigure.glb");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, RiggedFigure_glTF_Draco)
{
  auto path = get_path("RiggedFigure/glTF-Draco/RiggedFigure.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, RiggedFigure_glTF_Embedded)
{
  auto path = get_path("RiggedFigure/glTF-Embedded/RiggedFigure.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, RiggedSimple_glTF)
{
  auto path = get_path("RiggedSimple/glTF/RiggedSimple.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, RiggedSimple_glTF_Binary)
{
  auto path = get_path("RiggedSimple/glTF-Binary/RiggedSimple.glb");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, RiggedSimple_glTF_Draco)
{
  auto path = get_path("RiggedSimple/glTF-Draco/RiggedSimple.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, RiggedSimple_glTF_Embedded)
{
  auto path = get_path("RiggedSimple/glTF-Embedded/RiggedSimple.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, SciFiHelmet_glTF)
{
  auto path = get_path("SciFiHelmet/glTF/SciFiHelmet.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, SheenChair_glTF)
{
  auto path = get_path("SheenChair/glTF/SheenChair.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, SheenChair_glTF_Binary)
{
  auto path = get_path("SheenChair/glTF-Binary/SheenChair.glb");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, SheenCloth_glTF)
{
  auto path = get_path("SheenCloth/glTF/SheenCloth.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, SimpleInstancing_glTF)
{
  auto path = get_path("SimpleInstancing/glTF/SimpleInstancing.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, SimpleInstancing_glTF_Binary)
{
  auto path = get_path("SimpleInstancing/glTF-Binary/SimpleInstancing.glb");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, SimpleMeshes_glTF)
{
  auto path = get_path("SimpleMeshes/glTF/SimpleMeshes.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, SimpleMeshes_glTF_Embedded)
{
  auto path = get_path("SimpleMeshes/glTF-Embedded/SimpleMeshes.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, SimpleMorph_glTF)
{
  auto path = get_path("SimpleMorph/glTF/SimpleMorph.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, SimpleMorph_glTF_Embedded)
{
  auto path = get_path("SimpleMorph/glTF-Embedded/SimpleMorph.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, SimpleSkin_glTF)
{
  auto path = get_path("SimpleSkin/glTF/SimpleSkin.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, SimpleSkin_glTF_Embedded)
{
  auto path = get_path("SimpleSkin/glTF-Embedded/SimpleSkin.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, SimpleSparseAccessor_glTF)
{
  auto path = get_path("SimpleSparseAccessor/glTF/SimpleSparseAccessor.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, SimpleSparseAccessor_glTF_Embedded)
{
  auto path =
    get_path("SimpleSparseAccessor/glTF-Embedded/SimpleSparseAccessor.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, SpecGlossVsMetalRough_glTF)
{
  auto path = get_path("SpecGlossVsMetalRough/glTF/SpecGlossVsMetalRough.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, SpecGlossVsMetalRough_glTF_Binary)
{
  auto path =
    get_path("SpecGlossVsMetalRough/glTF-Binary/SpecGlossVsMetalRough.glb");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, SpecularTest_glTF)
{
  auto path = get_path("SpecularTest/glTF/SpecularTest.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, SpecularTest_glTF_Binary)
{
  auto path = get_path("SpecularTest/glTF-Binary/SpecularTest.glb");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, Sponza_glTF)
{
  auto path = get_path("Sponza/glTF/Sponza.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, StainedGlassLamp_glTF)
{
  auto path = get_path("StainedGlassLamp/glTF/StainedGlassLamp.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, StainedGlassLamp_glTF_JPG_PNG)
{
  auto path = get_path("StainedGlassLamp/glTF-JPG-PNG/StainedGlassLamp.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, StainedGlassLamp_glTF_KTX_BasisU)
{
  auto path =
    get_path("StainedGlassLamp/glTF-KTX-BasisU/StainedGlassLamp.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, Suzanne_glTF)
{
  auto path = get_path("Suzanne/glTF/Suzanne.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, TextureCoordinateTest_glTF)
{
  auto path = get_path("TextureCoordinateTest/glTF/TextureCoordinateTest.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, TextureCoordinateTest_glTF_Binary)
{
  auto path =
    get_path("TextureCoordinateTest/glTF-Binary/TextureCoordinateTest.glb");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, TextureCoordinateTest_glTF_Embedded)
{
  auto path =
    get_path("TextureCoordinateTest/glTF-Embedded/TextureCoordinateTest.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, TextureEncodingTest_glTF)
{
  auto path = get_path("TextureEncodingTest/glTF/TextureEncodingTest.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, TextureEncodingTest_glTF_Binary)
{
  auto path =
    get_path("TextureEncodingTest/glTF-Binary/TextureEncodingTest.glb");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, TextureLinearInterpolationTest_glTF)
{
  auto path = get_path(
    "TextureLinearInterpolationTest/glTF/TextureLinearInterpolationTest.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, TextureLinearInterpolationTest_glTF_Binary)
{
  auto path = get_path("TextureLinearInterpolationTest/glTF-Binary/"
                       "TextureLinearInterpolationTest.glb");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, TextureSettingsTest_glTF)
{
  auto path = get_path("TextureSettingsTest/glTF/TextureSettingsTest.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, TextureSettingsTest_glTF_Binary)
{
  auto path =
    get_path("TextureSettingsTest/glTF-Binary/TextureSettingsTest.glb");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, TextureSettingsTest_glTF_Embedded)
{
  auto path =
    get_path("TextureSettingsTest/glTF-Embedded/TextureSettingsTest.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, TextureTransformMultiTest_glTF)
{
  auto path =
    get_path("TextureTransformMultiTest/glTF/TextureTransformMultiTest.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, TextureTransformMultiTest_glTF_Binary)
{
  auto path = get_path(
    "TextureTransformMultiTest/glTF-Binary/TextureTransformMultiTest.glb");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, TextureTransformTest_glTF)
{
  auto path = get_path("TextureTransformTest/glTF/TextureTransformTest.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, ToyCar_glTF)
{
  auto path = get_path("ToyCar/glTF/ToyCar.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, ToyCar_glTF_Binary)
{
  auto path = get_path("ToyCar/glTF-Binary/ToyCar.glb");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, TransmissionRoughnessTest_glTF)
{
  auto path =
    get_path("TransmissionRoughnessTest/glTF/TransmissionRoughnessTest.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, TransmissionRoughnessTest_glTF_Binary)
{
  auto path = get_path(
    "TransmissionRoughnessTest/glTF-Binary/TransmissionRoughnessTest.glb");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, TransmissionTest_glTF)
{
  auto path = get_path("TransmissionTest/glTF/TransmissionTest.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, TransmissionTest_glTF_Binary)
{
  auto path = get_path("TransmissionTest/glTF-Binary/TransmissionTest.glb");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, Triangle_glTF)
{
  auto path = get_path("Triangle/glTF/Triangle.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, Triangle_glTF_Embedded)
{
  auto path = get_path("Triangle/glTF-Embedded/Triangle.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, TriangleWithoutIndices_glTF)
{
  auto path =
    get_path("TriangleWithoutIndices/glTF/TriangleWithoutIndices.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, TriangleWithoutIndices_glTF_Embedded)
{
  auto path = get_path(
    "TriangleWithoutIndices/glTF-Embedded/TriangleWithoutIndices.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, TwoSidedPlane_glTF)
{
  auto path = get_path("TwoSidedPlane/glTF/TwoSidedPlane.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, UnlitTest_glTF)
{
  auto path = get_path("UnlitTest/glTF/UnlitTest.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, UnlitTest_glTF_Binary)
{
  auto path = get_path("UnlitTest/glTF-Binary/UnlitTest.glb");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, VC_glTF)
{
  auto path = get_path("VC/glTF/VC.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, VC_glTF_Binary)
{
  auto path = get_path("VC/glTF-Binary/VC.glb");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, VC_glTF_Draco)
{
  auto path = get_path("VC/glTF-Draco/VC.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, VC_glTF_Embedded)
{
  auto path = get_path("VC/glTF-Embedded/VC.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, VertexColorTest_glTF)
{
  auto path = get_path("VertexColorTest/glTF/VertexColorTest.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, VertexColorTest_glTF_Binary)
{
  auto path = get_path("VertexColorTest/glTF-Binary/VertexColorTest.glb");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, VertexColorTest_glTF_Embedded)
{
  auto path = get_path("VertexColorTest/glTF-Embedded/VertexColorTest.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, WaterBottle_glTF)
{
  auto path = get_path("WaterBottle/glTF/WaterBottle.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, WaterBottle_glTF_Binary)
{
  auto path = get_path("WaterBottle/glTF-Binary/WaterBottle.glb");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}

TEST(GltfSamples, WaterBottle_glTF_Draco)
{
  auto path = get_path("WaterBottle/glTF-Draco/WaterBottle.gltf");
  if (!std::filesystem::exists(path)) {
    std::cerr << path << " not exists" << std::endl;
  }
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }
  if (path.extension() == ".glb") {
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  } else {
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
}
