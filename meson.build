project(
    'gltfjson',
    'cpp',
    version: '1.8.0',
    license: 'MIT',
)

gltfjson_dep = declare_dependency(
    include_directories: include_directories('include'),
)

if get_option('tests')
    subdir('tests')
endif
