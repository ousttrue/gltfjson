#include <gltfjson/base64.h>
#include <gtest/gtest.h>
#include <stdint.h>
#include <string>
#include <string_view>

auto DECODED = "ABCDEFG";
auto ENCODED = "QUJDREVGRw==";

TEST(Base64, Encode)
{
  auto encoded = gltfjson::base64::Encode(DECODED);
  EXPECT_EQ(encoded, ENCODED);
}

TEST(Base64, Decode)
{
  auto decoded = gltfjson::base64::Decode(ENCODED);
  EXPECT_EQ(std::string((char*)decoded.data(), decoded.size()), DECODED);
}
