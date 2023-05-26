gtest_main_dep = dependency('gtest_main')
executable(
    'tests',
    [
        'json.cpp',
        'test_json.cpp',
        'test_gltf.cpp',
        'test_base64.cpp',
        'test_tree.cpp',
        'test_tree_gltf.cpp',
        'test_jsonpath.cpp',
        'gltf_samples.cpp',
        'glb_export.cpp',
    ],
    install: true,
    dependencies: [gtest_main_dep, gltfjson_dep],
)
