#include <gltfjson/json_tree_parser.h>
#include <gtest/gtest.h>

TEST(TestJsonTree, Parse)
{
  {
    auto SRC = u8"true";
    gltfjson::tree::Parser parser(SRC);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
    if (result) {
      EXPECT_EQ(*result->Ptr<bool>(), true);
    }
  }
  {
    auto SRC = u8"false";
    gltfjson::tree::Parser parser(SRC);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
    if (result) {
      EXPECT_EQ(*result->Ptr<bool>(), false);
    }
  }
  {
    auto SRC = u8"null";
    gltfjson::tree::Parser parser(SRC);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
    if (result) {
      EXPECT_TRUE(result->IsNull());
    }
  }
}

TEST(TestJsonTree, ParseNumber)
{
  {
    auto SRC = u8"1";
    gltfjson::tree::Parser parser(SRC);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
    if (result) {
      EXPECT_EQ(*result->Ptr<float>(), 1);
    }
  }
  {
    auto SRC = u8"-1";
    gltfjson::tree::Parser parser(SRC);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
    if (result) {
      EXPECT_EQ(*result->Ptr<float>(), -1);
    }
  }
  {
    auto SRC = u8"1e-5";
    gltfjson::tree::Parser parser(SRC);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
    if (result) {
      EXPECT_EQ(*result->Ptr<float>(), 1e-5f);
    }
  }
  {
    auto SRC = u8"1.1";
    gltfjson::tree::Parser parser(SRC);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
    if (result) {
      EXPECT_EQ(*result->Ptr<float>(), 1.1f);
    }
  }
}

TEST(TestJsonTree, ParseArray)
{
  {
    auto SRC = u8"[]";
    gltfjson::tree::Parser parser(SRC);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
    if (auto array =
          std::dynamic_pointer_cast<gltfjson::tree::ArrayNode>(result)) {
      EXPECT_TRUE(array->Value.empty());
    }
  }
  {
    auto SRC = u8"[ ]";
    gltfjson::tree::Parser parser(SRC);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
  }
  {
    auto SRC = u8"[1, 2, 3]";
    gltfjson::tree::Parser parser(SRC);
    auto result = parser.Parse();
    if (auto array =
          std::dynamic_pointer_cast<gltfjson::tree::ArrayNode>(result)) {
      EXPECT_EQ(array->Value.size(), 3);
      EXPECT_EQ(*array->Value[0]->Ptr<float>(), 1);
    }
  }
  {
    auto SRC = u8"[1, [2, 3]]";
    gltfjson::tree::Parser parser(SRC);
    auto result = parser.Parse();
    if (auto array =
          std::dynamic_pointer_cast<gltfjson::tree::ArrayNode>(result)) {
      auto inner =
        std::dynamic_pointer_cast<gltfjson::tree::ArrayNode>(array->Value[1]);
      EXPECT_EQ(*inner->Value[1]->Ptr<float>(), 3);
    }
  }
}

TEST(TestJsonTree, ParseObject)
{
  {
    auto SRC = u8"{}";
    gltfjson::tree::Parser parser(SRC);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
    if (result) {
      EXPECT_EQ(result->Size(), 0);
    }

    if (auto object =
          std::dynamic_pointer_cast<gltfjson::tree::ObjectNode>(result)) {
      EXPECT_TRUE(object->Value.empty());
    }
  }
  {
    auto SRC = u8"{ }";
    gltfjson::tree::Parser parser(SRC);
    auto result = parser.Parse();
    if (result) {
      EXPECT_EQ(result->Size(), 0);
    }
  }
  {
    auto SRC = u8"{\"key\": 1}";
    gltfjson::tree::Parser parser(SRC);
    auto result = parser.Parse();
    if (result) {
      EXPECT_EQ(result->Size(), 1);
      EXPECT_EQ(*result->Get(u8"key")->Ptr<float>(), 1);
    }
  }
  {
    auto SRC = u8"{\"key\": {\"key2\": 2}}";
    gltfjson::tree::Parser parser(SRC);
    auto result = parser.Parse();
    if (result) {
      auto inner = result->Get(u8"key");
      EXPECT_EQ(*inner->Get(u8"key2")->Ptr<float>(), 2);
    }
  }
}
