#pragma once
#include "json_tree.h"
#include "json_writer.h"
#include <ostream>
#include <string_view>

namespace gltfjson {
namespace tree {
struct Exporter
{
  JsonWriter m_writer;

  Exporter(const StringSink& sink)
    : m_writer(sink)
  {
  }

  void Export(const NodePtr& node)
  {
    if (node->IsNull()) {
      m_writer.null();
    } else if (auto p = node->Ptr<bool>()) {
      m_writer.value(*p);
    } else if (auto p = node->Ptr<float>()) {
      m_writer.value(*p);
    } else if (auto p = node->Ptr<std::u8string>()) {
      m_writer.value(*p);
    } else if (auto p = std::dynamic_pointer_cast<tree::ArrayNode>(node)) {
      m_writer.array_open();
      for (auto child : p->Value) {
        Export(child);
      }
      m_writer.array_close();
    } else if (auto p = std::dynamic_pointer_cast<tree::ObjectNode>(node)) {
      m_writer.object_open();
      for (auto& kv : p->Value) {
        m_writer.key(kv.first);
        Export(kv.second);
      }
      m_writer.object_close();
    } else {
      assert(false);
    }
  }
};

inline std::ostream&
operator<<(std::ostream& os, const std::shared_ptr<Node>& n)
{
  auto sink = [&os](std::string_view s) mutable { os << s; };
  Exporter e(sink);
  e.Export(n);
  return os;
}

}
}
