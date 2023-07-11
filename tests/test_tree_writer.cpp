#include "minimum_gltf.h"
#include <gltfjson.h>
#include <gltfjson/json_tree_bin_serializer.h>
#include <gltfjson/json_tree_exporter.h>
#include <gtest/gtest.h>
#include <sstream>

TEST(TestTreeWriter, BinWriter)
{
  gltfjson::tree::Parser parser(MINIMUM);
  auto result = parser.Parse();
  EXPECT_TRUE(result);

  // regenerate bin. update bufferviews, images, accessors
  auto dir = std::make_shared<gltfjson::Directory>();
  gltfjson::Bin bin{ dir, {} };
  auto serializer = gltfjson::tree::BinSerializer(result, bin);
  auto bytes = serializer.Serialize({}, {});
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

  auto bufferView0 = result->Get(u8"bufferViews")->Get(0);
  auto bufferView1 = result2->Get(u8"bufferViews")->Get(0);
  EXPECT_EQ(*bufferView0->Get(u8"bytesLength")->Ptr<float>(),
            *bufferView1->Get(u8"bytesLength")->Ptr<float>());
}
