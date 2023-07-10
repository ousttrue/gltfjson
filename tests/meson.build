gtest_main_dep = dependency('gtest_main')
executable(
    'tests',
    [
        'test_json.cpp',
        'test_json_string.cpp',
        'test_base64.cpp',
        'test_tree.cpp',
        'test_tree_string.cpp',
        'test_tree_gltf.cpp',
        'test_jsonpath.cpp',
        'gltf_samples.cpp',
        'glb_export.cpp',
        'json.cpp',
        'write_read.cpp',
        'test_vrm0.cpp',
        'test_vrm1.cpp',
    ],
    install: true,
    dependencies: [gtest_main_dep, gltfjson_dep],
)
