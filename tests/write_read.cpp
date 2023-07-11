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

  auto json = std::make_shared<gltfjson::tree::Node>();
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

    auto json = std::make_shared<gltfjson::tree::Node>(true);
    exporter.Export(json);
    EXPECT_EQ(ss.str(), "true");
  }
  {
    std::stringstream ss;
    gltfjson::StringSink write = [&ss](std::string_view src) mutable {
      ss.write(src.data(), src.size());
    };
    gltfjson::tree::Exporter exporter{ write };

    auto json = std::make_shared<gltfjson::tree::Node>(false);
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

    auto json = std::make_shared<gltfjson::tree::Node>(1.0f);
    exporter.Export(json);
    EXPECT_EQ(ss.str(), "1");
  }
  {
    std::stringstream ss;
    gltfjson::StringSink write = [&ss](std::string_view src) mutable {
      ss.write(src.data(), src.size());
    };
    gltfjson::tree::Exporter exporter{ write };

    auto json = std::make_shared<gltfjson::tree::Node>(1.1f);
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

    auto json =
      std::make_shared<gltfjson::tree::Node>(gltfjson::tree::ArrayValue{
        std::make_shared<gltfjson::tree::Node>(),
        std::make_shared<gltfjson::tree::Node>(false),
        std::make_shared<gltfjson::tree::Node>(-1.5f),
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

    auto array =
      std::make_shared<gltfjson::tree::Node>(gltfjson::tree::ArrayValue{
        std::make_shared<gltfjson::tree::Node>(),
        std::make_shared<gltfjson::tree::Node>(false),
        std::make_shared<gltfjson::tree::Node>(-1.5f),
      });
    auto json = std::make_shared<gltfjson::tree::Node>(
      gltfjson::tree::ObjectValue{ { u8"key", array } });
    exporter.Export(json);
    EXPECT_EQ(ss.str(), "{\"key\":[null,false,-1.5]}");
  }
}
