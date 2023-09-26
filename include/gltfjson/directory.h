#pragma once
#include "json_tree.h"
#include "readallbytes.h"
#include <filesystem>
#include <fstream>
#include <stdint.h>
#include <unordered_map>
#include <vector>

namespace gltfjson {

const std::string BASE64_PREFIX[]{
  "data:application/octet-stream;base64,",
  "data:application/gltf-buffer;base64,",
};

struct Directory
{
  std::filesystem::path Base;
  std::unordered_map<std::string, std::vector<uint8_t>> FileCaches;

  std::optional<std::span<const uint8_t>> GetBuffer(std::u8string_view uri)
  {
    auto found = FileCaches.find({ uri.begin(), uri.end() });
    if (found != FileCaches.end()) {
      // use cache
      return found->second;
    }

    if (gltfjson::from_u8(uri).starts_with("data:")) {
      for (auto& prefix : BASE64_PREFIX) {
        if (gltfjson::from_u8(uri).starts_with(prefix)) {
          auto decoded =
            base64::Decode(gltfjson::from_u8(uri).substr(std::size(prefix)));
          std::string key{ uri.begin(), uri.end() };
          FileCaches.insert({ key, decoded });
          return FileCaches[key];
        }
      }
      // { "not implemented base64" };
      return {};
    }

    auto path = Base / uri;
    auto bytes = ReadAllBytes(path);
    if (bytes.size()) {
      std::string key{ uri.begin(), uri.end() };
      FileCaches.insert({ key, bytes });
      return FileCaches[key];
    } else {
      return {};
    }
  }
};

}
