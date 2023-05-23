#pragma once
#include "directory.h"
#include "gltf_types.h"
#include "json_tree.h"
#include <optional>
#include <string>
#include <string_view>

namespace gltfjson {
namespace annotation {

template<typename T>
struct Key
{
  std::u8string m_key;
  std::optional<T> operator()() const;
  void operator()(const T& t);
};

using Id = uint32_t;

struct ChildOfRootProperty
{
  Key<std::u8string> Name{ u8"name" };
};

template<typename T, size_t N>
struct FixedArray : Key<std::array<T, N>>
{};

template<typename T>
struct Array
{
  std::u8string m_key;
  struct Iterator
  {
    T& operator*();
    Iterator& operator++();
    bool operator!=(const Iterator& rhs) const;
  };
  uint32_t Size() const;
  T& operator[](size_t index);
  const T& operator[](size_t index) const;
  Iterator begin() const;
  Iterator end() const;
};

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
struct Node : ChildOfRootProperty
{
  Key<Id> Camera{ u8"camera" };
  Array<uint32_t> Children{ u8"children" };
  Key<Id> Skin{ u8"skin" };
  FixedArray<float, 16> Matrix{ u8"matrix" };
  Key<Id> Mesh{ u8"mesh" };
  FixedArray<float, 4> Rotation{ u8"rotation" };
  FixedArray<float, 3> Scale{ u8"scale" };
  FixedArray<float, 3> Translation{ u8"translation" };
  Array<float> Weights{ u8"weights" };
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

struct Scene : ChildOfRootProperty
{
  Array<uint32_t> Nodes{ u8"nodes" };
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/asset.schema.json
struct Asset
{
  Key<std::u8string> Copyright{ u8"copyright" };
  Key<std::u8string> Generator{ u8"generator" };
  Key<std::u8string> Version{ u8"version" };
  Key<std::u8string> MinVersion{ u8"minVersion" };
};

struct Root
{
  Array<Accessor> Accessors{ u8"accessors" };
  Array<Animation> Animations{ u8"animations" };
  Key<Asset> Asset{ u8"asset" };
  Array<Buffer> Buffers{ u8"buffers" };
  Array<BufferView> BufferViews{ u8"bufferViews" };
  Array<Camera> Cameras{ u8"cameras" };
  Array<Image> Images{ u8"images" };
  Array<Texture> Textures{ u8"textures" };
  Array<Material> Materials{ u8"materials" };
  Array<Mesh> Meshes{ u8"meshes" };
  Array<Node> Nodes{ u8"nodes" };
  Array<Sampler> Samplers{ u8"samplers" };
  Key<Id> Scene{ u8"scene" };
  Array<annotation::Scene> Scenes{ u8"scenes" };
  Array<Skin> Skins{ u8"skins" };
};

struct Bin
{
  std::shared_ptr<Directory> Dir;
  std::span<const uint8_t> Bytes;

  std::expected<std::span<const uint8_t>, std::string> GetBufferViewBytes(
    const Root& gltf,
    int buffer_view_index) const
  {
    if (buffer_view_index < 0 || buffer_view_index >= gltf.BufferViews.Size()) {
      return std::unexpected{ "buffer_view_index is out of range" };
    }

    auto buffer_view = gltf.BufferViews[buffer_view_index];
    // std::cout << buffer_view << std::endl;

    int buffer_index = *buffer_view.Buffer();
    auto buffer = gltf.Buffers[buffer_index];
    auto uri = buffer.Uri().value_or(u8"");
    if (uri.size()) {
      // external file
      if (auto bytes = Dir->GetBuffer(uri)) {
        return bytes->subspan(buffer_view.ByteOffset().value_or(0),
                              *buffer_view.ByteLength());
      } else {
        return bytes;
      }
    } else {
      // glb
      return Bytes.subspan(buffer_view.ByteOffset().value_or(0),
                           *buffer_view.ByteLength());
    }
  }

