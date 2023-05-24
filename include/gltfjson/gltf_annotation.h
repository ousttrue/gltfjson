#pragma once
#include "gltf_types.h"
#include "json_tree.h"
#include <optional>
#include <string>
#include <string_view>

namespace gltfjson {
namespace annotation {

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
    return (T)*m_json->Get(index)->Value<double>();
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

  template<typename T, StringLiteral lit>
  std::optional<T> m_number() const
  {
    if (auto node = m_node<lit>()) {
      return (T)*node->Value<double>();
    }
    return std::nullopt;
  }

  template<StringLiteral lit>
  std::optional<Id> m_id() const
  {
    if (auto node = m_node<lit>()) {
      return (Id)*node->Value<double>();
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
        if (array->m_values.size() == 3) {
          Float3 value;
          value.x = *array->m_values[0]->Value<double>();
          value.y = *array->m_values[1]->Value<double>();
          value.z = *array->m_values[2]->Value<double>();
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
        if (array->m_values.size() == 4) {
          Float4 value;
          value.x = *array->m_values[0]->Value<double>();
          value.y = *array->m_values[1]->Value<double>();
          value.z = *array->m_values[2]->Value<double>();
          value.w = *array->m_values[3]->Value<double>();
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
        if (array->m_values.size() == 16) {
          Float16 value;
          value._11 = *array->m_values[0]->Value<double>();
          value._12 = *array->m_values[1]->Value<double>();
          value._13 = *array->m_values[2]->Value<double>();
          value._14 = *array->m_values[3]->Value<double>();
          value._21 = *array->m_values[4]->Value<double>();
          value._22 = *array->m_values[5]->Value<double>();
          value._23 = *array->m_values[6]->Value<double>();
          value._24 = *array->m_values[7]->Value<double>();
          value._31 = *array->m_values[8]->Value<double>();
          value._32 = *array->m_values[9]->Value<double>();
          value._33 = *array->m_values[10]->Value<double>();
          value._34 = *array->m_values[11]->Value<double>();
          value._41 = *array->m_values[12]->Value<double>();
          value._42 = *array->m_values[13]->Value<double>();
          value._43 = *array->m_values[14]->Value<double>();
          value._44 = *array->m_values[15]->Value<double>();
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
};

template<typename T>
struct Array
{
  std::u8string m_key;
  tree::NodePtr m_json;
  struct Iterator
  {
    T operator*() { return {}; }
    Iterator& operator++() { return *this; }
    bool operator!=(const Iterator& rhs) const { return true; }
  };
  uint32_t size() const { return 0; }
  T operator[](size_t index) const { return {}; }
  Iterator begin() const { return {}; }
  Iterator end() const { return {}; }
};

template<typename T>
struct Key
{
  std::u8string m_key;
  tree::NodePtr m_parent;
  std::optional<T> operator()() const { return std::nullopt; }
  // void operator()(const T& t);
};

struct ChildOfRootProperty
{
  Key<std::u8string> Name{ u8"name" };
};

template<typename T, size_t N>
struct FixedArray : Key<std::array<T, N>>
{};

//
// gltf
//

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/buffer.schema.json
struct Buffer : ChildOfRootProperty
{
  Key<std::u8string> Uri{ u8"uri" };
  Key<uint32_t> ByteLength{ u8"byteLength" };
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/bufferView.schema.json
struct BufferView : ChildOfRootProperty
{
  Key<Id> Buffer{ u8"Buffer" };
  Key<uint32_t> ByteOffset{ u8"byteOffset" };
  Key<uint32_t> ByteLength{ u8"byteLength" };
  Key<uint32_t> ByteStride{ u8"byteStride" };
  Key<format::Targets> Target{ u8"target" };
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/accessor.sparse.indices.schema.json
struct SparseIndices
{
  Key<Id> BufferView{ u8"BufferView" };
  Key<uint32_t> ByteOffset{ u8"byteOffset" };
  Key<format::ComponentTypes> ComponentType{ u8"componentType" };
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/accessor.sparse.values.schema.json
struct SparseValues
{
  Key<Id> BufferView{ u8"bufferView" };
  Key<uint32_t> ByteOffset{ u8"byteOffset" };
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/accessor.sparse.schema.json
struct Sparse
{
  Key<uint32_t> Count{ u8"count" };
  Key<SparseIndices> Indices{ u8"indices" };
  Key<SparseValues> Values{ u8"values" };
};

struct Accessor : ChildOfRootProperty
{
  Key<Id> BufferView{ u8"bufferView" };
  Key<uint32_t> ByteOffset{ u8"byteOffset" };
  Key<format::ComponentTypes> ComponentType{ u8"componentType" };
  Key<bool> Normalized{ u8"normalized" };
  Key<uint32_t> Count{ u8"count" };
  Key<format::Types> Type{ u8"tyee" };
  Array<float> Max{ u8"max" };
  Array<float> Min{ u8"min" };
  Key<Sparse> Sparse{ u8"sparse" };

  uint32_t Stride() const { return ComponentSize() * TypeCount(); }
  uint32_t ComponentSize() const { return 4; }
  uint32_t TypeCount() const { return 1; }
};

struct Camera : ChildOfRootProperty
{};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/image.schema.json
struct Image : ChildOfRootProperty
{
  Key<std::u8string> Uri{ u8"uri" };
  Key<std::u8string> MimeType{ u8"mimeType" };
  Key<Id> BufferView{ u8"bufferView" };
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/sampler.schema.json
struct Sampler : ChildOfRootProperty
{
  Key<format::TextureMagFilter> MagFilter{ u8"magFilter" };
  Key<format::TextureMinFilter> MinFilter{ u8"minFilter" };
  Key<format::TextureWrap> WrapS{ u8"wrapS" };
  Key<format::TextureWrap> WrapT{ u8"wrapT" };
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/texture.schema.json
struct Texture : ChildOfRootProperty
{
  Key<Id> Sampler{ u8"sampler" };
  Key<Id> Source{ u8"source" };
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/textureInfo.schema.json
struct TextureInfo
{
  Key<Id> Index{ u8"index" };
  Key<uint32_t> TexCoord{ u8"texCoord" };
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/material.normalTextureInfo.schema.json
struct NormalTextureInfo : TextureInfo
{
  Key<float> Scale{ u8"scale" };
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/material.occlusionTextureInfo.schema.json
struct OcclusionTextureInfo : TextureInfo
{
  Key<float> Strength{ u8"strength" };
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/material.pbrMetallicRoughness.schema.json
struct PbrMetallicRoughness
{
  FixedArray<float, 4> BaseColorFactor{ u8"baseColorFactor" };
  Key<TextureInfo> BaseColorTexture{ u8"baseColorTexture" };
  Key<float> MetallicFactor{ u8"metallicFactor" };
  Key<float> RoughnessFactor{ u8"roughnessFactor" };
  Key<TextureInfo> MetallicRoughnessTexture{ u8"metallicRoughnessTexture" };
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/material.schema.json
struct Material : ChildOfRootProperty
{
  Key<PbrMetallicRoughness> PbrMetallicRoughness{ u8"pbrMetallicRoughness" };
  Key<NormalTextureInfo> NormalTexture{ u8"normalTexture" };
  Key<OcclusionTextureInfo> OcclusionTexture{ u8"occlusionTexture" };
  Key<TextureInfo> EmissiveTexture{ u8"emissiveTexture" };
  FixedArray<float, 3> EmissiveFactor{ u8"emissiveFactor" };
  Key<format::AlphaModes> AlphaMode{ u8"alphaMode" };
  Key<float> AlphaCutoff{ u8"alphaCutoff" };
  Key<bool> DoubleSided{ u8"doubleSided" };
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/skin.schema.json
struct Skin : ChildOfRootProperty
{
  Key<Id> InverseBindMatrices{ u8"inverseBindMatrices" };
  Key<Id> Skeleton{ u8"skeleton" };
  Array<uint32_t> Joints{ u8"joints" };
};

struct MeshPrimitiveAttributes
{
  Key<Id> COLOR_0{ u8"COLOR_0" };
  Key<Id> JOINTS_0{ u8"JOINTS_0" };
  Key<Id> NORMAL{ u8"NORMAL" };
  Key<Id> POSITION{ u8"POSITION" };
  Key<Id> TANGENT{ u8"TANGENT" };
  Key<Id> TEXCOORD_0{ u8"TEXCOORD_0" };
  Key<Id> TEXCOORD_1{ u8"TEXCOORD_1" };
  Key<Id> TEXCOORD_2{ u8"TEXCOORD_2" };
  Key<Id> TEXCOORD_3{ u8"TEXCOORD_3" };
  Key<Id> WEIGHTS_0{ u8"WEIGHTS_0" };
};

struct MeshPrimitiveMorphTarget
{
  Key<Id> POSITION{ u8"POSITION" };
  Key<Id> NORMAL{ u8"NORMAL" };
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/mesh.primitive.schema.json
struct MeshPrimitive
{
  Key<MeshPrimitiveAttributes> Attributes{ u8"attributes" };
  Key<Id> Indices{ u8"indices" };
  Key<Id> Material{ u8"material" };
  Key<format::MeshPrimitiveTopology> Mode{ u8"mode" };
  Array<MeshPrimitiveMorphTarget> Targets{ u8"targets" };
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/mesh.schema.json
struct Mesh : ChildOfRootProperty
{
  Array<MeshPrimitive> Primitives{ u8"primitives" };
  Array<float> Weights{ u8"weights" };
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
struct AnimationSampler
{
  Key<Id> Input{ u8"input" };
  Key<format::InterpolationTypes> Interpolation{ u8"interpolation" };
  Key<Id> Output{ u8"output" };
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/animation.channel.target.schema.json
struct AnimationTarget
{
  Key<Id> Node{ u8"node" };
  Key<format::PathTypes> Path{ u8"path" };
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/animation.channel.schema.json
struct AnimationChannel
{
  Key<Id> Sampler{ u8"sampler" };
  Key<AnimationTarget> Target{ u8"target" };
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/animation.schema.json
struct Animation : ChildOfRootProperty
{
  Array<AnimationChannel> Channels{ u8"channels" };
  Array<AnimationSampler> Samplers{ u8"samplers" };
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
    , Scenes(json)
    , Nodes(json)
  {
    m_json = json;
  }

  Array<Accessor> Accessors{ u8"accessors" };
  Array<Animation> Animations{ u8"animations" };
  auto Asset() const { return annotation::Asset{ m_node<u8"asset">() }; };
  Array<Buffer> Buffers{ u8"buffers" };
  Array<BufferView> BufferViews{ u8"bufferViews" };
  Array<Camera> Cameras{ u8"cameras" };
  Array<Image> Images{ u8"images" };
  Array<Texture> Textures{ u8"textures" };
  Array<Material> Materials{ u8"materials" };
  Array<Mesh> Meshes{ u8"meshes" };
  JsonArray<Node, u8"nodes"> Nodes;
  Array<Sampler> Samplers{ u8"samplers" };

  auto Scene() const { return m_number<uint32_t, u8"scene">(); }
  JsonArray<annotation::Scene, u8"scenes"> Scenes;

  Array<Skin> Skins{ u8"skins" };
};
}
}