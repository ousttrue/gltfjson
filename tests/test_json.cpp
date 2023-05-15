#include <gltfjson/format.h>
#include <gltfjson/json.h>
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

TEST(GltfJson, ParsePrimitive)
{
  {
    auto SRC = u8"true";
    gltfjson::json::Parser parser(SRC);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
    if (result) {
      EXPECT_EQ(*result, gltfjson::json::Json(SRC));
    }
  }
  {
    auto SRC = u8"false";
    gltfjson::json::Parser parser(SRC);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
    if (result) {
      EXPECT_EQ(*result, gltfjson::json::Json(SRC));
    }
  }
  {
    auto SRC = u8"null";
    gltfjson::json::Parser parser(SRC);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
    if (result) {
      EXPECT_EQ(*result, gltfjson::json::Json(SRC));
    }
  }
}

TEST(GltfJson, ParseNumber)
{
  {
    auto SRC = u8"1";
    gltfjson::json::Parser parser(SRC);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
    if (result) {
      EXPECT_EQ(*result, gltfjson::json::Json(SRC));
    }
  }
  {
    auto SRC = u8"-1";
    gltfjson::json::Parser parser(SRC);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
    if (result) {
      EXPECT_EQ(*result, gltfjson::json::Json(SRC));
    }
  }
  {
    auto SRC = u8"1e-5";
    gltfjson::json::Parser parser(SRC);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
    if (result) {
      EXPECT_EQ(*result, gltfjson::json::Json(SRC));
    }
  }
  {
    auto SRC = u8"1.1";
    gltfjson::json::Parser parser(SRC);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
    if (result) {
      EXPECT_EQ(*result, gltfjson::json::Json(SRC));
    }
  }
}
