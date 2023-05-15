gtest_main_dep = dependency('gtest_main')
executable(
    'tests',
    [
        'test_json.cpp',
        'test_gltf.cpp',
    ],
    install: true,
    dependencies: [gtest_main_dep, gltfjson_dep],
)
