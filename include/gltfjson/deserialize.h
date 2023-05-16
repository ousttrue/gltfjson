#pragma once
#include "gltf.h"
#include "json.h"
#include <optional>

namespace gltfjson {

inline void
Deserialize(std::optional<Value> value, format::Asset& dst)
{
  if (!value) {
    return;
  }
  if (auto version = value->Get("version")) {
    dst.Version = *version->String();
  }
}

inline void
Deserialize(const Parser& parser, format::Root& dst)
{
  auto root = parser.Values[0];
  Deserialize(root.Get(u8"asset"), dst.Asset);
}
}
