#include <array>
#include <filesystem>
#include <fstream>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <gltfjson.h>
#include <iostream>
#include <vector>

static std::vector<uint8_t>
ReadAllBytes(const std::filesystem::path& filename)
{
  std::ifstream ifs(filename, std::ios::binary | std::ios::ate);
  if (!ifs) {
    return {};
  }
  auto pos = ifs.tellg();
  std::vector<uint8_t> buffer(pos);
  ifs.seekg(0, std::ios::beg);
  ifs.read((char*)buffer.data(), pos);
  return buffer;
}

template<size_t N>
void
Print(const std::array<const char*, N>& array)
{
  std::vector<ftxui::Element> values;
  for (auto c : array) {
    values.push_back(ftxui::text(c) | ftxui::color(ftxui::Color::Red));
  }
  auto document = ftxui::hbox(values);
  auto screen = ftxui::Screen::Create(ftxui::Dimension::Full(),
                                      ftxui::Dimension::Fit(document));
  ftxui::Render(screen, document);
  std::cout << screen.ToString() << std::flush;
}

ftxui::Component
jsonComponent(const std::string& key,
              const gltfjson::tree::NodePtr& value,
              int level = 0)
{

  struct JsonComponent : ftxui::ComponentBase
  {
    ftxui::Component m_children;
    std::string m_key;
    gltfjson::tree::NodePtr m_json;
    int m_level;

    JsonComponent(const std::string& key,
                  const gltfjson::tree::NodePtr& value,
                  int level = 0)
      : m_key(key)
      , m_json(value)
      , m_level(level)
    {
      m_children = ftxui::Container::Vertical({});
      Add(m_children);

      m_children->Add(ftxui::Renderer([=](bool focused) {
        std::stringstream ss;
        for (int i = 0; i < m_level; ++i) {
          ss << "  ";
        }
        ss << m_key;
        auto element = ftxui::text(ss.str());

        if (focused) {
          element = element | ftxui::inverted | ftxui::focus;
        }
        return element;
      }));

      if (auto a =
            std::dynamic_pointer_cast<gltfjson::tree::ArrayNode>(value)) {
        for (auto i = 0; i < a->Value.size(); ++i) {
          std::stringstream ss;
          ss << i;
          m_children->Add(jsonComponent(ss.str(), a->Value[i], level + 1));
        }
      } else if (auto o = std::dynamic_pointer_cast<gltfjson::tree::ObjectNode>(
                   value)) {
        for (auto kv : o->Value) {
          std::string name{ (const char*)kv.first.data(), kv.first.size() };
          m_children->Add(jsonComponent(name, kv.second, level + 1));
        }
      }
    }
  };

  return std::make_shared<JsonComponent>(key, value, level);
}

void
Tui(ftxui::Component root)
{
  auto screen = ftxui::ScreenInteractive::Fullscreen();
  auto event_component = CatchEvent(root, [&](ftxui::Event event) {
    if (event == ftxui::Event::Character('q') ||
        event == ftxui::Event::Escape) {
      screen.ExitLoopClosure()();
      return true;
    }

    return false;
  });
  screen.Loop(event_component);
}

int
main(int argc, char** argv)
{
  if (argc < 2) {
    Print<3>({ "usage: ", argv[0], " file.{gltf,glb,vrm...}" });
    return 1;
  }

  auto bytes = ReadAllBytes(argv[1]);
  if (bytes.empty()) {
    Print<2>({ argv[1], " 0 bytes" });
    return 2;
  }

  auto glb = gltfjson::Glb::Parse(bytes);
  gltfjson::tree::NodePtr result;
  if (glb) {
    gltfjson::tree::Parser parser(glb->JsonChunk);
    result = parser.Parse();
  } else {
    // try gltf
    gltfjson::tree::Parser parser(bytes);
    result = parser.Parse();
  }
  if (!result) {
    Print<1>({ "fail to parse" });
    return 3;
  }

  auto root = jsonComponent("/", result, 0);
  auto scroll =
    ftxui::Renderer(root, [root]() { return root->Render() | ftxui::frame; });

  Tui(scroll);

  return 0;
}
