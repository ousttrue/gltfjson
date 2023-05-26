#pragma once
#include "json_tree.h"
#include "json_writer.h"

namespace gltfjson {
namespace tree {
struct Exporter
{
  Writer m_writer;

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
    } else if (auto p = node->Array()) {
      m_writer.array_open();
      for (auto child : *p) {
        Export(child);
      }
      m_writer.array_close();
    } else if (auto p = node->Object()) {
      m_writer.object_open();
      for (auto& kv : *p) {
        m_writer.key(kv.first);
        Export(kv.second);
      }
      m_writer.object_close();
    } else {
      assert(false);
    }
  }
};

}
}
