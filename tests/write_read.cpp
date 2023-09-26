#include <gltfjson.h>
#include <gltfjson/json_tree_exporter.h>
#include <gtest/gtest.h>
#include <sstream>

TEST(WriteRead, Null)
{
  std::stringstream ss;
  gltfjson::StringSink write = [&ss](std::string_view src) mutable {
    ss.write(src.data(), src.size());
  };
  gltfjson::tree::Exporter exporter{ write };

  auto json = gltfjson::tree::NewNode();
  exporter.Export(json);
  EXPECT_EQ(ss.str(), "null");
}

TEST(WriteRead, Bool)
{
  {
    std::stringstream ss;
    gltfjson::StringSink write = [&ss](std::string_view src) mutable {
      ss.write(src.data(), src.size());
    };
    gltfjson::tree::Exporter exporter{ write };

    auto json = gltfjson::tree::NewNode(true);
    exporter.Export(json);
    EXPECT_EQ(ss.str(), "true");
  }
  {
    std::stringstream ss;
    gltfjson::StringSink write = [&ss](std::string_view src) mutable {
      ss.write(src.data(), src.size());
    };
    gltfjson::tree::Exporter exporter{ write };

    auto json = gltfjson::tree::NewNode(false);
    exporter.Export(json);
    EXPECT_EQ(ss.str(), "false");
  }
}

TEST(WriteRead, Number)
{
  {
    std::stringstream ss;
    gltfjson::StringSink write = [&ss](std::string_view src) mutable {
      ss.write(src.data(), src.size());
    };
    gltfjson::tree::Exporter exporter{ write };

    auto json = gltfjson::tree::NewNode(1.0f);
    exporter.Export(json);
    EXPECT_EQ(ss.str(), "1");
  }
  {
    std::stringstream ss;
    gltfjson::StringSink write = [&ss](std::string_view src) mutable {
      ss.write(src.data(), src.size());
    };
    gltfjson::tree::Exporter exporter{ write };

    auto json = gltfjson::tree::NewNode(1.1f);
    exporter.Export(json);
    EXPECT_EQ(ss.str(), "1.1");
  }
}

TEST(WriteRead, Array)
{
  {
    std::stringstream ss;
    gltfjson::StringSink write = [&ss](std::string_view src) mutable {
      ss.write(src.data(), src.size());
    };
    gltfjson::tree::Exporter exporter{ write };

    auto json = gltfjson::tree::NewNode(gltfjson::tree::ArrayValue{
      gltfjson::tree::NewNode(),
      gltfjson::tree::NewNode(false),
      gltfjson::tree::NewNode(-1.5f),
    });
    exporter.Export(json);
    EXPECT_EQ(ss.str(), "[null,false,-1.5]");
  }
}

TEST(WriteRead, Object)
{
  {
    std::stringstream ss;
    gltfjson::StringSink write = [&ss](std::string_view src) mutable {
      ss.write(src.data(), src.size());
    };
    gltfjson::tree::Exporter exporter{ write };

    auto array = gltfjson::tree::NewNode(gltfjson::tree::ArrayValue{
      gltfjson::tree::NewNode(),
      gltfjson::tree::NewNode(false),
      gltfjson::tree::NewNode(-1.5f),
    });
    auto json = gltfjson::tree::NewNode(
      gltfjson::tree::ObjectValue{ { u8"key", array } });
    exporter.Export(json);
    EXPECT_EQ(ss.str(), "{\"key\":[null,false,-1.5]}");
  }
}
