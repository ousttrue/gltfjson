#pragma once
#include "gltf.h"

namespace gltfjson {
namespace format {

template<typename T>
inline const char*
GetIcon()
{
  return "? ";
}

template<>
inline const char*
GetIcon<Buffer>()
{
  return " ";
}
template<>
inline const char*
GetIcon<BufferView>()
{
  return " ";
}
template<>
inline const char*
GetIcon<Accessor>()
{
  return " ";
}

template<>
inline const char*
GetIcon<Image>()
{
  return " ";
}
template<>
inline const char*
GetIcon<Sampler>()
{
  return " ";
}
template<>
inline const char*
GetIcon<Texture>()
{
  return " ";
}

template<>
inline const char*
GetIcon<Material>()
{
  return " ";
}

template<>
inline const char*
GetIcon<Mesh>()
{
  return "󰕠 ";
}
template<>
inline const char*
GetIcon<Skin>()
{
  return "󰕠 ";
}
template<>
inline const char*
GetIcon<Node>()
{
  return "󱘎 ";
}
template<>
inline const char*
GetIcon<Scene>()
{
  return "󱘎 ";
}

template<>
inline const char*
GetIcon<Animation>()
{
  return " ";
}

}
}
