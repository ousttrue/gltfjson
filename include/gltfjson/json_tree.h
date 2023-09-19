#pragma once
#include "json_string_escape.h"
#include <array>
#include <assert.h>
#include <functional>
#include <iomanip>
#include <list>
#include <memory>
#include <ostream>
#include <span>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
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

enum class NodeType : uint8_t
{
  None,
  Null,
  Bool,
  Number,
  String,
  Array,
  Object,
};

struct Node
{
  NodeType Type;
  virtual ~Node() {}
  virtual bool operator==(const Node& rhs) const = 0;
  virtual std::shared_ptr<Node> Clone() const = 0;

protected:
  Node(NodeType t)
    : Type(t)
  {
  }

public:
  template<typename T>
  T* Ptr();

  template<typename T>
  const T* Ptr() const;

  std::shared_ptr<Node> Get(std::u8string_view key) const;
  std::shared_ptr<Node> Remove(std::u8string_view key);

  std::shared_ptr<Node> Get(size_t) const;

  bool IsNull() const;
  std::u8string U8String() const;
  size_t Size() const;
  template<typename T>
  std::shared_ptr<Node> SetProperty(std::u8string_view key, const T& value);
  template<typename T>
  std::shared_ptr<Node> Add(const T& value);
};

using NodePtr = std::shared_ptr<Node>;

struct NullNode : Node
{
  NullNode()
    : Node(NodeType::Null)
  {
  }

  NodePtr Clone() const override { return std::make_shared<NullNode>(); }

  bool operator==(const Node& rhs) const override
  {
    if (dynamic_cast<const NullNode*>(&rhs)) {
      return true;
    }
    return false;
  }
};

struct BoolNode : Node
{
  bool Value = false;

  BoolNode(bool value)
    : Node(NodeType::Bool)
    , Value(value)
  {
  }

  NodePtr Clone() const override { return std::make_shared<BoolNode>(Value); }

  bool operator==(const Node& rhs) const override
  {
    if (auto r = dynamic_cast<const BoolNode*>(&rhs)) {
      return Value == r->Value;
    }
    return false;
  }
};

struct NumberNode : Node
{
  float Value = 0;

  NumberNode(float value)
    : Node(NodeType::Number)
    , Value(value)
  {
  }

  NodePtr Clone() const override { return std::make_shared<NumberNode>(Value); }

  bool operator==(const Node& rhs) const override
  {
    if (auto r = dynamic_cast<const NumberNode*>(&rhs)) {
      return Value == r->Value;
    }
    return false;
  }
};

struct StringNode : Node
{
  std::u8string Value;

  StringNode(const std::u8string& value)
    : Node(NodeType::String)
    , Value(value)
  {
  }

  StringNode(std::u8string_view& value)
    : Node(NodeType::String)
    , Value(value)
  {
  }

  NodePtr Clone() const override { return std::make_shared<StringNode>(Value); }

  bool operator==(const Node& rhs) const override
  {
    if (auto r = dynamic_cast<const StringNode*>(&rhs)) {
      return Value == r->Value;
    }
    return false;
  }
};

using ArrayValue = std::vector<NodePtr>;
struct ArrayNode : Node
{
  ArrayValue Value;

  ArrayNode(const ArrayValue& value)
    : Node(NodeType::Array)
    , Value(value)
  {
  }

  NodePtr Clone() const override
  {
    auto a = std::make_shared<ArrayNode>(ArrayValue{});
    // deep copy
    for (auto e : Value) {
      a->Value.push_back(e->Clone());
    }
    return a;
  }

  bool operator==(const Node& rhs) const override
  {
    auto r = dynamic_cast<const ArrayNode*>(&rhs);
    if (!r) {
      return false;
    }
    auto& ra = r->Value;
    if (Value.size() != ra.size()) {
      return false;
    }
    for (int i = 0; i < Value.size(); ++i) {
      if (Value[i] != ra[i]) {
        return false;
      }
    }
    return true;
  }
};

using ObjectValue = std::unordered_map<std::u8string, NodePtr>;
struct ObjectNode : Node
{
  ObjectValue Value;

  ObjectNode(const ObjectValue& value)
    : Node(NodeType::Object)
    , Value(value)
  {
  }

