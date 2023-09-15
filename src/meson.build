ftxui_dep = dependency('ftxui-component')
cxxopts_dep = dependency('cxxopts')

executable(
    'gltfjson',
    [
        'main.cpp',
    ],
    install: true,
    dependencies: [
        gltfjson_dep,
        ftxui_dep,
        cxxopts_dep,
    ],
)
