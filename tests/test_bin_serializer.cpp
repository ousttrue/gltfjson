#include <gltfjson.h>
#include <gltfjson/json_tree_bin_serializer.h>
#include <gltfjson/json_tree_exporter.h>
#include <gtest/gtest.h>

TEST(TestBinSerializer, BinSerializer)
{
  auto json = gltfjson::tree::NewNode(gltfjson::tree::ObjectValue{});
  auto bufferViews =
    json->SetProperty(u8"bufferViews", gltfjson::tree::ArrayValue{});
  auto accessors =
    json->SetProperty(u8"accessors", gltfjson::tree::ArrayValue{});
  gltfjson::Root gltf(json);

  std::vector<uint8_t> src;
  gltfjson::BinWriter w(src);

  uint8_t data[] = { 1, 2, 3, 4 };
  auto [offset, length] = w.PushBufferView(data);
  auto buffer = bufferViews->Add(gltfjson::tree::ObjectValue{});
  buffer->SetProperty(u8"buffer", (float)0);
  buffer->SetProperty(u8"offset", (float)offset);
  buffer->SetProperty(u8"length", (float)length);

  auto accessor = accessors->Add(gltfjson::tree::ObjectValue{});
  accessor->SetProperty(u8"bufferView", (float)0);
  accessor->SetProperty(u8"type", u8"SCALAR");
  accessor->SetProperty(u8"componentType", (float)5121);

  gltfjson::Bin bin;
  std::vector<uint8_t> dst;
  gltfjson::tree::BinSerializer s(gltf, bin, dst);
  s.Serialize({}, {});

  EXPECT_EQ(src, dst);
}
