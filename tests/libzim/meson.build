project('test_libzim', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3'])

libzim_deps = dependency('libzim')

exe = executable(
  'test_libzim.out', 
  'test_libzim.cpp',
  dependencies: libzim_deps,
  install : true
)

test('basic', exe)
