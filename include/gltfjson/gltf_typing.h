#pragma once
#include "gltf_types.h"
#include "json_tree.h"
#include <optional>
#include <string>
#include <string_view>

namespace gltfjson {
namespace typing {

struct Float3
{
  float x, y, z;
};
struct Float4
{
  float x, y, z, w;
};
struct Float16
{
  float _11, _12, _13, _14;
  float _21, _22, _23, _24;
  float _31, _32, _33, _34;
  float _41, _42, _43, _44;
};

template<size_t N>
struct StringLiteral
{
  constexpr StringLiteral(const char8_t (&str)[N])
  {
    std::copy_n(str, N, value);
  }
  char8_t value[N];
};

template<typename T, StringLiteral lit>
struct JsonArray
{
  tree::NodePtr m_json;
  JsonArray(tree::NodePtr parent)
    : m_json(parent->Get(lit.value))
  {
  }

  struct Iterator
  {
    T operator*() { return {}; }
    Iterator& operator++() { return *this; }
    bool operator!=(const Iterator& rhs) const { return true; }
  };
  uint32_t size() const { return m_json->Size(); }
  T operator[](size_t index) const { return T{ m_json->Get(index) }; }
  Iterator begin() const { return {}; }
  Iterator end() const { return {}; }
};

template<typename T, StringLiteral lit>
struct NumberArray
{
  tree::NodePtr m_json;
  NumberArray(tree::NodePtr parent)
    : m_json(parent->Get(lit.value))
  {
  }

  struct Iterator
  {
    T operator*() { return {}; }
    Iterator& operator++() { return *this; }
    bool operator!=(const Iterator& rhs) const { return true; }
  };
  uint32_t size() const { return m_json->Size(); }
  T operator[](size_t index) const
  {
    return (T)*m_json->Get(index)->Value<float>();
  }
  Iterator begin() const { return {}; }
  Iterator end() const { return {}; }
};

using Id = uint32_t;
struct JsonObject
{
  tree::NodePtr m_json;

  JsonObject(const tree::NodePtr& json)
    : m_json(json)
  {
  }

  template<StringLiteral lit>
  tree::NodePtr m_node() const
  {
    return m_json->Get(lit.value);
  }

  template<StringLiteral lit>
  bool m_bool() const
  {
    if (auto node = m_node<lit>()) {
      if (auto value = node->Value<bool>()) {
        return *value;
      }
    }
    return false;
  }

  template<typename T, StringLiteral lit>
  std::optional<T> m_number() const
  {
    if (auto node = m_node<lit>()) {
      return (T)*node->Value<float>();
    }
    return std::nullopt;
  }

  template<StringLiteral lit>
  std::optional<Id> m_id() const
  {
    if (auto node = m_node<lit>()) {
      return (Id)*node->Value<float>();
    }
    return std::nullopt;
  }

  template<StringLiteral lit>
  std::u8string m_string() const
  {
    if (auto node = m_node<lit>()) {
      if (auto str = node->Value<std::u8string>()) {
        return *str;
      }
    }
    return u8"";
  }

  template<StringLiteral lit>
  std::optional<Float3> m_float3() const
  {
    if (auto node = m_node<lit>()) {
      if (auto array = node->Array()) {
        if (array->size() == 3) {
          Float3 value;
          value.x = *(*array)[0]->Value<float>();
          value.y = *(*array)[1]->Value<float>();
          value.z = *(*array)[2]->Value<float>();
          return value;
        }
      }
    }
    return std::nullopt;
  }
  template<StringLiteral lit>
  std::optional<Float4> m_float4() const
  {
    if (auto node = m_node<lit>()) {
      if (auto array = node->Array()) {
        if (array->size() == 4) {
          Float4 value;
          value.x = *(*array)[0]->Value<float>();
          value.y = *(*array)[1]->Value<float>();
          value.z = *(*array)[2]->Value<float>();
          value.w = *(*array)[3]->Value<float>();
          return value;
        }
      }
    }
    return std::nullopt;
  }
  template<StringLiteral lit>
  std::optional<Float16> m_float16() const
  {
    if (auto node = m_node<lit>()) {
      if (auto array = node->Array()) {
        if (array->size() == 16) {
          Float16 value;
          value._11 = *(*array)[0]->Value<float>();
          value._12 = *(*array)[1]->Value<float>();
          value._13 = *(*array)[2]->Value<float>();
          value._14 = *(*array)[3]->Value<float>();
          value._21 = *(*array)[4]->Value<float>();
          value._22 = *(*array)[5]->Value<float>();
          value._23 = *(*array)[6]->Value<float>();
          value._24 = *(*array)[7]->Value<float>();
          value._31 = *(*array)[8]->Value<float>();
          value._32 = *(*array)[9]->Value<float>();
          value._33 = *(*array)[10]->Value<float>();
          value._34 = *(*array)[11]->Value<float>();
          value._41 = *(*array)[12]->Value<float>();
          value._42 = *(*array)[13]->Value<float>();
          value._43 = *(*array)[14]->Value<float>();
          value._44 = *(*array)[15]->Value<float>();
          return value;
        }
      }
    }
    return std::nullopt;
  }

