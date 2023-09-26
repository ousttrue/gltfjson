#pragma once
#include <filesystem>
#include <fstream>
#include <stdint.h>
#include <vector>

namespace gltfjson {

inline std::vector<uint8_t>
ReadAllBytes(const std::filesystem::path& filename)
{
  std::ifstream ifs(filename, std::ios::binary | std::ios::ate);
  if (!ifs) {
    return {};
  }
  auto pos = ifs.tellg();
  std::vector<uint8_t> buffer(pos);
  ifs.seekg(0, std::ios::beg);
  ifs.read((char*)buffer.data(), pos);
  return buffer;
}

// inline std::optional<std::vector<uint8_t>>
// ReadAllBytes(const std::filesystem::path& path)
// {
//   std::ifstream ifs(path, std::ios::binary | std::ios::ate);
//   if (!ifs) {
//     auto u8 = path.u8string();
//     // { std::string("fail to open: ") +
//     //                         std::string((const char*)u8.data(), u8.size())
//     }; return {};
//   }
//
//   auto pos = ifs.tellg();
//   std::vector<uint8_t> buffer(pos);
//   ifs.seekg(0, std::ios::beg);
//   ifs.read((char*)buffer.data(), pos);
//   return buffer;
// }

}
