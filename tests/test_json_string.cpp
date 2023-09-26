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
TEST(TestJson, ParseStringUnescape)
{
  {
    auto SRC = u8R"(
"\""
)";
    gltfjson::Parser parser(SRC);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
    if (result) {
      EXPECT_EQ(result->U8String(), u8"\"");
    }
  }
  {
    auto SRC = u8R"(
"\\"
)";
    gltfjson::Parser parser(SRC);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
    if (result) {
      EXPECT_EQ(result->U8String(), u8"\\");
    }
  }
  {
    auto SRC = u8R"(
"\/"
)";
    gltfjson::Parser parser(SRC);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
    if (result) {
      EXPECT_EQ(result->U8String(), u8"/");
    }
  }
  //   {
  //     auto SRC = u8R"(
  // "\b"
  // )";
  //     gltfjson::Parser parser(SRC);
  //     auto result = parser.Parse();
  //     EXPECT_TRUE(result);
  //     if (result) {
  //       EXPECT_EQ(result->U8String(), u8"\b");
  //     }
  //   }
  //   {
  //     auto SRC = u8R"(
  // "\f"
  // )";
  //     gltfjson::Parser parser(SRC);
  //     auto result = parser.Parse();
  //     EXPECT_TRUE(result);
  //     if (result) {
  //       EXPECT_EQ(result->U8String(), u8"\f");
  //     }
  //   }
  {
    auto SRC = u8R"(
"\n"
)";
    gltfjson::Parser parser(SRC);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
    if (result) {
      EXPECT_EQ(result->U8String(), u8"\n");
    }
  }
  {
    auto SRC = u8R"(
"\r"
)";
    gltfjson::Parser parser(SRC);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
    if (result) {
      EXPECT_EQ(result->U8String(), u8"\r");
    }
  }
  {
    auto SRC = u8R"(
"\t"
)";
    gltfjson::Parser parser(SRC);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
    if (result) {
      EXPECT_EQ(result->U8String(), u8"\t");
    }
  }
  {
    auto SRC = u8R"(
"\u304b"
)";
    gltfjson::Parser parser(SRC);
    auto result = parser.Parse();
    EXPECT_TRUE(result);
    if (result) {
      EXPECT_EQ(result->U8String(), u8"か");
    }
  }
}
