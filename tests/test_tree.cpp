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

TEST(TestJsonTree, ParseString)
{
  {
    auto SRC = u8R"(
"abc"
)";
    gltfjson::tree::Parser parser(SRC);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
    if (result) {
      EXPECT_EQ(result->U8String(), u8"abc");
    }
  }
  {
    // unescape slash
    auto SRC = u8R"(
"a\/b"
)";
    gltfjson::tree::Parser parser(SRC);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
    if (result) {
      EXPECT_EQ(result->U8String(), u8"a/b");
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
    if (auto array = result->Array()) {
      EXPECT_TRUE(array->empty());
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
    if (auto array = result->Array()) {
      EXPECT_EQ(array->size(), 3);
      EXPECT_EQ(*(*array)[0]->Ptr<float>(), 1);
    }
  }
  {
    auto SRC = u8"[1, [2, 3]]";
    gltfjson::tree::Parser parser(SRC);
    auto result = parser.Parse();
    if (auto array = result->Array()) {
      auto inner = (*array)[1]->Array();
      EXPECT_EQ(*(*inner)[1]->Ptr<float>(), 3);
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

    if (auto object = result->Object()) {
      EXPECT_TRUE(object->empty());
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
