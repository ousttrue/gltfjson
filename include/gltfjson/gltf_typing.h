#pragma once
#include "gltf_types.h"
#include "json_tree.h"
#include <array>
#include <optional>
#include <string>
#include <string_view>
#include <tuple>
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

  void push_back(const T& t)
  {
    if (t.m_json) {
      if (auto array = m_json->Array()) {
        array->push_back(t.m_json);
      }
    }
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
  std::optional<std::array<float, 2>> m_float2() const
  {
    if (auto node = m_node<lit>()) {
      if (auto array = node->template Ptr<tree::ArrayValue>()) {
        if (array->size() == 2) {
          if (auto x = (*array)[0]->Ptr<float>()) {
            if (auto y = (*array)[1]->Ptr<float>()) {
              return std::array<float, 2>{ *x, *y };
            }
          }
        }
      }
    }
    return std::nullopt;
  }

  template<StringLiteral lit>
  std::optional<std::array<float, 3>> m_float3() const
  {
    if (auto node = m_node<lit>()) {
      if (auto array = node->template Ptr<tree::ArrayValue>()) {
        if (array->size() == 3) {
          if (auto x = (*array)[0]->Ptr<float>()) {
            if (auto y = (*array)[1]->Ptr<float>()) {
              if (auto z = (*array)[2]->Ptr<float>()) {
                return std::array<float, 3>{ *x, *y, *z };
              }
            }
          }
        }
      }
    }
    return std::nullopt;
  }

  template<StringLiteral lit>
  std::optional<std::array<float, 4>> m_float4() const
  {
    if (auto node = m_node<lit>()) {
      if (auto array = node->template Ptr<tree::ArrayValue>()) {
        if (array->size() == 4) {
          if (auto x = (*array)[0]->Ptr<float>()) {
            if (auto y = (*array)[1]->Ptr<float>()) {
              if (auto z = (*array)[2]->Ptr<float>()) {
                if (auto w = (*array)[3]->Ptr<float>()) {
                  return std::array<float, 4>{ *x, *y, *z, *w };
                }
              }
            }
          }
        }
      }
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

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/glTFProperty.schema.json
struct GltfProperty : JsonObject
{
  using JsonObject::JsonObject;
  auto Extensions() const { return m_json->Get(u8"extensions"); }
  auto Extras() const { return m_json->Get(u8"extras"); }

  template<typename T>
  std::optional<T> GetExtension() const
  {
    if (auto extensions = Extensions()) {
      if (auto extension = extensions->Get(T::EXTENSION_NAME)) {
        return T(extension);
      }
    }
    return std::nullopt;
  }

  template<typename T>
  T GetOrCreateExtension()
  {
    auto extensions = Extensions();
    if (extensions) {
      if (auto extension = extensions->Get(T::EXTENSION_NAME)) {
        return T(extension);
      }
    }
    if (!extensions) {
      extensions = m_json->SetProperty(u8"extensions", tree::ObjectValue());
    }
    return extensions->SetProperty(T::EXTENSION_NAME, tree::ObjectValue());
  }
};

template<StringLiteral lit>
struct Extension : GltfProperty
{
  static inline const char8_t* EXTENSION_NAME = lit.value;
  using GltfProperty::GltfProperty;
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/glTFChildOfRootProperty.schema.json
struct ChildOfRootProperty : GltfProperty
{
  using GltfProperty::GltfProperty;
  auto NameString() const { return m_string<u8"name">(); }
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/buffer.schema.json
struct Buffer : ChildOfRootProperty
{
  using ChildOfRootProperty::ChildOfRootProperty;
  auto UriString() const { return m_string<u8"uri">(); };
  auto ByteLength() const { return m_ptr<float, u8"byteLength">(); };
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/bufferView.schema.json
struct BufferView : ChildOfRootProperty
{
  using ChildOfRootProperty::ChildOfRootProperty;
  auto BufferId() const { return m_id<u8"buffer">(); };
  auto ByteOffset() const { return m_ptr<float, u8"byteOffset">(); };
  auto ByteLength() const { return m_ptr<float, u8"byteLength">(); };
  auto ByteStride() const { return m_ptr<float, u8"byteStride">(); };
  auto Target() const { return m_ptr<float, u8"target">(); };
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/accessor.sparse.indices.schema.json
struct SparseIndices : JsonObject
{
  using JsonObject::JsonObject;
  auto BufferViewId() const { return m_id<u8"bufferView">(); };
  auto ByteOffset() const { return m_ptr<float, u8"byteOffset">(); }
  auto ComponentType() const { return m_ptr<float, u8"componentType">(); }
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/accessor.sparse.values.schema.json
struct SparseValues : JsonObject
{
  using JsonObject::JsonObject;
  auto BufferViewId() const { return m_id<u8"bufferView">(); }
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
  auto BufferViewId() const { return m_id<u8"bufferView">(); }
  auto ByteOffset() const { return m_ptr<float, u8"byteOffset">(); }
  auto ComponentType() const { return m_ptr<float, u8"componentType">(); }
  auto Normalized() const { return m_ptr<bool, u8"normalized">(); }
  auto Count() const { return m_ptr<float, u8"count">(); }
  auto TypeString() const { return m_string<u8"type">(); }
  NumberArray<float, u8"max"> Max;
  NumberArray<float, u8"min"> Min;
  auto Sparse() const { return m_object<gltfjson::Sparse, u8"sparse">(); }

  uint32_t Stride() const
  {
    return *component_size((ComponentTypes)*ComponentType()) *
           *type_count(TypeString());
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
  auto UriString() const { return m_string<u8"uri">(); }
  auto MimeTypeString() const { return m_string<u8"mimeType">(); }
  auto BufferViewId() const { return m_id<u8"bufferView">(); }
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
  auto SamplerId() const { return m_id<u8"sampler">(); }
  auto SourceId() const { return m_id<u8"source">(); }
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/textureInfo.schema.json
struct TextureInfo : JsonObject
{
  using JsonObject::JsonObject;
  auto IndexId() const { return m_id<u8"index">(); }
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
  auto AlphaModeString() const { return m_string<u8"alphaMode">(); }
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
  auto InverseBindMatricesId() const { return m_id<u8"inverseBindMatrices">(); }
  auto SkeletonId() const { return m_id<u8"skeleton">(); }
  NumberArray<uint32_t, u8"joints"> Joints;
};

struct MeshPrimitiveAttributes : JsonObject
{
  using JsonObject::JsonObject;
  auto COLOR_0_Id() const { return m_id<u8"COLOR_0">(); }
  auto JOINTS_0_Id() const { return m_id<u8"JOINTS_0">(); }
  auto NORMAL_Id() const { return m_id<u8"NORMAL">(); }
  auto POSITION_Id() const { return m_id<u8"POSITION">(); }
  auto TANGENT_Id() const { return m_id<u8"TANGENT">(); }
  auto TEXCOORD_0_Id() const { return m_id<u8"TEXCOORD_0">(); }
  auto TEXCOORD_1_Id() const { return m_id<u8"TEXCOORD_1">(); }
  auto TEXCOORD_2_Id() const { return m_id<u8"TEXCOORD_2">(); }
  auto TEXCOORD_3_Id() const { return m_id<u8"TEXCOORD_3">(); }
  auto WEIGHTS_0_Id() const { return m_id<u8"WEIGHTS_0">(); }

  bool operator==(const MeshPrimitiveAttributes& rhs) const
  {
    return COLOR_0_Id() == rhs.COLOR_0_Id() &&
           JOINTS_0_Id() == rhs.JOINTS_0_Id() &&
           NORMAL_Id() == rhs.NORMAL_Id() &&
           POSITION_Id() == rhs.POSITION_Id() &&
           TANGENT_Id() == rhs.TANGENT_Id() &&
           TEXCOORD_0_Id() == rhs.TEXCOORD_0_Id() &&
           TEXCOORD_1_Id() == rhs.TEXCOORD_1_Id() &&
           TEXCOORD_2_Id() == rhs.TEXCOORD_2_Id() &&
           TEXCOORD_3_Id() == rhs.TEXCOORD_3_Id() &&
           WEIGHTS_0_Id() == rhs.WEIGHTS_0_Id();
  }
};

struct MeshPrimitiveMorphTarget : JsonObject
{
  using JsonObject::JsonObject;
  auto POSITION_Id() const { return m_id<u8"POSITION">(); }
  auto NORMAL_Id() const { return m_id<u8"NORMAL">(); }
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
  auto IndicesId() const { return m_id<u8"indices">(); }
  auto MaterialId() const { return m_id<u8"material">(); }
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
  auto CameraId() const { return m_id<u8"camera">(); }
  NumberArray<uint32_t, u8"children"> Children;
  auto SkinId() const { return m_id<u8"skin">(); }
  NumberArray<float, u8"matrix"> Matrix;
  auto MeshId() const { return m_id<u8"mesh">(); }
  NumberArray<float, u8"rotation"> Rotation;
  NumberArray<float, u8"scale"> Scale;
  NumberArray<float, u8"translation"> Translation;
  NumberArray<float, u8"weights"> Weights;
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/animation.sampler.schema.json
struct AnimationSampler : JsonObject
{
  using JsonObject::JsonObject;
  auto InputId() const { return m_id<u8"input">(); }
  auto Interpolation() const { return m_ptr<float, u8"interpolation">(); }
  AnimationInterpolationModes InterpolationEnum() const
  {
    if (auto p = m_ptr<float, u8"interpolation">()) {
      return (AnimationInterpolationModes)*p;
    };
    return AnimationInterpolationModes::LINEAR;
  }
  auto OutputId() const { return m_id<u8"output">(); };
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/animation.channel.target.schema.json
struct AnimationTarget : JsonObject
{
  using JsonObject::JsonObject;
  auto Node() const { return m_id<u8"node">(); }
  auto PathString() const { return m_string<u8"path">(); }
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/animation.channel.schema.json
struct AnimationChannel : JsonObject
{
  using JsonObject::JsonObject;
  auto SamplerId() const { return m_id<u8"sampler">(); }
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

  auto CopyrightString() const { return m_string<u8"copyright">(); };
  auto GeneratorString() const { return m_string<u8"generator">(); };
  auto VersionString() const { return m_string<u8"version">(); };
  auto MinVersionString() const { return m_string<u8"minVersion">(); };
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
  auto ExtensionsUsed() const { return m_json->Get(u8"extensionsUsed"); }
  auto ExtensionsRequired() const
  {
    return m_json->Get(u8"extensionsRequired");
  }

  std::u8string GetTargetName(uint32_t meshIndex,
                              uint32_t primIndex,
                              uint32_t targetIndex) const
  {
    if (meshIndex >= Meshes.size()) {
      return {};
    }
    auto mesh = Meshes[meshIndex];
    if (auto extras = mesh.Extras()) {
      if (auto targetNames = extras->Get(u8"targetNames")) {
        if (auto name = targetNames->Get(targetIndex)) {
          return name->U8String();
        }
      }
    }

    if (primIndex >= mesh.Primitives.size()) {
      return {};
    }
    auto prim = mesh.Primitives[primIndex];
    if (auto extras = prim.m_json->Get(u8"extras")) {
      if (auto targetNames = extras->Get(u8"targetNames")) {
        if (auto name = targetNames->Get(targetIndex)) {
          return name->U8String();
        }
      }
    }

    return {};
  }
};

} // namespace
