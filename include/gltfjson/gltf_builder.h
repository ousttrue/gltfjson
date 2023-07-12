#pragma once
#include "gltf_typing.h"

namespace gltfjson {
namespace gltf {

inline Root
CreateEmpty()
{
  auto json = tree::Node::Create(tree::ObjectValue());

  auto asset = json->SetProperty(u8"asset", tree::ObjectValue());
  asset->SetProperty(u8"version", u8"2.0");
  auto scenes = json->SetProperty(u8"scenes", tree::ArrayValue());
  auto scene = scenes->Add(tree::ObjectValue());
  scene->SetProperty(u8"nodes", tree::ArrayValue());

  json->SetProperty(u8"nodes", tree::ArrayValue());
  return Root(json);
}

inline Node
CreateNode()
{
  auto json = tree::Node::Create(tree::ObjectValue());
  json->SetProperty(u8"children", tree::ArrayValue());
  return Node(json);
}

} // namespace
} // namespace
