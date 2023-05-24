#include <gltfjson/json_tree.h>
#include <gtest/gtest.h>

TEST(TestJsonTree, Parse)
{
  {
    auto SRC = u8"true";
    gltfjson::tree::Parser parser(SRC);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
    if (result) {
      EXPECT_EQ(result->Value<bool>(), true);
    }
  }
  {
    auto SRC = u8"false";
    gltfjson::tree::Parser parser(SRC);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
    if (result) {
      EXPECT_EQ(result->Value<bool>(), false);
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
      EXPECT_EQ(*result->Value<double>(), 1);
    }
  }
  {
    auto SRC = u8"-1";
    gltfjson::tree::Parser parser(SRC);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
    if (result) {
      EXPECT_EQ(*result->Value<double>(), -1);
    }
  }
  {
    auto SRC = u8"1e-5";
    gltfjson::tree::Parser parser(SRC);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
    if (result) {
      EXPECT_EQ(*result->Value<double>(), 1e-5);
    }
  }
  {
    auto SRC = u8"1.1";
    gltfjson::tree::Parser parser(SRC);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
    if (result) {
      EXPECT_EQ(*result->Value<double>(), 1.1);
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
      EXPECT_EQ(result->Value<std::u8string>(), u8"abc");
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
      EXPECT_TRUE(array->m_values.empty());
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
      EXPECT_EQ(array->m_values.size(), 3);
      EXPECT_EQ(*array->m_values[0]->Value<double>(), 1);
    }
  }
  {
    auto SRC = u8"[1, [2, 3]]";
    gltfjson::tree::Parser parser(SRC);
    auto result = parser.Parse();
    if (auto array = result->Array()) {
      auto inner = array->m_values[1]->Array();
      EXPECT_EQ(*inner->m_values[1]->Value<double>(), 3);
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
      EXPECT_TRUE(object->m_values.empty());
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
      EXPECT_EQ(*result->Get(u8"key")->Value<double>(), 1);
    }
  }
  {
    auto SRC = u8"{\"key\": {\"key2\": 2}}";
    gltfjson::tree::Parser parser(SRC);
    auto result = parser.Parse();
    if (result) {
      auto inner = result->Get(u8"key");
      EXPECT_EQ(*inner->Get(u8"key2")->Value<double>(), 2);
    }
  }
}