  NodePtr Clone() const override
  {
    auto o = std::make_shared<ObjectNode>(ObjectValue{});
    // deep copy
    for (auto& [k, v] : Value) {
      o->Value.insert({ k, v->Clone() });
    }
    return o;
  }

  bool operator==(const Node& rhs) const override
  {
    auto r = dynamic_cast<const ObjectNode*>(&rhs);
    if (!r) {
      return false;
    }
    auto& ra = r->Value;
    if (Value.size() != ra.size()) {
      return false;
    }
    for (auto l = Value.begin(); l != Value.end(); ++l) {
      auto found = ra.find(l->first);
      if (found == ra.end()) {
        return false;
      }
      if (l->second) {
        if (found->second) {
          if (*l->second != *found->second) {
            return false;
          }
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
  }
};

inline std::shared_ptr<NullNode>
NewNode()
{
  return std::make_shared<NullNode>();
}

struct NullValue
{};

inline std::shared_ptr<NullNode>
NewNode(NullValue)
{
  return std::make_shared<NullNode>();
}
inline std::shared_ptr<BoolNode>
NewNode(bool value)
{
  return std::make_shared<BoolNode>(value);
}
inline std::shared_ptr<NumberNode>
NewNode(float value)
{
  return std::make_shared<NumberNode>(value);
}
inline std::shared_ptr<StringNode>
NewNode(const char8_t* value)
{
  return std::make_shared<StringNode>(value);
}
inline std::shared_ptr<StringNode>
NewNode(const std::u8string& value)
{
  return std::make_shared<StringNode>(value);
}
inline std::shared_ptr<StringNode>
NewNode(std::u8string_view value)
{
  return std::make_shared<StringNode>(value);
}
inline std::shared_ptr<ArrayNode>
NewNode(const ArrayValue& value)
{
  return std::make_shared<ArrayNode>(value);
}
inline std::shared_ptr<ObjectNode>
NewNode(const ObjectValue& value)
{
  return std::make_shared<ObjectNode>(value);
}
inline NodePtr
NewNode(const std::shared_ptr<Node>& node)
{
  return node;
}

template<>
inline bool*
Node::Ptr<bool>()
{
  if (auto n = dynamic_cast<BoolNode*>(this)) {
    return &n->Value;
  }
  return {};
}
template<>
inline const bool*
Node::Ptr<bool>() const
{
  if (auto n = dynamic_cast<const BoolNode*>(this)) {
    return &n->Value;
  }
  return {};
}
template<>
inline float*
Node::Ptr<float>()
{
  if (auto n = dynamic_cast<NumberNode*>(this)) {
    return &n->Value;
  }
  return {};
}
template<>
inline const float*
Node::Ptr<float>() const
{
  if (auto n = dynamic_cast<const NumberNode*>(this)) {
    return &n->Value;
  }
  return {};
}
template<>
inline std::u8string*
Node::Ptr<std::u8string>()
{
  if (auto n = dynamic_cast<StringNode*>(this)) {
    return &n->Value;
  }
  return {};
}
template<>
inline const std::u8string*
Node::Ptr<std::u8string>() const
{
  if (auto n = dynamic_cast<const StringNode*>(this)) {
    return &n->Value;
  }
  return {};
}
template<>
inline ArrayValue*
Node::Ptr<ArrayValue>()
{
  if (auto n = dynamic_cast<ArrayNode*>(this)) {
    return &n->Value;
  }
  return {};
}
template<>
inline const ArrayValue*
Node::Ptr<ArrayValue>() const
{
  if (auto n = dynamic_cast<const ArrayNode*>(this)) {
    return &n->Value;
  }
  return {};
}
template<>
inline ObjectValue*
Node::Ptr<ObjectValue>()
{
  if (auto n = dynamic_cast<ObjectNode*>(this)) {
    return &n->Value;
  }
  return {};
}
template<>
inline const ObjectValue*
Node::Ptr<ObjectValue>() const
{
  if (auto n = dynamic_cast<const ObjectNode*>(this)) {
    return &n->Value;
  }
  return {};
}

inline bool
Node::IsNull() const
{
  if (dynamic_cast<const NullNode*>(this)) {
    return true;
  }
  return false;
}

inline std::u8string
Node::U8String() const
{
  if (auto s = dynamic_cast<const StringNode*>(this)) {
    return s->Value;
  }
  return {};
}

inline size_t
Node::Size() const
{
  if (auto a = dynamic_cast<const ArrayNode*>(this)) {
    return a->Value.size();
  } else if (auto o = dynamic_cast<const ObjectNode*>(this)) {
    return o->Value.size();
  }
  return 0;
}

inline std::shared_ptr<Node>
Node::Get(std::u8string_view key) const
{
  if (auto o = dynamic_cast<const ObjectNode*>(this)) {
    auto found = o->Value.find(std::u8string{ key.begin(), key.end() });
    if (found != o->Value.end()) {
      return found->second;
    }
  }
  return {};
}

inline std::shared_ptr<Node>
Node::Remove(std::u8string_view key)
{
  if (auto o = dynamic_cast<ObjectNode*>(this)) {
    auto found = o->Value.find(std::u8string{ key.begin(), key.end() });
    if (found != o->Value.end()) {
      auto removed = found->second;
      o->Value.erase(found);
      return removed;
    }
  }
  return {};
}

inline std::shared_ptr<Node>
Node::Get(size_t index) const
{
  if (auto a = dynamic_cast<const ArrayNode*>(this)) {
    if (index < a->Value.size()) {
      return a->Value[index];
    }
  }
  return {};
}

template<typename T>
std::shared_ptr<Node>
Node::SetProperty(std::u8string_view key, const T& value)
{
  if (auto o = dynamic_cast<ObjectNode*>(this)) {
    auto n = NewNode(value);
    o->Value[{ key.begin(), key.end() }] = n;
    return n;
  }
  return {};
}
template<>
inline std::shared_ptr<Node>
Node::SetProperty<std::array<float, 3>>(std::u8string_view key,
                                        const std::array<float, 3>& value)
{
  if (auto o = dynamic_cast<ObjectNode*>(this)) {
    auto n = NewNode(ArrayValue{
      NewNode(value[0]),
      NewNode(value[1]),
      NewNode(value[2]),
    });
    o->Value.insert({ { key.begin(), key.end() }, n });
    return n;
  }
  return {};
}
template<>
inline std::shared_ptr<Node>
Node::SetProperty<std::array<float, 4>>(std::u8string_view key,
                                        const std::array<float, 4>& value)
{
  if (auto o = dynamic_cast<ObjectNode*>(this)) {
    auto n = NewNode(ArrayValue{
      NewNode(value[0]),
      NewNode(value[1]),
      NewNode(value[2]),
      NewNode(value[3]),
    });
    o->Value.insert({ { key.begin(), key.end() }, n });
    return n;
  }
  return {};
}
template<typename T>
std::shared_ptr<Node>
Node::Add(const T& value)
{
  if (auto a = dynamic_cast<ArrayNode*>(this)) {
    auto n = NewNode(value);
    a->Value.push_back(n);
    return n;
  }
  return {};
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
    if (auto object = std::dynamic_pointer_cast<ObjectNode>(item)) {
      for (auto [k, v] : object->Value) {
        jsonpath += k;
        TraverseJsonRecursive(enter, leave, v, jsonpath);
        jsonpath.resize(size);
      }
    } else if (auto array = std::dynamic_pointer_cast<ArrayNode>(item)) {
      int i = 0;
      for (auto& v : array->Value) {
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
    if (auto a = std::dynamic_pointer_cast<tree::ArrayNode>(json)) {
      if (a->Value.size() == 3) {
        if (auto a0 = a->Value[0]) {
          if (auto p0 = a0->Ptr<float>()) {
            if (auto a1 = a->Value[1]) {
              if (auto p1 = a1->Ptr<float>()) {
                if (auto a2 = a->Value[2]) {
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
    if (auto a = std::dynamic_pointer_cast<tree::ArrayNode>(json)) {
      if (a->Value.size() == 4) {
        if (auto a0 = a->Value[0]) {
          if (auto p0 = a0->Ptr<float>()) {
            if (auto a1 = a->Value[1]) {
              if (auto p1 = a1->Ptr<float>()) {
                if (auto a2 = a->Value[2]) {
                  if (auto p2 = a2->Ptr<float>()) {
                    if (auto a3 = a->Value[3]) {
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
