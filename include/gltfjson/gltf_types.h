#pragma once
#include <optional>
#include <string>

namespace gltfjson {
namespace format {

enum class Targets
{
  NONE = 0,
  ARRAY_BUFFER = 34962,
  ELEMENT_ARRAY_BUFFER = 34963,
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
type_count(std::string_view type)
{
  if (type == "SCALAR") {
    return 1;
  } else if (type == "VEC2") {
    return 2;
  } else if (type == "VEC3") {
    return 3;
  } else if (type == "VEC4") {
    return 4;
  } else if (type == "MAT2") {
    return 4;
  } else if (type == "MAT3") {
    return 9;
  } else if (type == "MAT4") {
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

// inline std::expected<size_t, std::string>
// item_size(const nlohmann::json& accessor)
// {
//   if (auto cs = component_size(accessor["componentType"])) {
//     if (auto count = type_count(accessor["type"])) {
//       return *cs * *count;
//     } else {
//       return count;
//     }
//   } else {
//     throw cs;
//   }
// }

}
}
