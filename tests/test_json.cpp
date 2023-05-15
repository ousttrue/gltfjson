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
      EXPECT_EQ(*result, gltfjson::json::Value(SRC));
    }
  }
  {
    auto SRC = u8"false";
    gltfjson::json::Parser parser(SRC);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
    if (result) {
      EXPECT_EQ(*result, gltfjson::json::Value(SRC));
    }
  }
  {
    auto SRC = u8"null";
    gltfjson::json::Parser parser(SRC);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
    if (result) {
      EXPECT_EQ(*result, gltfjson::json::Value(SRC));
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
      EXPECT_EQ(*result, gltfjson::json::Value(SRC));
    }
  }
  {
    auto SRC = u8"-1";
    gltfjson::json::Parser parser(SRC);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
    if (result) {
      EXPECT_EQ(*result, gltfjson::json::Value(SRC));
    }
  }
  {
    auto SRC = u8"1e-5";
    gltfjson::json::Parser parser(SRC);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
    if (result) {
      EXPECT_EQ(*result, gltfjson::json::Value(SRC));
    }
  }
  {
    auto SRC = u8"1.1";
    gltfjson::json::Parser parser(SRC);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
    if (result) {
      EXPECT_EQ(*result, gltfjson::json::Value(SRC));
    }
  }
}

TEST(GltfJson, ParseString)
{
  {
    auto SRC = u8R"(
"abc"
)";
    gltfjson::json::Parser parser(SRC);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
    if (result) {
      EXPECT_EQ(*result, gltfjson::json::Value(u8"\"abc\""));
    }
  }
}

TEST(GltfJson, ParseArray)
{
  {
    auto SRC = u8"[ ]";
    gltfjson::json::Parser parser(SRC);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
    EXPECT_EQ(parser.Values.size(), 1);
    EXPECT_EQ(parser.ChildCount(*result), 0);
  }
  {
    auto SRC = u8"[1, 2, 3]";
    gltfjson::json::Parser parser(SRC);
    auto result = parser.Parse();
    EXPECT_EQ(parser.Values.size(), 4);
    if (result) {
      EXPECT_EQ(parser.ChildCount(*result), 3);
      EXPECT_EQ(*parser.GetItem(*result, 0), gltfjson::json::Value(u8"1"));
    }
  }
  {
    auto SRC = u8"[1, [2, 3]]";
    gltfjson::json::Parser parser(SRC);
    auto result = parser.Parse();
    EXPECT_EQ(parser.Values.size(), 5);
    if (result) {
      auto inner = parser.GetItem(*result, 1);
      EXPECT_EQ(*parser.GetItem(*inner, 1), gltfjson::json::Value(u8"3"));
    }
  }
}

TEST(GltfJson, ParseObject)
{
  {
    auto SRC = u8"{ }";
    gltfjson::json::Parser parser(SRC);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
    EXPECT_EQ(parser.Values.size(), 1);
    EXPECT_EQ(parser.ChildCount(*result), 0);
  }
  {
    auto SRC = u8"{\"key\": 1}";
    gltfjson::json::Parser parser(SRC);
    auto result = parser.Parse();
    EXPECT_EQ(parser.Values.size(), 3);
    if (result) {
      EXPECT_EQ(parser.ChildCount(*result), 1);
      EXPECT_EQ(*parser.GetProperty(*result, u8"key"),
                gltfjson::json::Value(u8"1"));
    }
  }
  {
    auto SRC = u8"{\"key\": {\"key2\": 2}}";
    gltfjson::json::Parser parser(SRC);
    auto result = parser.Parse();
    EXPECT_EQ(parser.Values.size(), 5);
    if (result) {
      auto inner = parser.GetProperty(*result, u8"key");
      EXPECT_EQ(*parser.GetProperty(*inner, u8"key2"),
                gltfjson::json::Value(u8"2"));
    }
  }
}