  template<typename T, StringLiteral lit>
  JsonArray<T, lit> m_array() const
  {
    JsonArray<T, lit> m;
    if (auto node = m_node<lit>()) {
      m.m_json = *node;
    }
    return m;
  }

  template<typename T, StringLiteral lit>
  std::optional<T> m_object() const
  {
    if (auto node = m_node<lit>()) {
      return T{ node };
    }
    return std::nullopt;
  }
};

// template<typename T>
// struct Array
// {
//   std::u8string m_key;
//   tree::NodePtr m_json;
//   struct Iterator
//   {
//     T operator*() { return {}; }
//     Iterator& operator++() { return *this; }
//     bool operator!=(const Iterator& rhs) const { return true; }
//   };
//   uint32_t size() const { return 0; }
//   T operator[](size_t index) const { return {}; }
//   Iterator begin() const { return {}; }
//   Iterator end() const { return {}; }
// };
//
// template<typename T>
// struct Key
// {
//   std::u8string m_key;
//   tree::NodePtr m_parent;
//   std::optional<T> operator()() const { return std::nullopt; }
//   // void operator()(const T& t);
// };
//
// struct ChildOfRootProperty
// {
//   Key<std::u8string> Name{ u8"name" };
// };
//
// template<typename T, size_t N>
// struct FixedArray : Key<std::array<T, N>>
// {};

//
// gltf
//

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/buffer.schema.json
struct Buffer : JsonObject
{
  using JsonObject::JsonObject;
  auto Uri() const { return m_string<u8"uri">(); };
  auto ByteLength() const { return m_number<uint32_t, u8"byteLength">(); };
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/bufferView.schema.json
struct BufferView : JsonObject
{
  using JsonObject::JsonObject;
  auto Buffer() const { return m_id<u8"buffer">(); };
  auto ByteOffset() const { return m_number<uint32_t, u8"byteOffset">(); };
  auto ByteLength() const { return m_number<uint32_t, u8"byteLength">(); };
  auto ByteStride() const { return m_number<uint32_t, u8"byteStride">(); };
  auto Target() const { return m_number<format::Targets, u8"target">(); };
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/accessor.sparse.indices.schema.json
struct SparseIndices : JsonObject
{
  using JsonObject::JsonObject;
  auto BufferView() const { return m_id<u8"bufferView">(); };
  auto ByteOffset() const { return m_number<uint32_t, u8"byteOffset">(); }
  auto ComponentType() const
  {
    return m_number<format::ComponentTypes, u8"componentType">();
  }
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/accessor.sparse.values.schema.json
struct SparseValues : JsonObject
{
  using JsonObject::JsonObject;
  auto BufferView() const { return m_id<u8"bufferView">(); }
  auto ByteOffset() const { return m_number<uint32_t, u8"byteOffset">(); }
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/accessor.sparse.schema.json
struct Sparse : JsonObject
{
  using JsonObject::JsonObject;
  auto Count() const { return m_number<uint32_t, u8"count">(); }
  auto Indices() const { return m_object<SparseIndices, u8"indices">(); }
  auto Values() const { return m_object<SparseValues, u8"values">(); }
};

struct Accessor : JsonObject
{
  Accessor(const tree::NodePtr& json)
    : JsonObject(json)
    , Max(json)
    , Min(json)
  {
  }
  auto BufferView() const { return m_id<u8"bufferView">(); }
  auto ByteOffset() const { return m_number<uint32_t, u8"byteOffset">(); }
  auto ComponentType() const
  {
    return m_number<format::ComponentTypes, u8"componentType">();
  }
  auto Normalized() const { return m_bool<u8"normalized">(); }
  auto Count() const { return m_number<uint32_t, u8"count">(); }
  auto Type() const { return m_string<u8"type">(); }
  NumberArray<float, u8"max"> Max;
  NumberArray<float, u8"min"> Min;
  auto Sparse() const { return m_object<typing::Sparse, u8"sparse">(); }
};

struct Camera : JsonObject
{
  using JsonObject::JsonObject;
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/image.schema.json
struct Image : JsonObject
{
  using JsonObject::JsonObject;
  auto Uri() const { return m_string<u8"uri">(); }
  auto MimeTypel() const { return m_string<u8"mimeType">(); }
  auto BufferView() const { return m_id<u8"bufferView">(); }
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/sampler.schema.json
struct Sampler : JsonObject
{
  using JsonObject::JsonObject;
  auto MagFilter() const
  {
    return m_number<format::TextureMagFilter, u8"magFilter">();
  };
  auto MinFilter() const
  {
    return m_number<format::TextureMinFilter, u8"minFilter">();
  };
  auto WrapS() const { return m_number<format::TextureWrap, u8"wrapS">(); }
  auto WrapT() const { return m_number<format::TextureWrap, u8"wrapT">(); }
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/texture.schema.json
struct Texture : JsonObject
{
  using JsonObject::JsonObject;
  auto Sampler() const { return m_id<u8"sampler">(); }
  auto Source() const { return m_id<u8"source">(); }
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/textureInfo.schema.json
struct TextureInfo : JsonObject
{
  using JsonObject::JsonObject;
  auto Index() const { return m_id<u8"index">(); }
  auto TexCoord() const { return m_number<uint32_t, u8"texCoord">(); }
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/material.normalTextureInfo.schema.json
struct NormalTextureInfo : TextureInfo
{
  using TextureInfo::TextureInfo;
  auto Scale() const { return m_number<float, u8"scale">(); }
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/material.occlusionTextureInfo.schema.json
struct OcclusionTextureInfo : TextureInfo
{
  using TextureInfo::TextureInfo;
  auto Strength() const { return m_number<float, u8"strength">(); };
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/material.pbrMetallicRoughness.schema.json
struct PbrMetallicRoughness : JsonObject
{
  using JsonObject::JsonObject;
  auto BaseColorFactor() const { return m_float4<u8"baseColorFactor">(); }
  auto BaseColorTexture() const
  {
    return m_object<TextureInfo, u8"baseColorTexture">();
  }
  auto MetallicFactor() const { return m_number<float, u8"metallicFactor">(); };
  auto RoughnessFactor() const
  {
    return m_number<float, u8"roughnessFactor">();
  };
  auto MetallicRoughnessTexture() const
  {
    return m_object<TextureInfo, u8"metallicRoughnessTexture">();
  };
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/material.schema.json
struct Material : JsonObject
{
  using JsonObject::JsonObject;
  auto PbrMetallicRoughness() const
  {
    return m_object<typing::PbrMetallicRoughness, u8"pbrMetallicRoughness">();
  }
  auto NormalTexture() const
  {
    return m_object<NormalTextureInfo, u8"normalTexture">();
  }
  auto OcclusionTexture() const
  {
    return m_object<OcclusionTextureInfo, u8"occlusionTexture">();
  }
  auto EmissiveTexture() const
  {
    return m_object<TextureInfo, u8"emissiveTexture">();
  }
  auto EmissiveFactor() const { return m_float3<u8"emissiveFactor">(); }
  auto AlphaMode() const
  {
    return m_number<format::AlphaModes, u8"alphaMode">();
  }
  auto AlphaCutoff() const { return m_number<float, u8"alphaCutoff">(); };
  auto DoubleSided() const { return m_number<bool, u8"doubleSided">(); };
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/skin.schema.json
struct Skin : JsonObject
{
  Skin(const tree::NodePtr& json)
    : JsonObject(json)
    , Joints(json)
  {
  }
  auto InverseBindMatrices() const { return m_id<u8"inverseBindMatrices">(); }
  auto Skeleton() const { return m_id<u8"skeleton">(); }
  NumberArray<uint32_t, u8"joints"> Joints;
};

struct MeshPrimitiveAttributes : JsonObject
{
  using JsonObject::JsonObject;
  auto COLOR_0() const { return m_id<u8"COLOR_0">(); }
  auto JOINTS_0() const { return m_id<u8"JOINTS_0">(); }
  auto NORMAL() const { return m_id<u8"NORMAL">(); }
  auto POSITION() const { return m_id<u8"POSITION">(); }
  auto TANGENT() const { return m_id<u8"TANGENT">(); }
  auto TEXCOORD_0() const { return m_id<u8"TEXCOORD_0">(); }
  auto TEXCOORD_1() const { return m_id<u8"TEXCOORD_1">(); }
  auto TEXCOORD_2() const { return m_id<u8"TEXCOORD_2">(); }
  auto TEXCOORD_3() const { return m_id<u8"TEXCOORD_3">(); }
  auto WEIGHTS_0() const { return m_id<u8"WEIGHTS_0">(); }
};

struct MeshPrimitiveMorphTarget : JsonObject
{
  using JsonObject::JsonObject;
  auto POSITION() const { return m_id<u8"POSITION">(); }
  auto NORMAL() const { return m_id<u8"NORMAL">(); }
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/mesh.primitive.schema.json
struct MeshPrimitive : JsonObject
{
  MeshPrimitive(const tree::NodePtr& json)
    : JsonObject(json)
    , Targets(json)
  {
  }
  auto Attributes() const
  {
    return m_object<MeshPrimitiveAttributes, u8"attributes">();
  }
  auto Indices() const { return m_id<u8"indices">(); }
  auto Material() const { return m_id<u8"material">(); }
  auto Mode() const
  {
    return m_number<format::MeshPrimitiveTopology, u8"mode">();
  };
  JsonArray<MeshPrimitiveMorphTarget, u8"targets"> Targets;
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/mesh.schema.json
struct Mesh : JsonObject
{
  Mesh(const tree::NodePtr& json)
    : JsonObject(json)
    , Primitives(json)
    , Weights(json)
  {
  }
  JsonArray<MeshPrimitive, u8"primitives"> Primitives;
  NumberArray<float, u8"weights"> Weights;
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/node.schema.json
struct Node : JsonObject
{
  Node(const tree::NodePtr& json)
    : JsonObject(json)
    , Children(json)
    , Weights(json)
  {
  }
  auto Camera() const { return m_id<u8"camera">(); }
  NumberArray<uint32_t, u8"children"> Children;
  auto Skin() const { return m_id<u8"skin">(); }
  auto FixedArray() const { return m_float16<u8"matrix">(); }
  auto Mesh() const { return m_id<u8"mesh">(); }
  auto Rotation() const { return m_float4<u8"rotation">(); }
  auto Scale() const { return m_float3<u8"scale">(); }
  auto Translation() const { m_float3<u8"translation">(); }
  NumberArray<float, u8"weights"> Weights;
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/animation.sampler.schema.json
struct AnimationSampler : JsonObject
{
  using JsonObject::JsonObject;
  auto Input() const { return m_id<u8"input">(); }
  auto Interpolation() const
  {
    return m_number<format::InterpolationTypes, u8"interpolation">();
  }
  auto Output() const { return m_id<u8"output">(); };
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/animation.channel.target.schema.json
struct AnimationTarget : JsonObject
{
  using JsonObject::JsonObject;
  auto Node() const { return m_id<u8"node">(); }
  auto Path() const { return m_number<format::PathTypes, u8"path">(); }
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/animation.channel.schema.json
struct AnimationChannel : JsonObject
{
  using JsonObject::JsonObject;
  auto Sampler() const { return m_id<u8"sampler">(); }
  auto Target() const { return m_object<AnimationTarget, u8"target">(); }
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/animation.schema.json
struct Animation : JsonObject
{
  Animation(const tree::NodePtr& json)
    : JsonObject(json)
    , Channels(json)
    , Samplers(json)
  {
  }
  JsonArray<AnimationChannel, u8"channels"> Channels;
  JsonArray<AnimationSampler, u8"samplers"> Samplers;
};

struct Scene : JsonObject
{
  Scene(const tree::NodePtr& json)
    : JsonObject(json)
    , Nodes(json)
  {
  }
  NumberArray<uint32_t, u8"nodes"> Nodes;
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/asset.schema.json
struct Asset : JsonObject
{
  using JsonObject::JsonObject;

