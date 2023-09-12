#pragma once
#include "binary_reader.h"
#include "binary_writer.h"
#include <filesystem>
#include <functional>
#include <optional>
#include <span>
#include <stdint.h>
#include <string>
#include <tuple>

namespace gltfjson {

const uint32_t GLB_MAGIC = 0x46546C67;
const uint32_t GLB_VERSION = 2;
const uint32_t GLB_JSON_CHUNK = 0x4E4F534A;
const uint32_t GLB_BIN_CHUNK = 0x004E4942;

struct Glb
{
  std::span<const uint8_t> JsonChunk;
  uint32_t JsonPadding() const
  {
    auto json_padding = 0;
    if (JsonChunk.size() % 4) {
      json_padding = 4 - (JsonChunk.size() % 4);
    }
    return json_padding;
  }

  std::span<const uint8_t> BinChunk;
  uint32_t BinPadding() const
  {
    auto bin_padding = 0;
    if (BinChunk.size() % 4) {
      bin_padding = 4 - (BinChunk.size() % 4);
    }
    return bin_padding;
  }

  static std::optional<Glb> Parse(std::span<const uint8_t> bytes)
  {
    BinaryReader r(bytes);
    if (r.Get<uint32_t>() != GLB_MAGIC) {
      return {};
    }

    if (r.Get<uint32_t>() != GLB_VERSION) {
      return {};
    }

    auto length = r.Get<uint32_t>();
    r.Resize(length);

    Glb glb{};
    {
      auto chunk_length = r.Get<uint32_t>();
      if (r.Get<uint32_t>() != GLB_JSON_CHUNK) {
        // first chunk must "JSON"
        return {};
      }
      glb.JsonChunk = r.Span(chunk_length);
    }
    if (!r.is_end()) {
      auto chunk_length = r.Get<uint32_t>();
      if (r.Get<uint32_t>() != GLB_BIN_CHUNK) {
        // second chunk is "BIN"
        return {};
      }
      glb.BinChunk = r.Span(chunk_length);
    }

    return glb;
  }

  uint32_t CalcSize() const
  {
    return
      // glb header
      12
      // json chunk
      + 8 + JsonChunk.size() +
      JsonPadding()
      // bin chunk
      + 8 + BinChunk.size() + BinPadding();
  }

  bool WriteTo(std::ostream& os)
  {
    BinaryWriter w(os);

    // GLB header
    w.Uint32(GLB_MAGIC);
    w.Uint32(GLB_VERSION);
    w.Uint32(CalcSize());

    // json
    w.Uint32(JsonChunk.size() + JsonPadding());
    w.Uint32(GLB_JSON_CHUNK);
    w.Bytes(JsonChunk);
    w.Padding(JsonPadding());

    // bin
    w.Uint32(BinChunk.size() + BinPadding());
    w.Uint32(GLB_BIN_CHUNK);
    w.Bytes(BinChunk);
    w.Padding(BinPadding());

    return true;
  }
};

}
