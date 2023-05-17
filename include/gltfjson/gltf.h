#pragma once
#include "gltf_types.h"
#include <array>
#include <optional>
#include <stdint.h>
#include <string>
#include <vector>

namespace gltfjson {
namespace format {

using Id = std::optional<uint32_t>;

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/glTFProperty.schema.json
struct Property
{
  // Value Extensions;
  // Value Extras;
  int Extensions;
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/glTFChildOfRootProperty.schema.json
struct ChildOfRootProperty : Property
{
  std::u8string Name;
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/glTFid.schema.json
template<typename T>
struct PropertyList
{
  std::vector<T> Values;
  T& Push(const T& t)
  {
    Values.push_back(t);
    return Values.back();
  }
  size_t Size() const { return Values.size(); }

  auto begin() { return Values.begin(); }
  auto end() { return Values.end(); }
  auto begin() const { return Values.begin(); }
  auto end() const { return Values.end(); }
  T& operator[](size_t i) { return Values[i]; }
  const T& operator[](size_t i) const { return Values[i]; }
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/buffer.schema.json
struct Buffer : ChildOfRootProperty
{
  std::u8string Uri;
  uint32_t ByteLength = 0;
};

struct BufferView : ChildOfRootProperty
{
  Id Buffer;
  uint32_t ByteOffset = 0;
  uint32_t ByteLength = 0;
  uint32_t ByteStride = 0;
  Targets Target = Targets::NONE;
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/accessor.sparse.indices.schema.json
struct SparseIndices : Property
{
  Id BufferView;
  uint32_t ByteOffset = 0;
  ComponentTypes ComponentType;
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/accessor.sparse.values.schema.json
struct SparseValues : Property
{
  Id BufferView;
  uint32_t ByteOffset = 0;
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/accessor.sparse.schema.json
struct Sparse : Property
{
  uint32_t Count = 0;
  SparseIndices Indices;
  SparseValues Values;
};

struct Accessor : ChildOfRootProperty
{
  Id BufferView;
  uint32_t ByteOffset = 0;
  ComponentTypes ComponentType;
  bool Normalized = false;
  uint32_t Count = 0;
  Types Type;
  std::vector<float> Max;
  std::vector<float> Min;
  std::optional<Sparse> Sparse;

  uint32_t Stride() const { return ComponentSize() * TypeCount(); }
  uint32_t ComponentSize() const { return 4; }
  uint32_t TypeCount() const { return 1; }
};

struct Camera : ChildOfRootProperty
{};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/image.schema.json
struct Image : ChildOfRootProperty
{
  std::u8string Uri;
  std::u8string MimeType;
  Id BufferView;
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/sampler.schema.json
struct Sampler : ChildOfRootProperty
{
  TextureMagFilter MagFilter = TextureMagFilter::NEAREST;
  TextureMinFilter MinFilter = TextureMinFilter::NEAREST;
  TextureWrap WrapS = TextureWrap::REPEAT;
  TextureWrap WrapT = TextureWrap::REPEAT;
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/texture.schema.json
struct Texture : ChildOfRootProperty
{
  Id Sampler;
  Id Source;
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/textureInfo.schema.json
struct TextureInfo : Property
{
  Id Index;
  uint32_t TexCoord = 0;
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/material.normalTextureInfo.schema.json
struct NormalTextureInfo : TextureInfo
{
  float Scale = 1.0f;
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/material.occlusionTextureInfo.schema.json
struct OcclusionTextureInfo : TextureInfo
{
  float Strength = 1.0f;
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/material.pbrMetallicRoughness.schema.json
struct PbrMetallicRoughness : Property
{
  std::array<float, 4> BaseColorFactor = { 1, 1, 1, 1 };
  std::optional<TextureInfo> BaseColorTexture;
  float MetallicFactor = 1.0f;
  float RoughnessFactor = 1.0f;
  std::optional<TextureInfo> MetallicRoughnessTexture;
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/material.schema.json
struct Material : ChildOfRootProperty
{
  std::optional<PbrMetallicRoughness> PbrMetallicRoughness;
  std::optional<NormalTextureInfo> NormalTexture;
  std::optional<OcclusionTextureInfo> OcclusionTexture;
  std::optional<TextureInfo> EmissiveTexture;
  std::array<float, 3> EmissiveFactor = { 0, 0, 0 };
  AlphaModes AlphaMode = AlphaModes::Opaque;
  float AlphaCutoff = 0.5f;
  bool DoubleSided = false;
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/skin.schema.json
struct Skin : ChildOfRootProperty
{
  Id InverseBindMatrices;
  Id Skeleton;
  std::vector<uint32_t> Joints;
};

struct MeshPrimitiveAttributes
{
  Id COLOR_0;
  Id JOINTS_0;
  Id NORMAL;
  Id POSITION;
  Id TANGENT;
  Id TEXCOORD_0;
  Id TEXCOORD_1;
  Id TEXCOORD_2;
  Id TEXCOORD_3;
  Id WEIGHTS_0;