  auto Copyright() const { return m_string<u8"copyright">(); };
  auto Generator() const { return m_string<u8"generator">(); };
  auto Version() const { return m_string<u8"version">(); };
  auto MinVersion() const { return m_string<u8"minVersion">(); };
};

struct Root : JsonObject
{
  Root(const tree::NodePtr& json)
    : JsonObject(json)
    , Accessors(json)
    , Animations(json)
    , Buffers(json)
    , BufferViews(json)
    , Cameras(json)
    , Images(json)
    , Textures(json)
    , Materials(json)
    , Meshes(json)
    , Nodes(json)
    , Samplers(json)
    , Scenes(json)
    , Skins(json)
  {
    m_json = json;
  }

  JsonArray<Accessor, u8"accessors"> Accessors;
  JsonArray<Animation, u8"animations"> Animations;
  auto Asset() const { return m_object<typing::Asset, u8"asset">(); }
  JsonArray<Buffer, u8"buffers"> Buffers;
  JsonArray<BufferView, u8"bufferViews"> BufferViews;
  JsonArray<Camera, u8"cameras"> Cameras;
  JsonArray<Image, u8"images"> Images;
  JsonArray<Texture, u8"textures"> Textures;
  JsonArray<Material, u8"materials"> Materials;
  JsonArray<Mesh, u8"meshes"> Meshes;
  JsonArray<Node, u8"nodes"> Nodes;
  JsonArray<Sampler, u8"samplers"> Samplers;
  auto Scene() const { return m_number<uint32_t, u8"scene">(); }
  JsonArray<typing::Scene, u8"scenes"> Scenes;
  JsonArray<Skin, u8"skins"> Skins;
};

}
}
