#include <gltfjson/json_tree_parser.h>
#include <gtest/gtest.h>

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
TEST(TestJsonTree, ParseStringUnescape)
{
  {
    // unescape slash
    auto SRC = u8R"(
"\""
)";
    gltfjson::tree::Parser parser(SRC);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
    if (result) {
      EXPECT_EQ(result->U8String(), u8"\"");
    }
  }
  {
    // unescape slash
    auto SRC = u8R"(
"\\"
)";
    gltfjson::tree::Parser parser(SRC);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
    if (result) {
      EXPECT_EQ(result->U8String(), u8"\\");
    }
  }
  {
    // unescape slash
    auto SRC = u8R"(
"\/"
)";
    gltfjson::tree::Parser parser(SRC);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
    if (result) {
      EXPECT_EQ(result->U8String(), u8"/");
    }
  }
  //   {
  //     // unescape slash
  //     auto SRC = u8R"(
  // "\b"
  // )";
  //     gltfjson::tree::Parser parser(SRC);
  //     auto result = parser.Parse();
  //     EXPECT_TRUE(result);
  //     if (result) {
  //       EXPECT_EQ(result->U8String(), u8"\b");
  //     }
  //   }
  //   {
  //     // unescape slash
  //     auto SRC = u8R"(
  // "\f"
  // )";
  //     gltfjson::tree::Parser parser(SRC);
  //     auto result = parser.Parse();
  //     EXPECT_TRUE(result);
  //     if (result) {
  //       EXPECT_EQ(result->U8String(), u8"\f");
  //     }
  //   }
  {
    // unescape slash
    auto SRC = u8R"(
"\n"
)";
    gltfjson::tree::Parser parser(SRC);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
    if (result) {
      EXPECT_EQ(result->U8String(), u8"\n");
    }
  }
  {
    // unescape slash
    auto SRC = u8R"(
"\r"
)";
    gltfjson::tree::Parser parser(SRC);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
    if (result) {
      EXPECT_EQ(result->U8String(), u8"\r");
    }
  }
  {
    // unescape slash
    auto SRC = u8R"(
"\t"
)";
    gltfjson::tree::Parser parser(SRC);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
    if (result) {
      EXPECT_EQ(result->U8String(), u8"\t");
    }
  }
  {
    // unescape slash
    auto SRC = u8R"(
"\u304b"
)";
    gltfjson::tree::Parser parser(SRC);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
    if (result) {
      EXPECT_EQ(result->U8String(), u8"か");
    }
  }
}
