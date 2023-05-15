#include <gltfjson/format.h>
#include <gltfjson/json.h>
#include <gtest/gtest.h>

TEST(TestJson, ParsePrimitive)
{
  {
    auto SRC = u8"true";
    gltfjson::json::Parser parser(SRC);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
    if (result) {
      EXPECT_EQ(*result, gltfjson::json::Value(SRC));
    }
  }
  {
    auto SRC = u8"false";
    gltfjson::json::Parser parser(SRC);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
    if (result) {
      EXPECT_EQ(*result, gltfjson::json::Value(SRC));
    }
  }
  {
    auto SRC = u8"null";
    gltfjson::json::Parser parser(SRC);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
    if (result) {
      EXPECT_EQ(*result, gltfjson::json::Value(SRC));
    }
  }
}

TEST(TestJson, ParseNumber)
{
  {
    auto SRC = u8"1";
    gltfjson::json::Parser parser(SRC);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
    if (result) {
      EXPECT_EQ(*result, gltfjson::json::Value(SRC));
    }
  }
  {
    auto SRC = u8"-1";
    gltfjson::json::Parser parser(SRC);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
    if (result) {
      EXPECT_EQ(*result, gltfjson::json::Value(SRC));
    }
  }
  {
    auto SRC = u8"1e-5";
    gltfjson::json::Parser parser(SRC);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
    if (result) {
      EXPECT_EQ(*result, gltfjson::json::Value(SRC));
    }
  }
  {
    auto SRC = u8"1.1";
    gltfjson::json::Parser parser(SRC);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
    if (result) {
      EXPECT_EQ(*result, gltfjson::json::Value(SRC));
    }
  }
}

TEST(TestJson, ParseString)
{
  {
    auto SRC = u8R"(
"abc"
)";
    gltfjson::json::Parser parser(SRC);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
    if (result) {
      EXPECT_EQ(*result, gltfjson::json::Value(u8"\"abc\""));
    }
  }
}

TEST(TestJson, ParseArray)
{
  {
    auto SRC = u8"[ ]";
    gltfjson::json::Parser parser(SRC);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
    EXPECT_EQ(parser.Values.size(), 1);
    EXPECT_EQ(parser.ChildCount(*result), 0);
  }
  {
    auto SRC = u8"[1, 2, 3]";
    gltfjson::json::Parser parser(SRC);
    auto result = parser.Parse();
    EXPECT_EQ(parser.Values.size(), 4);
    EXPECT_TRUE(result);
    if (result) {
      EXPECT_EQ(parser.ChildCount(*result), 3);
      EXPECT_EQ(*parser.GetItem(*result, 0), gltfjson::json::Value(u8"1"));
    }
  }
  {
    auto SRC = u8"[1, [2, 3]]";
    gltfjson::json::Parser parser(SRC);
    auto result = parser.Parse();
    EXPECT_EQ(parser.Values.size(), 5);
    EXPECT_TRUE(result);
    if (result) {
      auto inner = parser.GetItem(*result, 1);
      EXPECT_EQ(*parser.GetItem(*inner, 1), gltfjson::json::Value(u8"3"));
    }
  }
}

TEST(TestJson, ParseObject)
{
  {
    auto SRC = u8"{ }";
    gltfjson::json::Parser parser(SRC);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
    EXPECT_EQ(parser.Values.size(), 1);
    EXPECT_EQ(parser.ChildCount(*result), 0);
  }
  {
    auto SRC = u8"{\"key\": 1}";
    gltfjson::json::Parser parser(SRC);
    auto result = parser.Parse();
    EXPECT_EQ(parser.Values.size(), 3);
    if (result) {
      EXPECT_EQ(parser.ChildCount(*result), 1);
      EXPECT_EQ(*parser.GetProperty(*result, u8"key"),
                gltfjson::json::Value(u8"1"));
    }
  }
  {
    auto SRC = u8"{\"key\": {\"key2\": 2}}";
    gltfjson::json::Parser parser(SRC);
    auto result = parser.Parse();
    EXPECT_EQ(parser.Values.size(), 5);
    if (result) {
      auto inner = parser.GetProperty(*result, u8"key");
      EXPECT_EQ(*parser.GetProperty(*inner, u8"key2"),
                gltfjson::json::Value(u8"2"));
    }
  }
}
