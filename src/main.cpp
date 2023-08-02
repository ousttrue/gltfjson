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
Node(const std::string& name)
{
  return ftxui::Renderer([name](bool focused) {
    auto element = ftxui::text(name);
    if (focused) {
      element = element | ftxui::inverted;
    }
    return element;
  });
}

void
Build(const std::shared_ptr<ftxui::ComponentBase>& c,
      const gltfjson::tree::NodePtr& json)
{
  if (auto a = json->Array()) {
    for (auto i = 0; i < a->size(); ++i) {
      std::stringstream ss;
      ss << i;
      c->Add(Node(ss.str()));
      Build(c, (*a)[i]);
    }
  } else if (auto o = json->Object()) {
    for (auto kv : *o) {
      std::string name{ (const char*)kv.first.data(), kv.first.size() };
      c->Add(Node(name));
      Build(c, kv.second);
    }
  }
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

  auto list = ftxui::Container::Vertical({});
  Build(list, result);

  Tui(list);

  return 0;
}
