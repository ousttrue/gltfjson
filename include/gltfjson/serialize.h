#pragma once
#include "gltf.h"
#include "json_writer.h"

namespace gltfjson {
namespace format {

static void
Serialize(Writer& w, std::string_view key, const std::u8string& value)
{
  if (value.size()) {
    w.key(key);
    w.value(value);
  }
}

static void
Serialize(Writer& w, std::string_view key, const Id& id)
{
  if (id) {
    w.key(key);
    w.value(*id);
  }
}

// "asset": {
//     "version": "2.0",
//     "generator": "collada2gltf@f356b99aef8868f74877c7ca545f2cd206b9d3b7",
//     "copyright": "2017 (c) Khronos Group"
// }
static void
ExportAsset(Writer& w, const Asset& asset)
{
  w.object_open();
  Serialize(w, "version", asset.Version);
  Serialize(w, "generator", asset.Generator);
  Serialize(w, "copyright", asset.Copyright);
  w.object_close();
}

// {
//     "bufferView": 14,
//     "mimeType": "image/jpeg"
// }
static void
ExportImage(Writer& w, const Image& image)
{
  w.object_open();
  Serialize(w, "name", image.Name);
  Serialize(w, "bufferView", image.BufferView);
  w.object_close();
}

// {
//     "magFilter": 9729,
//     "minFilter": 9987,
//     "wrapS": 10497,
//     "wrapT": 10497
// }
static void
ExportTextureSampler(Writer& w, const Sampler& sampler)
{
  w.object_open();
  w.object_close();
}

// {
//     "sampler": 0,
//     "source": 2
// }
static void
ExportTexture(Writer& w, const Texture& texture)
{
  w.object_open();
  Serialize(w, "name", texture.Name);
  Serialize(w, "source", texture.Source);
  Serialize(w, "sampler", texture.Sampler);
  w.object_close();
}

// {
//     "name": "gold",
//     "pbrMetallicRoughness": {
//         "baseColorFactor": [ 1.000, 0.766, 0.336, 1.0 ],
//         "baseColorTexture": {
//             "index": 0,
//             "texCoord": 1
//         },
//         "metallicFactor": 1.0,
//         "roughnessFactor": 0.0
//     }
// }
static void
ExportMaterial(Writer& w, const Material& material)
{
  w.object_open();
  Serialize(w, "name", material.Name);
  w.key("pbrMetallicRoughness");
  {
    w.object_open();
    // if (material->ColorTexture) {
    //   w.key("baseColorTexture");
    //   {
    //     w.object_open();
    //     w.key("index");
    //     w.value(*scene.IndexOf(material->ColorTexture));
    //     w.object_close();
    //   }
    // }
    w.object_close();
  }
  w.object_close();
}

// {
//     "primitives": [
//         {
//             "attributes": {
//                 "NORMAL": 23,
//                 "POSITION": 22,
//                 "TANGENT": 24,
//                 "TEXCOORD_0": 25
//             },
//             "indices": 21,
//             "material": 3,
//             "mode": 4
//         }
//     ]
// }
static void
ExportMesh(Writer& w, const Mesh& mesh)
{
  w.object_open();
  Serialize(w, "name", mesh.Name);
  w.key("primitives");
  w.array_open();
  // uint32_t index = 0;
  // for (auto& prim : mesh.Primitives) {
  //   index = ExportMeshPrimitive(c, mesh, prim, index);
  // }
  w.array_close();
  w.object_close();
}

// {
//     "inverseBindMatrices": 0,
//     "joints": [ 1, 2 ],
//     "skeleton": 1
// }
static void
ExportSkin(Writer& w, const Skin& skin)
{
  w.object_open();
  Serialize(w, "name", skin.Name);
  w.key("joints");
  {
    w.array_open();
    for (auto joint : skin.Joints) {
      w.value(joint);
    }
    w.array_close();
  }
  Serialize(w, "inverseBindMatrices", skin.InverseBindMatrices);
  w.object_close();
}

template<typename T, typename V, typename S>
inline void
PushVertices(std::vector<T>& indices,
             const std::shared_ptr<runtimescene::BaseMesh>& mesh,
             uint32_t& index,
             uint32_t drawCount,
             const V& push_vertex,
             bool has_skinning,
             const S& push_skinning)
{
  std::unordered_map<uint32_t, uint32_t> vertexIndexMap;
  for (int i = 0; i < drawCount; ++i, ++index) {
    auto vertex_index = mesh->m_indices[index];
    auto found = vertexIndexMap.find(vertex_index);
    if (found == vertexIndexMap.end()) {
      // new vertex
      // 分割するので index が 0 に戻るので vertex_index ではなく i を使う
      indices.push_back(i);
      vertexIndexMap.insert({ vertex_index, i });
    } else {
      // already exists
      indices.push_back(found->second);
    }
    push_vertex(mesh->m_vertices[vertex_index]);
    if (has_skinning) {
      push_skinning(mesh->m_bindings[vertex_index]);
    }
  }
}

//
// vertex buffer を submesh で分割する
//
// static uint32_t
// ExportMeshPrimitive(Context& c,
//                     const std::shared_ptr<runtimescene::BaseMesh>& mesh,
//                     const runtimescene::Primitive& prim,
//                     uint32_t index)
// {
//   w.object_open();
//
//   if (auto material = prim.Material) {
//     w.key("material");
//     w.value(*material);
//   }
//
//   std::vector<DirectX::XMFLOAT3> positions;
//   std::vector<DirectX::XMFLOAT3> normals;
//   std::vector<DirectX::XMFLOAT2> tex0;
//   auto push_vertex =
//     [&positions, &normals, &tex0](const runtimescene::Vertex& v) {
//       positions.push_back(v.Position);
//       normals.push_back(v.Normal);
//       tex0.push_back(v.Uv);
//     };
//
//   std::vector<runtimescene::ushort4> joints;
//   std::vector<DirectX::XMFLOAT4> weights;
//   auto push_skinning = [&joints,
//                         &weights](const runtimescene::JointBinding& v) {
//     joints.push_back(v.Joints);
//     weights.push_back(v.Weights);
//   };
//   bool has_skinning = mesh->m_bindings.size() == mesh->m_vertices.size();
//
//   if (mesh->m_vertices.size() < 255) {
//     std::vector<uint8_t> indices;
//     PushVertices(indices,
//                  mesh,
//                  index,
//                  prim.DrawCount,
//                  push_vertex,
//                  has_skinning,
//                  push_skinning);
//     auto indices_index = c.m_binWriter.PushAccessor(indices);
//     w.key("indices");
//     w.value(indices_index);
//
//   } else if (mesh->m_vertices.size() < 65535) {
//     std::vector<uint16_t> indices;
//     PushVertices(indices,
//                  mesh,
//                  index,
//                  prim.DrawCount,
//                  push_vertex,
//                  has_skinning,
//                  push_skinning);
//     auto indices_index = c.m_binWriter.PushAccessor(indices);
//     w.key("indices");
//     w.value(indices_index);
//
//   } else {
//     std::vector<uint32_t> indices;
//     PushVertices(indices,
//                  mesh,
//                  index,
//                  prim.DrawCount,
//                  push_vertex,
//                  has_skinning,
//                  push_skinning);
//     auto indices_index = c.m_binWriter.PushAccessor(indices);
//     w.key("indices");
//     w.value(indices_index);
//   }
//
//   w.key("attributes");
//   {
//     w.object_open();
//     {
//       auto position_accessor_index = c.m_binWriter.PushAccessor(positions);
//       w.key(gltfjson::format::VERTEX_POSITION);
//       w.value(position_accessor_index);
//     }
//     {
//       auto normal_accessor_index = c.m_binWriter.PushAccessor(normals);
//       w.key(gltfjson::format::VERTEX_NORMAL);
//       w.value(normal_accessor_index);
//     }
//     {
//       auto tex0_accessor_index = c.m_binWriter.PushAccessor(tex0);
//       w.key(gltfjson::format::VERTEX_UV);
//       w.value(tex0_accessor_index);
//     }
//     // skinning
//     if (has_skinning) {
//       auto joint_accessor_index = c.m_binWriter.PushAccessor(joints);
//       w.key(gltfjson::format::VERTEX_JOINT);
//       w.value(joint_accessor_index);
//       auto weight_accessor_index = c.m_binWriter.PushAccessor(weights);
//       w.key(gltfjson::format::VERTEX_WEIGHT);
//       w.value(weight_accessor_index);
//     }
//     w.object_close();
//   }
//
//   w.object_close();
//
//   return index;
// }

static void
ExportNode(Writer& w, const Node& node)
{
  w.object_open();
  Serialize(w, "name", node.Name);
  // TRS
  // if (node->InitialTransform.Translation.x != 0 ||
  //     node->InitialTransform.Translation.y != 0 ||
  //     node->InitialTransform.Translation.z != 0) {
  //   w.key("translation");
  //   w.array_open();
  //   w.value(node->InitialTransform.Translation.x);
  //   w.value(node->InitialTransform.Translation.y);
  //   w.value(node->InitialTransform.Translation.z);
  //   w.array_close();
  // }
  if (node.Children.size()) {
    w.key("children");
    w.array_open();
    for (auto& child : node.Children) {
      w.value(child);
    }
    w.array_close();
  }
  if (node.Mesh) {
    w.key("mesh");
    w.value(*node.Mesh);
  }
  if (node.Skin) {
    w.key("skin");
    w.value(*node.Skin);
  }
  w.object_close();
}

// static void
// ExportBuffersViewsAccessors(Writer& w, const Root& root)
// {
//   if (c.m_binWriter.Accessors.size()) {
//     c.m_writer.key("accessors");
//     {
//       c.m_writer.array_open();
//       for (auto& accessor : c.m_binWriter.Accessors) {
//         c.m_writer.object_open();
//         c.m_writer.key("bufferView");
//         c.m_writer.value(*accessor.BufferView);
//         c.m_writer.key("count");
//         c.m_writer.value(accessor.Count);
//         c.m_writer.key("byteOffset");
//         c.m_writer.value(0);
//         c.m_writer.key("type");
//         c.m_writer.value(gltfjson::format::type_str(accessor.Type));
//         c.m_writer.key("componentType");
//         c.m_writer.value((int)accessor.ComponentType);
//         c.m_writer.object_close();
//       }
//       c.m_writer.array_close();
//     }
//   }
//   if (c.m_binWriter.BufferViews.size()) {
//     c.m_writer.key("bufferViews");
//     {
//       c.m_writer.array_open();
//       for (auto& bufferView : c.m_binWriter.BufferViews) {
//         c.m_writer.object_open();
//         c.m_writer.key("buffer");
//         c.m_writer.value(0); // for glb
//         c.m_writer.key("byteOffset");
//         c.m_writer.value(bufferView.ByteOffset);
//         c.m_writer.key("byteLength");
//         c.m_writer.value(bufferView.ByteLength);
//         c.m_writer.object_close();
//       }
//       c.m_writer.array_close();
//     }
//
//     c.m_writer.key("buffers");
//     {
//       c.m_writer.array_open();
//       {
//         c.m_writer.object_open();
//         c.m_writer.key("byteLength");
//         c.m_writer.value(c.m_binWriter.BufferPosition);
//         c.m_writer.object_close();
//       }
//       c.m_writer.array_close();
//     }
//   }
// }

// static void
// ExportAnimations(Context& c, const GltfRoot& scene)
// {
//   if (scene.m_animations.empty()) {
//     return;
//   }
//
//   c.m_writer.key("animations");
//   c.m_writer.array_open();
//
//   // perpare
//   for (auto& animation : scene.m_animations) {
//     AnimationExporter animationExporter(c.m_binWriter);
//
//     for (auto& [k, v] : animation->m_translationMap) {
//       animationExporter.ExportAnimationTranslation(k, v);
//     }
//     for (auto& [k, v] : animation->m_rotationMap) {
//       animationExporter.ExportAnimationRotation(k, v);
//     }
//     for (auto& [k, v] : animation->m_scaleMap) {
//       animationExporter.ExportAnimationScale(k, v);
//     }
//     for (auto& [k, v] : animation->m_weightsMap) {
//       animationExporter.ExportAnimationWeights(k, v);
//     }
//
//     c.m_writer.object_open();
//     {
//       c.m_writer.key("name");
//       c.m_writer.value(animation->m_name);
//
//       c.m_writer.key("samplers");
//       c.m_writer.array_open();
//       for (auto& sampler : animationExporter.AnimationSamplers) {
//         c.m_writer.object_open();
//         c.m_writer.key("input");
//         c.m_writer.value(sampler.Input);
//         c.m_writer.key("output");
//         c.m_writer.value(sampler.Output);
//         c.m_writer.key("interpolation");
//         c.m_writer.value(
//           AnimationInterpolationModeNames[(int)sampler.Interpolation]);
//         c.m_writer.object_close();
//       }
//       c.m_writer.array_close();
//
//       c.m_writer.key("channels");
//       c.m_writer.array_open();
//       for (auto& channel : animationExporter.AnimationChannels) {
//         c.m_writer.object_open();
//         c.m_writer.key("sampler");
//         c.m_writer.value(channel.Sampler);
//         c.m_writer.key("target");
//         c.m_writer.object_open();
//         c.m_writer.key("node");
//         c.m_writer.value(channel.Node);
//         c.m_writer.key("path");
//         c.m_writer.value(AnimationTargetNames[(int)channel.Target]);
//         c.m_writer.object_close();
//         c.m_writer.object_close();
//       }
//       c.m_writer.array_close();
//     }
//     c.m_writer.object_close();
//   }
//
//   c.m_writer.array_close();
// }


inline void
Serialize(Writer& w, const Root& src)
{
  w.object_open();
  w.key("asset");
  {
    ExportAsset(w, src.Asset);
  }

  if (src.Images.Size()) {
    w.key("images");
    {
      w.array_open();
      for (auto& image : src.Images) {
        ExportImage(w, image);
      }
      w.array_close();
    }
  }

  if (src.Samplers.Size()) {
    w.key("samplers");
    {
      w.array_open();
      for (auto& sampler : src.Samplers) {
        ExportTextureSampler(w, sampler);
      }
      w.array_close();
    }
  }

  if (src.Textures.Size()) {
    w.key("textures");
    {
      w.array_open();
      for (auto& texture : src.Textures) {
        ExportTexture(w, texture);
      }
      w.array_close();
    }
  }

  if (src.Materials.Size()) {
    w.key("materials");
    {
      w.array_open();
      for (auto& material : src.Materials) {
        ExportMaterial(w, material);
      }
      w.array_close();
    }
  }

  if (src.Meshes.Size()) {
    w.key("meshes");
    {
      w.array_open();
      for (auto& mesh : src.Meshes) {
        ExportMesh(w, mesh);
      }
      w.array_close();
    }
  }

  if (src.Skins.Size()) {
    w.key("skins");
    {
      w.array_open();
      for (auto& skin : src.Skins) {
        ExportSkin(w, skin);
      }
      w.array_close();
    }
  }

  if (src.Nodes.Size()) {
    w.key("nodes");
    {
      w.array_open();
      for (auto& node : src.Nodes) {
        ExportNode(w, node);
      }
      w.array_close();
    }
  }

  if (src.Scenes.Size()) {
    w.key("scenes");
    {
      w.array_open();
      w.object_open();
      w.key("nodes");
      w.array_open();
      // for (auto& root : scene.m_roots) {
      //   w.value(*scene.IndexOf(root));
      // }
      w.array_close();
      w.object_close();
      w.array_close();
    }
    w.key("scene");
    {
      w.value(0);
    }
  }

  // update bin
  // ExportAnimations(c, scene);

  // last
  // ExportBuffersViewsAccessors(w, src);

  //
  // extensions
  //
  // if (scene.m_vrma) {
  //   w.key("extensions");
  //   w.object_open();
  //   {
  //     w.key("VRMC_vrm_animation");
  //     w.object_open();
  //     {
  //       w.key("expressions");
  //       w.object_open();
  //       {
  //         w.key("preset");
  //         w.object_open();
  //         {
  //           w.key("aa");
  //           w.object_open();
  //           {
  //             w.key("node");
  //             w.value(0);
  //           }
  //           w.object_close();
  //         }
  //         w.object_close();
  //       }
  //       w.object_close();
  //     }
  //     w.object_close();
  //   }
  //   w.object_close();
  // }

  w.object_close();
}

}
}
