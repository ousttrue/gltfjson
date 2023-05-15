project('gltfjson', 'cpp')

gltfjson_dep = declare_dependency(
    include_directories: include_directories('include'),
)

if get_option('tests')
    subdir('tests')
endif
