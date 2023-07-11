#pragma once
#include "json_string_escape.h"
#include <array>
#include <assert.h>
#include <charconv>
#include <expected>
#include <functional>
#include <iomanip>
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

inline float
deref_or(const float* p, float defaultValue)
{
  return p ? *p : defaultValue;
}

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

namespace tree {

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

  bool operator==(const Node& dst) const
  {
    if (auto array = Array()) {
      if (auto dstArray = dst.Array()) {
        if (array->size() == dstArray->size()) {
          for (int i = 0; i < array->size(); ++i) {
            auto lhs = (*array)[i];
            auto rhs = (*dstArray)[i];
            if (lhs) {
              if (rhs) {
                if (*lhs == *rhs) {
                  continue;
                }
                return false;
              } else {
                return false;
              }
            } else {
              if (rhs) {
                return false;
              }
            }
          }
          return true;
        } else {
          return false;
        }
      } else {
        return false;
      }
    } else if (auto object = Object()) {
      if (auto dstObject = dst.Object()) {
        if (object->size() == dstObject->size()) {
          for (auto [k, v] : *object) {
            auto found = dstObject->find(k);
            if (found == dstObject->end()) {
              return false;
            }
            if (v) {
              if (found->second) {
                if (*v == *found->second) {
                  continue;
                }
                return false;
              } else {
                return false;
              }
            } else {
              if (found->second) {
                return false;
              }
            }
          }
          return true;
        } else {
          return false;
        }
      } else {
        return false;
      }
    } else {
      return Var == dst.Var;
    }
  }

  template<typename T>
  static NodePtr Create(const T& t)
  {
    auto ptr = std::make_shared<Node>();
    ptr->Var = t;
    return ptr;
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
    p->Set(value);

    return p;
  }

  template<typename T>
  NodePtr Add(const T& value)
  {
    auto array = Array();
    if (!array) {
      return nullptr;
    }

    array->push_back(Create(value));

    return array->back();
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

  void Set(bool b) { Var = b; }
  void Set(float f) { Var = f; }
  void Set(const std::u8string& s) { Var = s; }
  void Set(const char8_t* s) { Var = std::u8string(s); }
  void Set(const ArrayValue& a) { Var = a; }
  void Set(const ObjectValue& o) { Var = o; }

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

  void Copy(const std::shared_ptr<Node>& dst) {}
};

// inline std::ostream&
// operator<<(std::ostream& os, const Node& node)
// {
//   struct Visitor
//   {
//     std::ostream& m_os;
//     Visitor(std::ostream& os)
//       : m_os(os)
//     {
//     }
//     void operator()(std::monostate) { m_os << "null"; }
//     void operator()(bool value)
//     {
//       if (value) {
//         m_os << "true";
//       } else {
//         m_os << "false";
//       }
//     }
//     void operator()(float value) { m_os << std::setprecision(9) << value; }
//     void operator()(const std::u8string& value)
//     {
//       m_os << '"' << from_u8(value) << '"';
//     }
//     void operator()(const ArrayValue& value)
//     {
//       m_os << '[' << value.size() << ']';
//     }
//     void operator()(const ObjectValue& value)
//     {
//       m_os << '{' << value.size() << '}';
//     }
//   };
//   std::visit(Visitor(os), node.Var);
//   return os;
// }

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

} // namespace

inline std::array<float, 3>
Vec3(const tree::NodePtr& json, const std::array<float, 3>& defaultValue)
{
  if (json) {
    if (auto a = json->Array()) {
      if (a->size() == 3) {
        if (auto a0 = (*a)[0]) {
          if (auto p0 = a0->Ptr<float>()) {
            if (auto a1 = (*a)[1]) {
              if (auto p1 = a1->Ptr<float>()) {
                if (auto a2 = (*a)[2]) {
                  if (auto p2 = a2->Ptr<float>()) {
                    return { *p0, *p1, *p2 };
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  return defaultValue;
}

inline std::array<float, 4>
Vec4(const tree::NodePtr& json, const std::array<float, 4>& defaultValue)
{
  if (json) {
    if (auto a = json->Array()) {
      if (a->size() == 4) {
        if (auto a0 = (*a)[0]) {
          if (auto p0 = a0->Ptr<float>()) {
            if (auto a1 = (*a)[1]) {
              if (auto p1 = a1->Ptr<float>()) {
                if (auto a2 = (*a)[2]) {
                  if (auto p2 = a2->Ptr<float>()) {
                    if (auto a3 = (*a)[3]) {
                      if (auto p3 = a3->Ptr<float>()) {
                        return { *p0, *p1, *p2, *p3 };
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  return defaultValue;
}

} // namespace
