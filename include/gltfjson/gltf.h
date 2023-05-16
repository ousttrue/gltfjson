#pragma once
#include "json.h"
#include <array>
#include <optional>
#include <string>
#include <vector>

namespace gltfjson {
namespace format {

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/glTFProperty.schema.json
struct Property
{
  // Value Extensions;
  // Value Extras;
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/glTFChildOfRootProperty.schema.json
struct ChildOfRootProperty : Property
{
  std::string Name;
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

  T& operator[](size_t i) { return Values[i]; }
};

using Id = std::optional<uint32_t>;

struct Buffer
{};

enum class Targets
{
  NONE = 0,
  ARRAY_BUFFER = 34962,
  ELEMENT_ARRAY_BUFFER = 34963,
};

struct BufferView : ChildOfRootProperty
{
  Id Buffer;
  uint32_t ByteOffset = 0;
  uint32_t ByteLength = 0;
  uint32_t ByteStride = 0;
  Targets Target = Targets::NONE;
};

enum class ComponentTypes
{
  BYTE = 5120,
  UNSIGNED_BYTE = 5121,
  SHORT = 5122,
  UNSIGNED_SHORT = 5123,
  UNSIGNED_INT = 5125,
  FLOAT = 5126,
};
enum class Types
{
  SCALAR,
  VEC2,
  VEC3,
  VEC4,
  MAT2,
  MAT3,
  MAT4,
};

struct Sparse
{};

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
};

struct Camera : ChildOfRootProperty
{};

struct Image : ChildOfRootProperty
{};

struct Sampler : ChildOfRootProperty
{};

struct Texture : ChildOfRootProperty
{};

struct Material : ChildOfRootProperty
{};

struct Skin : ChildOfRootProperty
{};

struct MeshPrimitiveAttributes
{
  Id POSITION;
};
struct MeshPrimitiveMorphTarget
{};

enum class MeshPrimitiveTopology
{
  POINTS,
  LINES,
  LINE_LOOP,
  LINE_STRIP,
  TRIANGLES,
  TRIANGLE_STRIP,
  TRIANGLE_FAN,
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
  std::optional<Id> Camera;
  std::vector<uint32_t> Children;
  std::optional<Id> Skin;
  std::optional<std::array<float, 16>> Matrix;
  std::optional<Id> Mesh;
  std::optional<std::array<float, 4>> Rotation;
  std::optional<std::array<float, 3>> Scale;
  std::optional<std::array<float, 3>> Translation;
  std::vector<float> Weights;
};

struct Animation : ChildOfRootProperty
{};

struct Scene : ChildOfRootProperty
{
  std::vector<uint32_t> Nodes;
};

struct Asset
{
  std::u8string Version;
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
  PropertyList<Material> Materials;
  PropertyList<Mesh> Meshes;
  PropertyList<Node> Nodes;
  PropertyList<Sampler> Samplers;
  Id Scene;
  PropertyList<::gltfjson::format::Scene> Scenes;
  PropertyList<Skin> Skins;
};

} // namespace format
} // namespace gltfjson
