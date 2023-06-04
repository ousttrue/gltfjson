#pragma once
#include "gltf_types.h"
#include "json_tree.h"
#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace gltfjson {

template<typename T>
inline T
value_or(const float* p, T default_value = {})
{
  if (p) {
    return (T)*p;
  } else {
    return default_value;
  }
}

template<size_t N>
struct StringLiteral
{
  constexpr StringLiteral(const char8_t (&str)[N])
  {
    std::copy_n(str, N, value);
  }
  char8_t value[N];
};

template<typename T>
struct JsonArrayBase
{
  struct Iterator
  {
    std::vector<tree::NodePtr>::iterator m_it;
    T operator*() { return T{ *m_it }; }
    Iterator& operator++()
    {
      ++m_it;
      return *this;
    }
    bool operator!=(const Iterator& rhs) const { return rhs.m_it != m_it; }
  };

  tree::NodePtr m_json;
  JsonArrayBase(const tree::NodePtr& json)
    : m_json(json)
  {
    // assert(m_json);
  }
  uint32_t size() const { return m_json ? m_json->Size() : 0; }
  T operator[](size_t index) const { return T{ m_json->Get(index) }; }
  Iterator begin() const
  {
    return m_json ? Iterator{ m_json->Array()->begin() } : Iterator{};
  }
  Iterator end() const
  {
    return m_json ? Iterator{ m_json->Array()->end() } : Iterator{};
  }
};

template<typename T, StringLiteral lit>
struct JsonArray : JsonArrayBase<T>
{
  JsonArray(tree::NodePtr parent)
    : JsonArrayBase<T>(parent->Get(lit.value))
  {
  }
};

template<typename T, StringLiteral lit>
struct NumberArray
{
  struct Iterator
  {
    std::vector<tree::NodePtr>::iterator m_it;
    T operator*()
    {
      auto p = (*m_it)->Ptr<float>();
      return (T)*p;
    }
    Iterator& operator++()
    {
      ++m_it;
      return *this;
    }
    bool operator!=(const Iterator& rhs) const { return rhs.m_it != m_it; }
  };

  tree::NodePtr m_json;
  NumberArray(tree::NodePtr parent)
    : m_json(parent->Get(lit.value))
  {
  }
  uint32_t size() const { return m_json ? m_json->Size() : 0; }
  T operator[](size_t index) const
  {
    return (T)*m_json->Get(index)->Ptr<float>();
  }
  Iterator begin() const
  {
    return m_json ? Iterator{ m_json->Array()->begin() } : Iterator{};
  }
  Iterator end() const
  {
    return m_json ? Iterator{ m_json->Array()->end() } : Iterator{};
  }
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
  T* m_ptr() const
  {
    if (auto node = m_node<lit>()) {
      return node->template Ptr<T>();
    }
    return nullptr;
  }

  template<StringLiteral lit>
  std::optional<Id> m_id() const
  {
    if (auto node = m_node<lit>()) {
      return (Id)*node->template Ptr<float>();
    }
    return std::nullopt;
  }