  bool operator==(const MeshPrimitiveAttributes& rhs) const
  {
    if (COLOR_0 != rhs.COLOR_0)
      return false;
    if (JOINTS_0 != rhs.JOINTS_0)
      return false;
    if (NORMAL != rhs.NORMAL)
      return false;
    if (POSITION != rhs.POSITION)
      return false;
    if (TANGENT != rhs.TANGENT)
      return false;
    if (TEXCOORD_0 != rhs.TEXCOORD_0)
      return false;
    if (TEXCOORD_1 != rhs.TEXCOORD_1)
      return false;
    if (TEXCOORD_2 != rhs.TEXCOORD_2)
      return false;
    if (TEXCOORD_3 != rhs.TEXCOORD_3)
      return false;
    if (WEIGHTS_0 != rhs.WEIGHTS_0)
      return false;
    return true;
  }
};

struct MeshPrimitiveMorphTarget
{
  Id POSITION;
  Id NORMAL;
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/mesh.primitive.schema.json
struct MeshPrimitive : Property
{
  MeshPrimitiveAttributes Attributes;
  Id Indices;
  Id Material;
  MeshPrimitiveTopology Mode = MeshPrimitiveTopology::TRIANGLES;
  std::vector<MeshPrimitiveMorphTarget> Targets;
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/mesh.schema.json
struct Mesh : ChildOfRootProperty
{
  std::vector<MeshPrimitive> Primitives;
  std::vector<float> Weights;
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/node.schema.json
struct Node : ChildOfRootProperty
{
  Id Camera;
  std::vector<uint32_t> Children;
  Id Skin;
  std::optional<std::array<float, 16>> Matrix;
  Id Mesh;
  std::optional<std::array<float, 4>> Rotation;
  std::optional<std::array<float, 3>> Scale;
  std::optional<std::array<float, 3>> Translation;
  std::vector<float> Weights;
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/animation.sampler.schema.json
struct AnimationSampler
{
  Id Input;
  InterpolationTypes Interpolation;
  Id Output;
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/animation.channel.target.schema.json
struct AnimationTarget
{
  Id Node;
  PathTypes Path;
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/animation.channel.schema.json
struct AnimationChannel : Property
{
  Id Sampler;
  AnimationTarget Target;
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/animation.schema.json
struct Animation : ChildOfRootProperty
{
  std::vector<AnimationChannel> Channels;
  std::vector<AnimationSampler> Samplers;
};

struct Scene : ChildOfRootProperty
{
  std::vector<uint32_t> Nodes;
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/asset.schema.json
struct Asset : Property
{
  std::u8string Copyright;
  std::u8string Generator;
  std::u8string Version;
  std::u8string MinVersion;
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/glTF.schema.json
struct Root
{
  std::vector<std::u8string> ExtensionsUsed;
  std::vector<std::u8string> ExtensionsRequired;
  PropertyList<Accessor> Accessors;
  PropertyList<Animation> Animations;
  Asset Asset;
  PropertyList<Buffer> Buffers;
  PropertyList<BufferView> BufferViews;
  PropertyList<Camera> Cameras;
  PropertyList<Image> Images;
  PropertyList<Texture> Textures;
  PropertyList<Material> Materials;
  PropertyList<Mesh> Meshes;
  PropertyList<Node> Nodes;
  PropertyList<Sampler> Samplers;
  Id Scene;
  PropertyList<::gltfjson::format::Scene> Scenes;
  PropertyList<Skin> Skins;
};

}
}
