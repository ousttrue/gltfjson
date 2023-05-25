#pragma once
#include <assert.h>
#include <charconv>
#include <expected>
#include <functional>
#include <list>
#include <memory>
#include <optional>
#include <span>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

namespace gltfjson {
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
};

using EnterJson =
  std::function<bool(const NodePtr&, std::u8string_view jsonpath)>;
using LeaveJson = std::function<void()>;
inline void
TraverseJson(const EnterJson& enter,
             const LeaveJson& leave,
             const NodePtr& item,
             std::u8string& jsonpath)
{
  const auto DELIMITER = u8'/';
  if (enter(item, jsonpath)) {
    if (auto object = item->Object()) {
      auto size = jsonpath.size();
      for (auto [k, v] : *object) {
        jsonpath.push_back(DELIMITER);
        jsonpath += k;
        TraverseJson(enter, leave, v, jsonpath);
        jsonpath.resize(size);
      }
    } else if (auto array = item->Array()) {
      auto size = jsonpath.size();
      static std::stringstream ss;
      ss.str("");
      int i = 0;
      for (auto& v : *array) {
        ss << (i++);
        auto str = ss.str();
        jsonpath.push_back(DELIMITER);
        jsonpath +=
          std::u8string_view{ (const char8_t*)str.c_str(), str.size() };
        TraverseJson(enter, leave, v, jsonpath);
        jsonpath.resize(size);
      }
    }
    if (leave) {
      leave();
    }
  }
}

}
}
