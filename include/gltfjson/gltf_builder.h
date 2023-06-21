#pragma once
#include "gltf_typing.h"

namespace gltfjson {
namespace gltf {

inline Root
CreateEmpty()
{
  auto json = tree::Node::Create(tree::ObjectValue());

  auto asset = json->Add(u8"asset", tree::ObjectValue());
  asset->Add(u8"version", u8"2.0");
  auto scenes = json->Add(u8"scenes", tree::ArrayValue());
  auto scene = scenes->Add(tree::ObjectValue());
  scene->Add(u8"nodes", tree::ArrayValue());

  json->Add(u8"nodes", tree::ArrayValue());
  return Root(json);
}

inline Node
CreateNode()
{
  auto json = tree::Node::Create(tree::ObjectValue());
  json->Add(u8"children", tree::ArrayValue());
  return Node(json);
}

} // namespace
} // namespace
