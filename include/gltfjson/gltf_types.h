#pragma once
#include <optional>
#include <string>

namespace gltfjson {
namespace format {

inline const auto VERTEX_JOINT = "JOINTS_0";
inline const auto VERTEX_WEIGHT = "WEIGHTS_0";
inline const auto VERTEX_POSITION = "POSITION";
inline const auto VERTEX_NORMAL = "NORMAL";
inline const auto VERTEX_UV = "TEXCOORD_0";

enum class Targets
{
  NONE = 0,
  ARRAY_BUFFER = 34962,
  ELEMENT_ARRAY_BUFFER = 34963,
};
inline std::tuple<gltfjson::format::Targets, const char*> TargetsCombo[] = {
  { Targets::NONE, "NONE" },
  { Targets::ARRAY_BUFFER, "ARRAY_BUFFER" },
  { Targets::ELEMENT_ARRAY_BUFFER, "ELEMENT_ARRAY_BUFFER" },
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
inline std::tuple<gltfjson::format::ComponentTypes, const char*>
  ComponentTypesCombo[] = {
    { ComponentTypes::BYTE, "BYTE" },
    { ComponentTypes::UNSIGNED_BYTE, "UNSIGNED_BYTE" },
    { ComponentTypes::SHORT, "SHORT" },
    { ComponentTypes::UNSIGNED_SHORT, "UNSIGNED_SHORT" },
    { ComponentTypes::UNSIGNED_INT, "UNSIGNED_INT" },
    { ComponentTypes::FLOAT, "FLOAT" },
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
inline std::tuple<gltfjson::format::Types, std::string> TypesCombo[] = {
  { Types::SCALAR, "SCALAR" }, { Types::VEC2, "VEC2" }, { Types::VEC3, "VEC3" },
  { Types::VEC4, "VEC4" },     { Types::MAT2, "MAT2" }, { Types::MAT3, "MAT3" },
  { Types::MAT4, "MAT4" },
};
inline std::optional<Types>
types_from_str(std::u8string_view u8)
{
  std::string src{ (const char*)u8.data() };
  for (auto [t, str] : TypesCombo) {
    if (str == src) {
      return t;
    }
  }
  return std::nullopt;
}
inline std::optional<size_t>
component_size(ComponentTypes component_type)
{
  switch (component_type) {
    case ComponentTypes::BYTE:
      return 1;
    case ComponentTypes::UNSIGNED_BYTE:
      return 1;
    case ComponentTypes::SHORT:
      return 2;
    case ComponentTypes::UNSIGNED_SHORT:
      return 2;
    case ComponentTypes::UNSIGNED_INT:
      return 4;
    case ComponentTypes::FLOAT:
      return 4;
  }

  return std::nullopt;
}

inline const char*
component_type_name(ComponentTypes component_type)
{
  switch (component_type) {
    case ComponentTypes::BYTE:
      return "byte";
    case ComponentTypes::UNSIGNED_BYTE:
      return "ubyte";
    case ComponentTypes::SHORT:
      return "short";
    case ComponentTypes::UNSIGNED_SHORT:
      return "ushort";
    case ComponentTypes::UNSIGNED_INT:
      return "uint";
    case ComponentTypes::FLOAT:
      return "float";
    default:
      return "invalid";
  }
}

inline std::string
component_type_name(ComponentTypes component_type, std::string_view type)
{
  if (type == "SCALAR") {
    return component_type_name(component_type);
  }

  std::string base = component_type_name(component_type);
  if (type == "VEC2") {
    return base + "2";
  } else if (type == "VEC3") {
    return base + "3";
  } else if (type == "VEC4" || type == "MAT2") {
    return base + "4";
  } else if (type == "MAT3") {
    return base + "9";
  } else if (type == "MAT4") {
    return base + "16";
  } else {
    return base + "?";
  }
}

inline std::optional<size_t>
type_count(std::u8string_view type)
{
  if (type == u8"SCALAR") {
    return 1;
  } else if (type == u8"VEC2") {
    return 2;
  } else if (type == u8"VEC3") {
    return 3;
  } else if (type == u8"VEC4") {
    return 4;
  } else if (type == u8"MAT2") {
    return 4;
  } else if (type == u8"MAT3") {
    return 9;
  } else if (type == u8"MAT4") {
    return 16;
  } else {
    return std::nullopt;
  }
}
inline const char*
type_str(Types type)
{
  switch (type) {
    case Types::SCALAR:
      return "SCALAR";
    case Types::VEC2:
      return "VEC2";
    case Types::VEC3:
      return "VEC3";
    case Types::VEC4:
      return "VEC4";
    case Types::MAT2:
      return "MAT2";
    case Types::MAT3:
      return "MAT3";
    case Types::MAT4:
      return "MAT4";
    default:
      return "";
  }
}

enum class TextureMagFilter
{
  NEAREST = 9728,
  LINEAR = 9729,
};
inline std::tuple<gltfjson::format::TextureMagFilter, const char*>
  TextureMagFilterCombo[] = {
    { TextureMagFilter::NEAREST, "NEAREST" },
    { TextureMagFilter::LINEAR, "LINEAR" },
  };

enum class TextureMinFilter
{
  NEAREST = 9728,
  LINEAR = 9729,
  NEAREST_MIPMAP_NEAREST = 9984,
  LINEAR_MIPMAP_NEAREST = 9985,
  NEAREST_MIPMAP_LINEAR = 9986,
  LINEAR_MIPMAP_LINEAR = 9987,
};
inline std::tuple<gltfjson::format::TextureMinFilter, const char*>
  TextureMinFilterCombo[] = {
    { TextureMinFilter::NEAREST, "NEAREST" },
    { TextureMinFilter::LINEAR, "LINEAR" },
    { TextureMinFilter::NEAREST_MIPMAP_NEAREST, "NEAREST_MIPMAP_NEAREST" },
    { TextureMinFilter::LINEAR_MIPMAP_NEAREST, "LINEAR_MIPMAP_NEAREST" },
    { TextureMinFilter::NEAREST_MIPMAP_LINEAR, "NEAREST_MIPMAP_LINEAR" },
    { TextureMinFilter::LINEAR_MIPMAP_LINEAR, "LINEAR_MIPMAP_LINEAR" },
  };

enum class TextureWrap
{
  CLAMP_TO_EDGE = 33071,
  MIRRORED_REPEAT = 33648,
  REPEAT = 10497,
};
inline std::tuple<gltfjson::format::TextureWrap, const char*>
  TextureWrapCombo[] = {
    { TextureWrap::CLAMP_TO_EDGE, "CLAMP_TO_EDGE" },
    { TextureWrap::MIRRORED_REPEAT, "MIRRORED_REPEAT" },
    { TextureWrap::REPEAT, "REPEAT" },
  };

// enum class AlphaModes
// {
//   Opaque,
//   Mask,
//   Blend,
// };
// inline std::tuple<gltfjson::format::AlphaModes, const char*>
//   AlphaModesCombo[] = {
//     { AlphaModes::Opaque, "OPAQUE" },
//     { AlphaModes::Mask, "MASK" },
//     { AlphaModes::Blend, "BLEND" },
//   };
// inline AlphaModes
// AlphaModesFromStr(std::u8string_view str)
// {
//   for (auto [mode, label] : AlphaModesCombo) {
//     if (str == (const char8_t*)label) {
//       return mode;
//     }
//   }
//   return {};
// }

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
inline std::tuple<gltfjson::format::MeshPrimitiveTopology, const char*>
  MeshPrimitiveTopologyCombo[] = {
    { MeshPrimitiveTopology::POINTS, "POINTS" },
    { MeshPrimitiveTopology::LINES, "LINES" },
    { MeshPrimitiveTopology::LINE_LOOP, "LINE_LOOP" },
    { MeshPrimitiveTopology::LINE_STRIP, "LINE_STRIP" },
    { MeshPrimitiveTopology::TRIANGLES, "TRIANGLES" },
    { MeshPrimitiveTopology::TRIANGLE_STRIP, "TRIANGLE_STRIP" },
    { MeshPrimitiveTopology::TRIANGLE_FAN, "TRIANGLE_FAN" },
  };

// enum class PathTypes
// {
//   Translation,
//   Rotation,
//   Scale,
//   Weights,
// };
//
// enum class InterpolationTypes
// {
//   LINEAR,
//   STEP,
//   CUBESPLINE,
// };

// inline const char8_t* ChildOfRootProperties[]{
//   u8"textures",
//   u8"materials",
// };

}
}