  template<typename S, typename T>
  std::expected<bool, std::string> GetSparseValue(const Root& gltf,
                                                  std::span<const S> indices,
                                                  uint32_t buffer_view_index,
                                                  std::span<T> dst) const
  {
    if (auto span = GetBufferViewBytes(gltf, buffer_view_index)) {
      assert(indices.size() == span->size() / sizeof(T));
      auto p = (const T*)span->data();
      for (int i = 0; i < indices.size(); ++i) {
        dst[i] = p[indices[i]];
      }
      return true;
    } else {
      return std::unexpected{ span.error() };
    }
  }

  mutable std::vector<uint8_t> m_sparseBuffer;
  template<typename T>
  std::expected<std::span<const T>, std::string> GetAccessorBytes(
    const Root& gltf,
    const Accessor& accessor) const
  {
    // std::cout << accessor << std::endl;
    // assert(*item_size(accessor) == sizeof(T));
    int count = *accessor.Count();
    if (auto sparse = accessor.Sparse()) {
      m_sparseBuffer.resize(count * sizeof(T));
      auto begin = (T*)m_sparseBuffer.data();
      auto sparse_span = std::span<T>(begin, begin + count);
      if (accessor.BufferView()) {
        // non zero sparse
        return std::unexpected{ "non zero sparse not implemented" };
      } else {
        // zero fill
        T zero = {};
        std::fill(sparse_span.begin(), sparse_span.end(), zero);
      }
      int sparse_count = *sparse->Count();
      auto sparse_indices = *sparse->Indices();
      auto sparse_values = *sparse->Values();
      switch (*sparse_indices.ComponentType()) {
        case gltfjson::format::ComponentTypes::UNSIGNED_BYTE:
          if (auto sparse_indices_bytes =
                GetBufferViewBytes(gltf, *sparse_indices.BufferView())) {
            auto begin = (const uint8_t*)sparse_indices_bytes->data();
            auto indices_span = std::span(begin, begin + sparse_count);
            if (auto result = GetSparseValue(gltf,
                                             indices_span,
                                             *sparse_values.BufferView(),
                                             sparse_span)) {
              return sparse_span;
            } else {
              return std::unexpected{ result.error() };
            }
          } else {
            return std::unexpected{ sparse_indices_bytes.error() };
          }

        case gltfjson::format::ComponentTypes::UNSIGNED_SHORT:
          if (auto sparse_indices_bytes =
                GetBufferViewBytes(gltf, *sparse_indices.BufferView())) {
            auto begin = (const uint16_t*)sparse_indices_bytes->data();
            auto indices_span = std::span(begin, begin + sparse_count);
            if (auto result = GetSparseValue(gltf,
                                             indices_span,
                                             *sparse_values.BufferView(),
                                             sparse_span)) {

              return sparse_span;
            } else {
              return std::unexpected{ result.error() };
            }
          } else {
            return std::unexpected{ sparse_indices_bytes.error() };
          }
        case gltfjson::format::ComponentTypes::UNSIGNED_INT:
          if (auto sparse_indices_bytes =
                GetBufferViewBytes(gltf, *sparse_indices.BufferView())) {
            auto begin = (const uint32_t*)sparse_indices_bytes->data();
            auto indices_span = std::span(begin, begin + sparse_count);
            if (auto result = GetSparseValue(gltf,
                                             indices_span,
                                             *sparse_values.BufferView(),
                                             sparse_span)) {
              return sparse_span;
            } else {
              return std::unexpected{ result.error() };
            }
          } else {
            return std::unexpected{ sparse_indices_bytes.error() };
          }
        default:
          return std::unexpected{ "sparse.indices: unknown" };
      }
      throw std::runtime_error("not implemented");
    } else if (auto bufferView = accessor.BufferView()) {
      if (auto span = GetBufferViewBytes(gltf, *bufferView)) {
        int offset = accessor.ByteOffset().value_or(0);
        return std::span<const T>((const T*)(span->data() + offset), count);

      } else {
        return std::unexpected{ "invalid bufferView" };
      }
    } else {
      return std::unexpected{ "sparse nor bufferView" };
    }
  }

  template<typename T>
  std::expected<std::span<const T>, std::string> GetAccessorBytes(
    const Root& gltf,
    int accessor_index) const
  {
    return GetAccessorBytes<T>(gltf, gltf.Accessors[accessor_index]);
  }
};

}
}
