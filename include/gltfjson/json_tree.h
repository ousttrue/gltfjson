#pragma once
#include <assert.h>
#include <charconv>
#include <expected>
#include <functional>
#include <list>
#include <memory>
#include <optional>
#include <ostream>
#include <span>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

namespace gltfjson {
namespace tree {

inline std::string_view
from_u8(std::u8string_view src)
{
  return { (const char*)src.data(), (const char*)src.data() + src.size() };
}
inline std::u8string_view
to_u8(std::string_view src)
{
  return { (const char8_t*)src.data(),
           (const char8_t*)src.data() + src.size() };
}

struct Node;
using NodePtr = std::shared_ptr<Node>;
using ArrayValue = std::vector<NodePtr>;
using ObjectValue = std::unordered_map<std::u8string, NodePtr>;
struct Node
{
  std::
    variant<std::monostate, bool, float, std::u8string, ArrayValue, ObjectValue>
      Var;

  Node() {}

  Node(bool b)
    : Var(b)
  {
  }

  Node(float n)
    : Var(n)
  {
  }

  Node(std::u8string_view str)
    : Var(std::u8string{ str.begin(), str.end() })
  {
  }

  Node(const ArrayValue& a)
    : Var(a)
  {
  }

  Node(const ObjectValue& o)
    : Var(o)
  {
  }

  template<typename T>
  const T* Ptr() const
  {
    if (std::holds_alternative<T>(Var)) {
      return &std::get<T>(Var);
    } else {
      return nullptr;
    }
  }
  template<typename T>
  T* Ptr()
  {
    if (std::holds_alternative<T>(Var)) {
      return &std::get<T>(Var);
    } else {
      return nullptr;
    }
  }

  bool IsNull() const { return std::holds_alternative<std::monostate>(Var); }

  std::u8string U8String() const
  {
    if (auto str = Ptr<std::u8string>()) {
      return *str;
    } else {
      return u8"";
    }
  }

  // array
  const ArrayValue* Array() const { return Ptr<ArrayValue>(); }

  // array
  ArrayValue* Array() { return Ptr<ArrayValue>(); }

  // array member
  NodePtr Get(size_t index) const
  {
    if (auto array = Array()) {
      return (*array)[index];
    }

    return nullptr;
  }

  // object
  const ObjectValue* Object() const { return Ptr<ObjectValue>(); }

  // object
  ObjectValue* Object() { return Ptr<ObjectValue>(); }

  // object member
  NodePtr Get(std::u8string_view target) const
  {
    if (auto object = Object()) {
      auto found = object->find({ target.begin(), target.end() });
      if (found != object->end()) {
        return found->second;
      }
    }

    return nullptr;
  }

  void Remove(std::u8string_view target)
  {
    if (auto object = Object()) {
      object->erase({ target.begin(), target.end() });
    }
  }

  template<typename T>
  NodePtr Add(std::u8string_view target, const T& value)
  {
    auto object = Object();
    if (!object) {
      return nullptr;
    }

    auto p = Get(target);
    if (!p) {
      p = std::make_shared<Node>();
      object->insert({ { target.begin(), target.end() }, p });
    }
    p->Var = value;

    return p;
  }

  // array or object size
  size_t Size() const
  {
    if (auto array = Ptr<ArrayValue>()) {
      return array->size();
    } else if (auto object = Ptr<ObjectValue>()) {
      return object->size();
    } else {
      return 0;
    }
  }

  template<size_t N>
  void Set(const std::array<float, N>& values)
  {
    auto p = Array();
    if (!p) {
      Var = ArrayValue{};
      p = Array();
    }
    for (int i = 0; i < N; ++i) {
      if (i >= p->size()) {
        p->push_back(std::make_shared<Node>());
      }
      (*p)[i]->Var = values[i];
    }
  }
};

inline std::ostream&
operator<<(std::ostream& os, const Node& node)
{
  struct Visitor
  {
    std::ostream& m_os;
    Visitor(std::ostream& os)
      : m_os(os)
    {
    }
    void operator()(std::monostate) { m_os << "null"; }
    void operator()(bool value)
    {
      if (value) {
        m_os << "true";
      } else {
        m_os << "false";
      }
    }
    void operator()(float value) { m_os << value; }
    void operator()(const std::u8string& value)
    {
      m_os << '"' << from_u8(value) << '"';
    }
    void operator()(const ArrayValue& value)
    {
      m_os << '[' << value.size() << ']';
    }
    void operator()(const ObjectValue& value)
    {
      m_os << '{' << value.size() << '}';
    }
  };
  std::visit(Visitor(os), node.Var);
  return os;
}

inline void
AddDelimiter(std::u8string& jsonpath)
{
  const auto DELIMITER = u8'/';
  if (jsonpath != u8"/") {
    jsonpath.push_back(DELIMITER);
  }
}

inline void
concat_int(std::u8string& str, int i)
{
  if (i >= 10) {
    concat_int(str, i / 10);
  }
  auto n = i % 10;
  str.push_back(u8'0' + n);
}

using EnterJson =
  std::function<bool(const NodePtr&, std::u8string_view jsonpath)>;
using LeaveJson = std::function<void()>;
inline void
TraverseJsonRecursive(const EnterJson& enter,
                      const LeaveJson& leave,
                      const NodePtr& item,
                      std::u8string& jsonpath)
{
  if (enter(item, jsonpath)) {
    AddDelimiter(jsonpath);
    auto size = jsonpath.size();
    if (auto object = item->Object()) {
      for (auto [k, v] : *object) {
        jsonpath += k;
        TraverseJsonRecursive(enter, leave, v, jsonpath);
        jsonpath.resize(size);
      }
    } else if (auto array = item->Array()) {
      int i = 0;
      for (auto& v : *array) {
        concat_int(jsonpath, i++);
        TraverseJsonRecursive(enter, leave, v, jsonpath);
        jsonpath.resize(size);
      }
    }
    if (leave) {
      leave();
    }
  }
}

inline void
TraverseJson(const EnterJson& enter,
             const LeaveJson& leave,
             const NodePtr& item)
{
  std::u8string buf = u8"/";
  TraverseJsonRecursive(enter, leave, item, buf);
}

inline NodePtr
FindJsonPath(const NodePtr& root, std::u8string_view jsonpath)
{
  NodePtr found;
  auto enter = [&found, jsonpath](const NodePtr& node,
                                  std::u8string_view current) {
    if (current == jsonpath) {
      found = node;
      return false;
    }

    return true;
  };

  TraverseJson(enter, {}, root);

  return found;
}
}
}
