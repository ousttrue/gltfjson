#include <gltfjson/json_parser.h>
#include <gtest/gtest.h>

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

// '"'
// '\'
// '/'
// 'b'
// 'f'
// 'n'
// 'r'
// 't'
// 'u' hex hex hex hex
TEST(TestJson, ParseStringEscape)
{
  {
    auto SRC = u8R"(
"\\""
)";
    gltfjson::Parser parser(SRC);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
    if (result) {
      EXPECT_EQ(*result, gltfjson::Value(u8"\"\\\"\""));
    }
  }
}
