# gltfjson

A json manipulation library for glTF.
It focuses on usability of glTF editing, not on performance.

- `c++20` required.
- `c++21(std::expected)` removed

msvc19, clang-16 OK.

```
> meson setup builddir -Dcpp_std=c++20 --native-file zig.ini -Dexecutables=true -Dtests=true
```

## JSON DOM

structures.

```c++
struct Node;
using NodePtr = std::shared_ptr<Node>;
using ArrayValue = std::vector<NodePtr>;
using ObjectValue = std::unordered_map<std::u8string, NodePtr>;
struct Node
{
  std::variant<std::monostate, bool, float, std::u8string, ArrayValue, ObjectValue>
    Var;

  // Get pointer for payload
  template<typename T>
  const T* Ptr() const
  {
    if (std::holds_alternative<T>(Var)) {
      return &std::get<T>(Var);
    } else {
      return nullptr;
    }
  }
 };
```

```c++
#include <gltfjson/json_tree.h>

int main()
{
  auto SRC = u8"{\"key\": {\"key2\": 2}}";
  gltfjson::tree::Parser parser(SRC);
  auto result = parser.Parse();
  if (result) {
    // get json object property
    auto inner = result->Get(u8"key");
    // get pointer for leaf value
    EXPECT_EQ(*inner->Get(u8"key2")->Ptr<float>(), 2);
  }

  return 0;
}
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
