import pathlib
import os

HERE = pathlib.Path(__file__).parent

TEMPLATE = """
TEST(GltfSamples, {name}) {{
  auto path = get_path("{relative}");
  if(!std::filesystem::exists(path))
  {{
    std::cerr << path << " not exists" << std::endl;
  }}
  auto bytes = ReadAllBytes(path);
  if(bytes.empty())
  {{
    std::cerr << path << " 0 bytes" << std::endl;
    return;
  }}
  if(path.extension()==".glb")
  {{
    auto glb = gltfjson::Glb::Parse(bytes);
    EXPECT_TRUE(glb);
    gltfjson::tree::Parser parser(glb->JsonChunk);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }}
  else{{
    gltfjson::tree::Parser parser(bytes);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }}
}}
"""


def process(gltf_dir: pathlib.Path, path: pathlib.Path):
    with path.open("w", encoding="utf-8") as w:
        w.write(
            """#include <cstdlib>
#include <gtest/gtest.h>
#include <gltfjson.h>

static std::filesystem::path get_path(std::string_view relative) {
  std::filesystem::path base = std::getenv("GLTF_SAMPLE_MODELS");
  return base / "2.0" / relative;
}

static std::vector<uint8_t>
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
"""
        )

        for e in gltf_dir.rglob("*"):
            if "Unicode❤♻Test" in str(e):
                # skip
                continue
            if e.is_file:
                ext = e.suffix.lower()
                if ext == ".gltf" or ext == ".glb":
                    rel = e.relative_to(gltf_dir)
                    name = str(rel.parent).replace("\\", "_")
                    w.write(
                        TEMPLATE.format(
                            name=name.replace(" ", "_").replace("-", "_"),
                            relative=str(rel).replace("\\", "/"),
                        )
                    )


if __name__ == "__main__":
    sample_models = os.environ["GLTF_SAMPLE_MODELS"]

    process(pathlib.Path(sample_models) / "2.0", HERE.parent / "tests/gltf_samples.cpp")
