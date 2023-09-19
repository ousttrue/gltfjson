#include "minimum_gltf.h"
#include <gltfjson.h>
#include <gltfjson/json_tree_bin_serializer.h>
#include <gltfjson/json_tree_exporter.h>
#include <gtest/gtest.h>
#include <sstream>

static bool
eq(std::span<const uint8_t> lhs, std::span<const uint8_t> rhs)
{
  if (lhs.size() != rhs.size()) {
    return false;
  }
  return memcmp(lhs.data(), rhs.data(), lhs.size()) == 0;
}

TEST(TestTreeWriter, BinWriter)
{
  gltfjson::tree::Parser parser(MINIMUM);
  auto result = parser.Parse();
  EXPECT_TRUE(result);

  // regenerate bin. update bufferviews, images, accessors
  auto dir = std::make_shared<gltfjson::Directory>();
  gltfjson::Bin bin{ dir, {} };
  std::vector<uint8_t> bytes;

  gltfjson::Root root(result);
  gltfjson::tree::BinSerializer serializer(root, bin, bytes);
  serializer.Serialize({}, {});
  EXPECT_TRUE(bytes.size());

  // tree to json
  std::stringstream ss;
  gltfjson::StringSink sink = [&ss](std::string_view view) mutable {
    ss << view;
  };
  gltfjson::tree::Exporter exporter(sink);
  exporter.Export(result);
  auto jsonchunk = ss.str();

  std::cout << jsonchunk << std::endl;

  // glb
  // gltfjson::Glb{
  //   .JsonChunk = { (const uint8_t*)jsonchunk.data(), jsonchunk.size() },
  //   .BinChunk = bytes,
  // }
  //   .WriteTo(ss);

  // parse2
  gltfjson::tree::Parser parser2(jsonchunk);
  auto result2 = parser2.Parse();
  EXPECT_TRUE(result2);
  gltfjson::Root root2(result2);
  gltfjson::Bin bin2{ dir, bytes };

  gltfjson::tree::Parser parser3(MINIMUM);
  auto result3 = parser3.Parse();
  gltfjson::Root root3(result3);

  // auto bufferView3 = result3->Get(u8"bufferViews")->Get(0);
  // auto bufferView2 = result2->Get(u8"bufferViews")->Get(0);
  // EXPECT_EQ(*bufferView3, *bufferView2);

  // images
  for (int i = 0; i < root3.Images.size(); ++i) {
    auto lhs = *bin.GetImageBytes(root3, i);
    auto rhs = *bin2.GetImageBytes(root2, i);
    EXPECT_TRUE(eq(lhs, rhs));
  }

  // accessors
  for (int i = 0; i < root3.Accessors.size(); ++i) {
    auto lhs = *bin.GetAccessorBlock(root3, i);
    auto rhs = *bin2.GetAccessorBlock(root2, i);
    EXPECT_TRUE(eq(lhs.Span, rhs.Span));
  }
}
