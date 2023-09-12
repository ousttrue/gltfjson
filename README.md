# gltfjson

A json manipulation library for glTF.
It focuses on usability of glTF editing, not on performance.

msvc19, clang-16 OK.

```
> meson setup builddir -Dcpp_std=c++20 --native-file zig.ini -Dexecutables=true -Dtests=true
```

## JSON DOM

Simple inheritance.

```c++
struct Node
{
  virtual ~Node() {}
  virtual bool operator==(const Node& rhs) const = 0;
  template<typename T>
  T* Ptr();
  template<typename T>
  const T* Ptr() const;
  std::shared_ptr<Node> Get(std::u8string_view key) const;
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

struct NullNode : Node;
struct BoolNode : Node;
struct NumberNode : Node;
struct StringNode : Node;
using ArrayValue = std::vector<NodePtr>;
struct ArrayNode : Node;
using ObjectValue = std::unordered_map<std::u8string, NodePtr>;
struct ObjectNode : Node;
```

## Typed wrapper

```c++
  gltfjson::tree::Parser parser(GLTF_JSON_STRING);
  auto result = parser.Parse();

  // JSON wrapper for static typing
  gltfjson::typing::Root gltf(result);

  // asset
  EXPECT_EQ(gltf.Asset()->Version(), u8"2.0");
```

