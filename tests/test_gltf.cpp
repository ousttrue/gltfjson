#include <gltfjson/deserialize.h>
#include <gtest/gtest.h>

// https://github.com/KhronosGroup/glTF-Tutorials/blob/master/gltfTutorial/gltfTutorial_003_MinimalGltfFile.md
auto MINIMUM = u8R"(
{
  "scene": 0,
  "scenes" : [
    {
      "nodes" : [ 0 ]
    }
  ],
  
  "nodes" : [
    {
      "mesh" : 0
    }
  ],
  
  "meshes" : [
    {
      "primitives" : [ {
        "attributes" : {
          "POSITION" : 1
        },
        "indices" : 0
      } ]
    }
  ],

  "buffers" : [
    {
      "uri" : "data:application/octet-stream;base64,AAABAAIAAAAAAAAAAAAAAAAAAAAAAIA/AAAAAAAAAAAAAAAAAACAPwAAAAA=",
      "byteLength" : 44
    }
  ],
  "bufferViews" : [
    {
      "buffer" : 0,
      "byteOffset" : 0,
      "byteLength" : 6,
      "target" : 34963
    },
    {
      "buffer" : 0,
      "byteOffset" : 8,
      "byteLength" : 36,
      "target" : 34962
    }
  ],
  "accessors" : [
    {
      "bufferView" : 0,
      "byteOffset" : 0,
      "componentType" : 5123,
      "count" : 3,
      "type" : "SCALAR",
      "max" : [ 2 ],
      "min" : [ 0 ]
    },
    {
      "bufferView" : 1,
      "byteOffset" : 0,
      "componentType" : 5126,
      "count" : 3,
      "type" : "VEC3",
      "max" : [ 1.0, 1.0, 0.0 ],
      "min" : [ 0.0, 0.0, 0.0 ]
    }
  ],
  
  "asset" : {
    "version" : "2.0"
  }
}
)";

TEST(GltfTest, Parse)
{
  gltfjson::Parser parser(MINIMUM);
  auto result = parser.Parse();
  EXPECT_TRUE(result);
  auto asset = result->Get(u8"asset");
  auto version = asset->Get(u8"version");
  EXPECT_EQ(*version, gltfjson::Value(u8"\"2.0\""));

  gltfjson::format::Root gltf;
  gltfjson::Deserialize(parser, gltf);

  EXPECT_EQ(gltf.BufferViews[0].Buffer, 0);
  EXPECT_EQ(gltf.BufferViews[0].ByteOffset, 0);
  EXPECT_EQ(gltf.BufferViews[0].ByteOffset, 0);
  EXPECT_EQ(gltf.BufferViews[0].ByteLength, 6);
  EXPECT_EQ(gltf.BufferViews[0].Target,
            gltfjson::format::Targets::ELEMENT_ARRAY_BUFFER);
  // accessors.0
  EXPECT_EQ(gltf.Accessors[0].BufferView, 0);
  EXPECT_EQ(gltf.Accessors[0].ByteOffset, 0);
  EXPECT_EQ(gltf.Accessors[0].ComponentType,
            gltfjson::format::ComponentTypes::UNSIGNED_SHORT);
  EXPECT_EQ(gltf.Accessors[0].Count, 3);
  EXPECT_EQ(gltf.Accessors[0].Type, gltfjson::format::Types::SCALAR);
  EXPECT_EQ(gltf.Accessors[0].Max, std::vector<float>{ 2 });
  EXPECT_EQ(gltf.Accessors[0].Min, std::vector<float>{ 0 });

  // accessors.1
  std::vector<float> values = { 0, 0, 0 };
  EXPECT_EQ(gltf.Accessors[1].Min, values);

  EXPECT_EQ(gltf.Asset.Version, u8"2.0");
}
