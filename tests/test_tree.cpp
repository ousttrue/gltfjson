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
      EXPECT_TRUE(result->IsTrue());
    }
  }
  {
    auto SRC = u8"false";
    gltfjson::tree::Parser parser(SRC);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
    if (result) {
      EXPECT_TRUE(result->IsFalse());
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
