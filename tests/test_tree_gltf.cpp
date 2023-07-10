#include <gltfjson.h>
#include <gtest/gtest.h>

// https://github.com/KhronosGroup/glTF-Tutorials/blob/master/gltfTutorial/gltfTutorial_003_MinimalGltfFile.md
static auto MINIMUM = u8R"(
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

TEST(GltfTestTree, Parse)
{
  gltfjson::tree::Parser parser(MINIMUM);
  auto result = parser.Parse();
  EXPECT_TRUE(result);

  gltfjson::Root gltf(result);

  // asset
  EXPECT_EQ(gltf.Asset()->VersionString(), u8"2.0");

  EXPECT_EQ(*gltf.Scene(), 0);

  // scenes.0
  EXPECT_EQ(gltf.Scenes[0].Nodes.size(), 1);
  EXPECT_EQ(gltf.Scenes[0].Nodes[0], 0);

  // nodes.0
  EXPECT_EQ(*gltf.Nodes[0].MeshId(), 0);

  // meshes.0.primitives.0
  EXPECT_EQ(*gltf.Meshes[0].Primitives[0].Attributes()->POSITION_Id(), 1);
  EXPECT_EQ(*gltf.Meshes[0].Primitives[0].IndicesId(), 0);

  // bufferViews.0
  EXPECT_EQ(*gltf.BufferViews[0].BufferId(), 0);
  EXPECT_EQ(*gltf.BufferViews[0].ByteOffset(), 0);
  EXPECT_EQ(*gltf.BufferViews[0].ByteOffset(), 0);
  EXPECT_EQ(*gltf.BufferViews[0].ByteLength(), 6);
  // EXPECT_EQ((gltfjson::Targets)*gltf.BufferViews[0].Target(),
  //           gltfjson::Targets::ELEMENT_ARRAY_BUFFER);

  // accessors.0
  EXPECT_EQ(*gltf.Accessors[0].BufferViewId(), 0);
  EXPECT_EQ(*gltf.Accessors[0].ByteOffset(), 0);
  EXPECT_EQ((gltfjson::ComponentTypes)*gltf.Accessors[0].ComponentType(),
            gltfjson::ComponentTypes::UNSIGNED_SHORT);
  EXPECT_EQ(*gltf.Accessors[0].Count(), 3);
  EXPECT_EQ(gltf.Accessors[0].TypeString(), u8"SCALAR");
  EXPECT_EQ(gltf.Accessors[0].Max.size(), 1);
  EXPECT_EQ(gltf.Accessors[0].Max[0], 2);
  EXPECT_EQ(gltf.Accessors[0].Min.size(), 1);
  EXPECT_EQ(gltf.Accessors[0].Min[0], 0);

  // accessors.1
  EXPECT_EQ(gltf.Accessors[1].Min.size(), 3);
  EXPECT_EQ(gltf.Accessors[1].Min[0], 0);
  EXPECT_EQ(gltf.Accessors[1].Min[1], 0);
  EXPECT_EQ(gltf.Accessors[1].Min[2], 0);
}
