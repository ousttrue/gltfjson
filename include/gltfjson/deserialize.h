#pragma once
#include "gltf.h"
#include "json.h"
#include <optional>

namespace gltfjson {

inline void
Deserialize(std::optional<ObjectValue> asset, format::Asset& dst)
{
  if (!asset) {
    return;
  }
  if (auto version = asset->Get("version")) {
    dst.Version = *version->String();
  }
}

inline void
Deserialize(const Parser& parser, format::Root& dst)
{
  auto root = parser.Values[0].Object();
  if (auto asset = root->Get(u8"asset")) {
    Deserialize(asset->Object(), dst.Asset);
  }
}
}
