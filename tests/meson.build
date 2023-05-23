gtest_main_dep = dependency('gtest_main')
executable(
    'tests',
    [
        'test_json.cpp',
        'test_gltf.cpp',
        'test_base64.cpp',
        'test_tree.cpp',
    ],
    install: true,
    dependencies: [gtest_main_dep, gltfjson_dep],
)
