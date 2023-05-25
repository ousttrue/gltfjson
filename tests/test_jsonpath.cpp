#include <gltfjson/json_tree_parser.h>
#include <gtest/gtest.h>
#include <iostream>

static std::string_view
from_u8(std::u8string_view src)
{
  return { (const char*)src.data(), (const char*)src.data() + src.size() };
}

TEST(TestJsonPath, ConcatInt)
{
  std::u8string buf;
  gltfjson::tree::concat_int(buf, 1);
  EXPECT_EQ(buf, u8"1");
}

TEST(TestJsonPath, Test)
{
  auto SRC = u8"{\"key\": {\"key2\": 2}, \"ar\": [1,2, 3]}";
  gltfjson::tree::Parser parser(SRC);
  auto result = parser.Parse();
  EXPECT_TRUE(result);
  if (result) {
    // auto inner = result->Get(u8"key");
    // EXPECT_EQ(*inner->Get(u8"key2")->Ptr<float>(), 2);
    std::vector<std::u8string> list;
    gltfjson::tree::EnterJson enter = [&list](const auto& node, auto jsonpath) {
      // std::cout << from_u8(jsonpath) << std::endl;
      list.push_back({ jsonpath.begin(), jsonpath.end() });
      return true;
    };
    gltfjson::tree::LeaveJson leave = []() {};

    gltfjson::tree::TraverseJson(enter, leave, result);
    EXPECT_EQ(list.size(), 7);
    EXPECT_EQ(list[0], u8"/");
    EXPECT_EQ(list[1], u8"/key");
    EXPECT_EQ(list[2], u8"/key/key2");
    EXPECT_EQ(list[3], u8"/ar");
    EXPECT_EQ(list[4], u8"/ar/0");
    EXPECT_EQ(list[5], u8"/ar/1");
    EXPECT_EQ(list[6], u8"/ar/2");
  }
}
