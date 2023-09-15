#include <gltfjson.h>
#include <gltfjson/json_tree_bin_serializer.h>
#include <gltfjson/json_tree_exporter.h>
#include <gtest/gtest.h>

TEST(TestBinSerializer, BinSerializer)
{
  auto json = gltfjson::tree::NewNode(gltfjson::tree::ObjectValue{});
  auto buffers = json->SetProperty(u8"buffers", gltfjson::tree::ArrayValue{});
  auto bufferViews =
    json->SetProperty(u8"bufferViews", gltfjson::tree::ArrayValue{});
  auto accessors =
    json->SetProperty(u8"accessors", gltfjson::tree::ArrayValue{});
  gltfjson::Root gltf(json);

  std::vector<uint8_t> src;
  gltfjson::BinWriter w(src);

  uint8_t data[] = { 1, 2, 3, 4 };
  auto [offset, length] = w.PushBufferView(data);
  auto buffer = buffers->Add(gltfjson::tree::ObjectValue{});
  buffer->SetProperty(u8"byteLength", (float)4);

  auto bufferView = bufferViews->Add(gltfjson::tree::ObjectValue{});
  bufferView->SetProperty(u8"buffer", (float)0);
  bufferView->SetProperty(u8"byteOffset", (float)offset);
  bufferView->SetProperty(u8"byteLength", (float)length);

  auto accessor = accessors->Add(gltfjson::tree::ObjectValue{});
  accessor->SetProperty(u8"bufferView", (float)0);
  accessor->SetProperty(u8"type", u8"SCALAR");
  accessor->SetProperty(u8"componentType", (float)5121);
  accessor->SetProperty(u8"count", (float)4);

  gltfjson::Bin bin{ .Bytes = src };
  std::vector<uint8_t> dst;
  gltfjson::tree::BinSerializer s(gltf, bin, dst);
  s.Serialize({}, {});

  EXPECT_EQ(src, dst);
}
