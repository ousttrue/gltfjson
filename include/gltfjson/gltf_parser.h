#pragma once
#include "bin.h"
#include "glb.h"
#include "gltf_types.h"
#include "json_tree_parser.h"
#include "readallbytes.h"
#include <string>

namespace gltfjson {

// hold gltf or glb
struct GltfData
{
  // owned bytes
  std::vector<uint8_t> Bytes;
  struct Root Root;
  struct Bin Bin;

  bool Parse(const std::shared_ptr<Directory>& dir = {})
  {
    auto glb = Glb::Parse(Bytes);
    // EXPECT_TRUE(glb);
    if (glb) {
      // as glb
      gltfjson::tree::Parser parser(glb->JsonChunk);
      if (auto result = parser.Parse()) {
        Root = gltfjson::Root(result);
        Bin = { dir, glb->BinChunk };
        return true;
      }
    } else {
      // as gltf
      gltfjson::tree::Parser parser(Bytes);
      if (auto result = parser.Parse()) {
        Root = gltfjson::Root(result);
        Bin = { dir };
        return true;
      }
    }
    return false;
  }
};

inline std::shared_ptr<GltfData>
FromBytes(std::vector<uint8_t>&& bytes)
{
  auto ptr = std::make_shared<GltfData>();
  // move
  ptr->Bytes = std::move(bytes);
  if (ptr->Parse()) {
    return ptr;
  } else {
    return {};
  }
}

inline std::shared_ptr<GltfData>
FromBytes(std::span<const uint8_t> bytes)
{
  auto ptr = std::make_shared<GltfData>();
  // copy
  ptr->Bytes.assign(bytes.begin(), bytes.end());
  if (ptr->Parse()) {
    return ptr;
  } else {
    return {};
  }

  gltfjson::tree::Parser parser(bytes);
  if (auto result = parser.Parse()) {

    auto ptr = std::make_shared<GltfData>();
    ptr->Root = Root(result);

    return ptr;

  } else {
    return {};
  }
}

inline std::shared_ptr<GltfData>
FromU8(std::u8string_view utf8)
{
  return FromBytes(std::span{ (const uint8_t*)utf8.data(),
                              (const uint8_t*)utf8.data() + utf8.size() });
}

inline std::shared_ptr<GltfData>
FromPath(const std::filesystem::path& path)
{
  auto bytes = ReadAllBytes(path);
  if (bytes.empty()) {
    // std::cerr << path << " 0 bytes" << std::endl;
    return {};
  }

  auto ptr = std::make_shared<GltfData>();
  std::swap(ptr->Bytes, bytes);
  auto dir = std::make_shared<Directory>(path);
  if (ptr->Parse(dir)) {
    return ptr;
  } else {
    return {};
  }
}

}
