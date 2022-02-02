project('php-uv', 'c', version: '0.3.0', default_options: [
  'b_lundef=false',
  'b_colorout=always',
  'b_pie=true',
  'c_std=c17',
  'cpp_std=c++20'
])

cmake = import('cmake')

cc = meson.get_compiler('c')
cc_clang = cc.get_id().contains('clang')
cc_gnu = cc.get_id().contains('gcc')

linux = host_machine.system() == 'linux'
apple = host_machine.system() == 'darwin'


cm_libuv_opt = cmake.subproject_options()

cm_libuv_opt.add_cmake_defines({
  'LIBUV_BUILD_TESTS': 'OFF',
  'LIBUV_BUILD_BENCH': 'OFF',
})

cm_libuv = cmake.subproject('libuv', options: cm_libuv_opt)

php_include_dir = run_command('php-config', '--include-dir', check: true).stdout().strip()
# php_lib = run_command('php-config', '--ldflags', check: true).stdout().strip()

# ldflags = php_lib.split(' ')

php_include_dir_all = include_directories(php_include_dir)
php_include_dir_main = include_directories(php_include_dir + '/main')
php_include_dir_Zend = include_directories(php_include_dir + '/Zend')
php_include_dir_TSRM = include_directories(php_include_dir + '/TSRM')
php_include_dir_ext = include_directories(php_include_dir + '/ext')

incdir = [
  php_include_dir_all,
  php_include_dir_main,
  php_include_dir_Zend,
  php_include_dir_TSRM,
  php_include_dir_ext
]


ROOT_SRC = [
    './php_uv.c',
    './uv.c',
]

have_libuv = '1'

conf = configuration_data({
    'HAVE_INTTYPES_H': '1',
    'HAVE_STDINT_H': '1',
    'HAVE_STDIO_H': '1',
    'HAVE_STDLIB_H': '1',
    'HAVE_STRINGS_H': '1',
    'HAVE_STRING_H': '1',
    'HAVE_SYS_STAT_H': '1',
    'HAVE_SYS_TYPES_H': '1',
    'HAVE_UNISTD_H': '1',
})

debug = get_option('debug')

if debug == true
    conf.set('PHP_UV_DEBUG', '1')
endif

if have_libuv == '1'
    conf.set('HAVE_LIBUV', '1')
endif

configure_file(
    output : 'config.h',
    configuration : conf
)


SOURCES = ROOT_SRC

libuv_dep = cm_libuv.dependency('uv_a')

library('php_uv',
  sources: SOURCES,
  include_directories: incdir,
  name_prefix: '',
  dependencies: [
    libuv_dep
  ],
  # c_args: ldflags
)