  template<StringLiteral lit>
  std::u8string m_string() const
  {
    if (auto node = m_node<lit>()) {
      return node->U8String();
    }
    return u8"";
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

//
// gltf
//
struct Extensions : JsonObject
{
  using JsonObject::JsonObject;
};

struct Extras : JsonObject
{
  using JsonObject::JsonObject;
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/glTFProperty.schema.json
struct GltfProperty : JsonObject
{
  using JsonObject::JsonObject;
  auto Extensions() const { return m_json->Get(u8"extensions"); }
  auto Extras() const { return m_json->Get(u8"extras"); }
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/glTFChildOfRootProperty.schema.json
struct ChildOfRootProperty : GltfProperty
{
  using GltfProperty::GltfProperty;
  auto Name() const { return m_string<u8"name">(); }
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/buffer.schema.json
struct Buffer : ChildOfRootProperty
{
  using ChildOfRootProperty::ChildOfRootProperty;
  auto Uri() const { return m_string<u8"uri">(); };
  auto ByteLength() const { return m_ptr<float, u8"byteLength">(); };
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/bufferView.schema.json
struct BufferView : ChildOfRootProperty
{
  using ChildOfRootProperty::ChildOfRootProperty;
  auto Buffer() const { return m_id<u8"buffer">(); };
  auto ByteOffset() const { return m_ptr<float, u8"byteOffset">(); };
  auto ByteLength() const { return m_ptr<float, u8"byteLength">(); };
  auto ByteStride() const { return m_ptr<float, u8"byteStride">(); };
  auto Target() const { return m_ptr<float, u8"target">(); };
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/accessor.sparse.indices.schema.json
struct SparseIndices : JsonObject
{
  using JsonObject::JsonObject;
  auto BufferView() const { return m_id<u8"bufferView">(); };
  auto ByteOffset() const { return m_ptr<float, u8"byteOffset">(); }
  auto ComponentType() const { return m_ptr<float, u8"componentType">(); }
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/accessor.sparse.values.schema.json
struct SparseValues : JsonObject
{
  using JsonObject::JsonObject;
  auto BufferView() const { return m_id<u8"bufferView">(); }
  auto ByteOffset() const { return m_ptr<float, u8"byteOffset">(); }
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/accessor.sparse.schema.json
struct Sparse : JsonObject
{
  using JsonObject::JsonObject;
  auto Count() const { return m_ptr<float, u8"count">(); }
  auto Indices() const { return m_object<SparseIndices, u8"indices">(); }
  auto Values() const { return m_object<SparseValues, u8"values">(); }
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/accessor.schema.json
struct Accessor : ChildOfRootProperty
{
  Accessor(const tree::NodePtr& json)
    : ChildOfRootProperty(json)
    , Max(json)
    , Min(json)
  {
  }
  auto BufferView() const { return m_id<u8"bufferView">(); }
  auto ByteOffset() const { return m_ptr<float, u8"byteOffset">(); }
  auto ComponentType() const { return m_ptr<float, u8"componentType">(); }
  auto Normalized() const { return m_ptr<bool, u8"normalized">(); }
  auto Count() const { return m_ptr<float, u8"count">(); }
  auto Type() const { return m_string<u8"type">(); }
  NumberArray<float, u8"max"> Max;
  NumberArray<float, u8"min"> Min;
  auto Sparse() const { return m_object<gltfjson::Sparse, u8"sparse">(); }

  uint32_t Stride() const
  {
    return *component_size((ComponentTypes)*ComponentType()) *
           *type_count(Type());
  }
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/camera.schema.json
struct Camera : ChildOfRootProperty
{
  using ChildOfRootProperty::ChildOfRootProperty;
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/image.schema.json
struct Image : ChildOfRootProperty
{
  using ChildOfRootProperty::ChildOfRootProperty;
  auto Uri() const { return m_string<u8"uri">(); }
  auto MimeTypel() const { return m_string<u8"mimeType">(); }
  auto BufferView() const { return m_id<u8"bufferView">(); }
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/sampler.schema.json
struct Sampler : ChildOfRootProperty
{
  using ChildOfRootProperty::ChildOfRootProperty;
  auto MagFilter() const { return m_ptr<float, u8"magFilter">(); };
  auto MinFilter() const { return m_ptr<float, u8"minFilter">(); };
  auto WrapS() const { return m_ptr<float, u8"wrapS">(); }
  auto WrapT() const { return m_ptr<float, u8"wrapT">(); }
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/texture.schema.json
struct Texture : ChildOfRootProperty
{
  using ChildOfRootProperty::ChildOfRootProperty;
  auto Sampler() const { return m_id<u8"sampler">(); }
  auto Source() const { return m_id<u8"source">(); }
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/textureInfo.schema.json
struct TextureInfo : JsonObject
{
  using JsonObject::JsonObject;
  auto Index() const { return m_id<u8"index">(); }
  auto TexCoord() const { return m_ptr<float, u8"texCoord">(); }
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/material.normalTextureInfo.schema.json
struct NormalTextureInfo : TextureInfo
{
  using TextureInfo::TextureInfo;
  auto Scale() const { return m_ptr<float, u8"scale">(); }
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/material.occlusionTextureInfo.schema.json
struct OcclusionTextureInfo : TextureInfo
{
  using TextureInfo::TextureInfo;
  auto Strength() const { return m_ptr<float, u8"strength">(); };
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/material.pbrMetallicRoughness.schema.json
struct PbrMetallicRoughness : JsonObject
{
  PbrMetallicRoughness(const tree::NodePtr& json)
    : JsonObject(json)
    , BaseColorFactor(json)
  {
  }
  NumberArray<float, u8"baseColorFactor"> BaseColorFactor;
  auto BaseColorTexture() const
  {
    return m_object<TextureInfo, u8"baseColorTexture">();
  }
  auto MetallicFactor() const { return m_ptr<float, u8"metallicFactor">(); };
  auto RoughnessFactor() const { return m_ptr<float, u8"roughnessFactor">(); };
  auto MetallicRoughnessTexture() const
  {
    return m_object<TextureInfo, u8"metallicRoughnessTexture">();
  };
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/material.schema.json
struct Material : ChildOfRootProperty
{
  Material(const tree::NodePtr& json)
    : ChildOfRootProperty(json)
    , EmissiveFactor(json)
  {
  }
  auto PbrMetallicRoughness() const
  {
    return m_object<gltfjson::PbrMetallicRoughness, u8"pbrMetallicRoughness">();
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
  NumberArray<float, u8"emissiveFactor"> EmissiveFactor;
  auto AlphaMode() const { return m_string<u8"alphaMode">(); }
  auto AlphaCutoff() const { return m_ptr<float, u8"alphaCutoff">(); };
  auto DoubleSided() const { return m_ptr<bool, u8"doubleSided">(); };
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/skin.schema.json
struct Skin : ChildOfRootProperty
{
  Skin(const tree::NodePtr& json)
    : ChildOfRootProperty(json)
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

  bool operator==(const MeshPrimitiveAttributes& rhs) const
  {
    return COLOR_0() == rhs.COLOR_0() && JOINTS_0() == rhs.JOINTS_0() &&
           NORMAL() == rhs.NORMAL() && POSITION() == rhs.POSITION() &&
           TANGENT() == rhs.TANGENT() && TEXCOORD_0() == rhs.TEXCOORD_0() &&
           TEXCOORD_1() == rhs.TEXCOORD_1() &&
           TEXCOORD_2() == rhs.TEXCOORD_2() &&
           TEXCOORD_3() == rhs.TEXCOORD_3() && WEIGHTS_0() == rhs.WEIGHTS_0();
  }
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
  auto Mode() const { return m_ptr<float, u8"mode">(); };
  JsonArray<MeshPrimitiveMorphTarget, u8"targets"> Targets;
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/mesh.schema.json
struct Mesh : ChildOfRootProperty
{
  Mesh(const tree::NodePtr& json)
    : ChildOfRootProperty(json)
    , Primitives(json)
    , Weights(json)
  {
  }
  JsonArray<MeshPrimitive, u8"primitives"> Primitives;
  NumberArray<float, u8"weights"> Weights;
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/node.schema.json
struct Node : ChildOfRootProperty
{
  Node(const tree::NodePtr& json)
    : ChildOfRootProperty(json)
    , Children(json)
    , Matrix(json)
    , Rotation(json)
    , Scale(json)
    , Translation(json)
    , Weights(json)
  {
  }
  auto Camera() const { return m_id<u8"camera">(); }
  NumberArray<uint32_t, u8"children"> Children;
  auto Skin() const { return m_id<u8"skin">(); }
  NumberArray<float, u8"matrix"> Matrix;
  auto Mesh() const { return m_id<u8"mesh">(); }
  NumberArray<float, u8"rotation"> Rotation;
  NumberArray<float, u8"scale"> Scale;
  NumberArray<float, u8"translation"> Translation;
  NumberArray<float, u8"weights"> Weights;
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/animation.sampler.schema.json
struct AnimationSampler : JsonObject
{
  using JsonObject::JsonObject;
  auto Input() const { return m_id<u8"input">(); }
  auto Interpolation() const { return m_ptr<float, u8"interpolation">(); }
  auto Output() const { return m_id<u8"output">(); };
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/animation.channel.target.schema.json
struct AnimationTarget : JsonObject
{
  using JsonObject::JsonObject;
  auto Node() const { return m_id<u8"node">(); }
  auto Path() const { return m_string<u8"path">(); }
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/animation.channel.schema.json
struct AnimationChannel : JsonObject
{
  using JsonObject::JsonObject;
  auto Sampler() const { return m_id<u8"sampler">(); }
  auto Target() const { return m_object<AnimationTarget, u8"target">(); }
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/animation.schema.json
struct Animation : ChildOfRootProperty
{
  Animation(const tree::NodePtr& json)
    : ChildOfRootProperty(json)
    , Channels(json)
    , Samplers(json)
  {
  }
  JsonArray<AnimationChannel, u8"channels"> Channels;
  JsonArray<AnimationSampler, u8"samplers"> Samplers;
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/scene.schema.json
struct Scene : ChildOfRootProperty
{
  Scene(const tree::NodePtr& json)
    : ChildOfRootProperty(json)
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

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/glTF.schema.json
struct Root : GltfProperty
{
  Root(const tree::NodePtr& json)
    : GltfProperty(json)
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
  auto Asset() const { return m_object<gltfjson::Asset, u8"asset">(); }
  JsonArray<Buffer, u8"buffers"> Buffers;
  JsonArray<BufferView, u8"bufferViews"> BufferViews;
  JsonArray<Camera, u8"cameras"> Cameras;
  JsonArray<Image, u8"images"> Images;
  JsonArray<Texture, u8"textures"> Textures;
  JsonArray<Material, u8"materials"> Materials;
  JsonArray<Mesh, u8"meshes"> Meshes;
  JsonArray<Node, u8"nodes"> Nodes;
  JsonArray<Sampler, u8"samplers"> Samplers;
  auto Scene() const { return m_ptr<float, u8"scene">(); }
  JsonArray<gltfjson::Scene, u8"scenes"> Scenes;
  JsonArray<Skin, u8"skins"> Skins;
};

} // namespace
