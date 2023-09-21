project(
    'gltfjson',
    'cpp',
    version: '2.3.0',
    license: 'MIT',
)

gltfjson_dep = declare_dependency(
    include_directories: include_directories('include'),
)

if get_option('executables')
    subdir('src')
endif

if get_option('tests')
    subdir('tests')
endif
