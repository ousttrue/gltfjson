#include <gltfjson/json.h>
#include <gtest/gtest.h>

TEST(TestJson, ParsePrimitive)
{
  {
    auto SRC = u8"true";
    gltfjson::Parser parser(SRC);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
    if (result) {
      EXPECT_EQ(*result, gltfjson::Value(SRC));
    }
  }
  {
    auto SRC = u8"false";
    gltfjson::Parser parser(SRC);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
    if (result) {
      EXPECT_EQ(*result, gltfjson::Value(SRC));
    }
  }
  {
    auto SRC = u8"null";
    gltfjson::Parser parser(SRC);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
    if (result) {
      EXPECT_EQ(*result, gltfjson::Value(SRC));
    }
  }
}

TEST(TestJson, ParseNumber)
{
  {
    auto SRC = u8"1";
    gltfjson::Parser parser(SRC);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
    if (result) {
      EXPECT_EQ(*result, gltfjson::Value(SRC));
    }
  }
  {
    auto SRC = u8"-1";
    gltfjson::Parser parser(SRC);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
    if (result) {
      EXPECT_EQ(*result, gltfjson::Value(SRC));
    }
  }
  {
    auto SRC = u8"1e-5";
    gltfjson::Parser parser(SRC);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
    if (result) {
      EXPECT_EQ(*result, gltfjson::Value(SRC));
    }
  }
  {
    auto SRC = u8"1.1";
    gltfjson::Parser parser(SRC);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
    if (result) {
      EXPECT_EQ(*result, gltfjson::Value(SRC));
    }
  }
}

TEST(TestJson, ParseString)
{
  {
    auto SRC = u8R"(
"abc"
)";
    gltfjson::Parser parser(SRC);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
    if (result) {
      EXPECT_EQ(*result, gltfjson::Value(u8"\"abc\""));
    }
  }
}

TEST(TestJson, ParseArray)
{
  {
    auto SRC = u8"[ ]";
    gltfjson::Parser parser(SRC);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
    EXPECT_EQ(parser.Values.size(), 1);
    EXPECT_EQ(result->Size(), 0);
  }
  {
    auto SRC = u8"[1, 2, 3]";
    gltfjson::Parser parser(SRC);
    auto result = parser.Parse();
    EXPECT_EQ(parser.Values.size(), 4);
    EXPECT_TRUE(result);
    if (result) {
      EXPECT_EQ(result->Size(), 3);
      EXPECT_EQ(*result->Get(0), gltfjson::Value(u8"1"));
    }
  }
  {
    auto SRC = u8"[1, [2, 3]]";
    gltfjson::Parser parser(SRC);
    auto result = parser.Parse();
    EXPECT_EQ(parser.Values.size(), 5);
    EXPECT_TRUE(result);
    if (result) {
      auto inner = result->Get(1);
      EXPECT_EQ(*inner->Get(1), gltfjson::Value(u8"3"));
    }
  }
}

TEST(TestJson, ParseObject)
{
  {
    auto SRC = u8"{ }";
    gltfjson::Parser parser(SRC);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
    EXPECT_EQ(parser.Values.size(), 1);
    EXPECT_EQ(result->Size(), 0);
  }
  {
    auto SRC = u8"{\"key\": 1}";
    gltfjson::Parser parser(SRC);
    auto result = parser.Parse();
    EXPECT_EQ(parser.Values.size(), 3);
    if (result) {
      EXPECT_EQ(result->Size(), 1);
      EXPECT_EQ(*result->Get(u8"key"), gltfjson::Value(u8"1"));
    }
  }
  {
    auto SRC = u8"{\"key\": {\"key2\": 2}}";
    gltfjson::Parser parser(SRC);
    auto result = parser.Parse();
    EXPECT_EQ(parser.Values.size(), 5);
    if (result) {
      auto inner = result->Get(u8"key");
      EXPECT_EQ(*inner->Get(u8"key2"), gltfjson::Value(u8"2"));
    }
  }
}
