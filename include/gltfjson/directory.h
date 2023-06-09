#pragma once
#include "base64.h"
#include <expected>
#include <filesystem>
#include <fstream>
#include <span>
#include <stdint.h>
#include <unordered_map>
#include <vector>

namespace gltfjson {

inline std::expected<std::vector<uint8_t>, std::string>
ReadAllBytes(const std::filesystem::path& path)
{
  std::ifstream ifs(path, std::ios::binary | std::ios::ate);
  if (!ifs) {
    auto u8 = path.u8string();
    return std::unexpected{ std::string("fail to open: ") +
                            std::string((const char*)u8.data(), u8.size()) };
  }

  auto pos = ifs.tellg();
  std::vector<uint8_t> buffer(pos);
  ifs.seekg(0, std::ios::beg);
  ifs.read((char*)buffer.data(), pos);
  return buffer;
}

const std::string BASE64_PREFIX[]{
  "data:application/octet-stream;base64,",
  "data:application/gltf-buffer;base64,",
};

struct Directory
{
  std::filesystem::path Base;
  std::unordered_map<std::string, std::vector<uint8_t>> FileCaches;

  std::expected<std::span<const uint8_t>, std::string> GetBuffer(
    std::u8string_view uri)
  {
    auto found = FileCaches.find({ uri.begin(), uri.end() });
    if (found != FileCaches.end()) {
      // use cache
      return found->second;
    }

    if (gltfjson::from_u8(uri).starts_with("data:")) {
      // return std::unexpected{"base64 not implemented"};
      for (auto& prefix : BASE64_PREFIX) {
        if (gltfjson::from_u8(uri).starts_with(prefix)) {
          auto decoded =
            base64::Decode(gltfjson::from_u8(uri).substr(std::size(prefix)));
          std::string key{ uri.begin(), uri.end() };
          FileCaches.insert({ key, decoded });
          return FileCaches[key];
        }
      }
      return std::unexpected{ "not implemented base64" };
    }

    auto path = Base / uri;
    if (auto bytes = ReadAllBytes(path)) {
      std::string key{ uri.begin(), uri.end() };
      FileCaches.insert({ key, *bytes });
      return FileCaches[key];
    } else {
      return bytes;
    }
  }
};

}
