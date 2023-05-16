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
{};
template<typename T>
struct Id
{
  PropertyList<T>& List;
  uint32_t Index;
};

struct Accessor : ChildOfRootProperty
{};

struct Camera : ChildOfRootProperty
{};

struct Skin : ChildOfRootProperty
{};

struct Material : ChildOfRootProperty
{};

struct MeshPrimitiveAttributes
{};
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
  std::optional<Id<Accessor>> Indices;
  std::optional<Id<Material>> Material;
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
  std::optional<Id<Camera>> Camera;
  std::vector<Id<Node>> Children;
  std::optional<Id<Skin>> Skin;
  std::optional<std::array<float, 16>> Matrix;
  std::optional<Id<Mesh>> Mesh;
  std::optional<std::array<float, 4>> Rotation;
  std::optional<std::array<float, 3>> Scale;
  std::optional<std::array<float, 3>> Translation;
  std::vector<float> Weights;
};

// https://github.com/KhronosGroup/glTF/blob/main/specification/2.0/schema/glTF.schema.json
struct Root
{
  PropertyList<Node> Nodes;
};

} // namespace format
} // namespace gltfjson
