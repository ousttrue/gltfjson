project(
    'gltfjson',
    'cpp',
    version: '2.5.0',
    license: 'MIT',
)

if meson.get_compiler('cpp').get_id() == 'gcc'
add_project_arguments(
    '-fpermissive',
    language: 'cpp',
)
endif

gltfjson_dep = declare_dependency(
    include_directories: include_directories('include'),
)

if get_option('executables')
    subdir('src')
endif

if get_option('tests')
    subdir('tests')
endif
