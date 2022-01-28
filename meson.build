project('php-uv', 'c', version: '0.3.0', default_options: [
  'b_lundef=false',
  'b_colorout=always',
  'b_pie=true',
  'c_std=c17',
  'cpp_std=c++20'
])

cc = meson.get_compiler('c')
cc_clang = cc.get_id().contains('clang')
cc_gnu = cc.get_id().contains('gcc')

linux = host_machine.system() == 'linux'
apple = host_machine.system() == 'darwin'

libuv_cargs = [
    '-D_FILE_OFFSET_BITS=64',
    '-D_LARGEFILE_SOURCE',
]

cc_other_cargs_all = [
  '-fno-strict-aliasing',   # f_strict_aliasing
]

libuv_deps = [
  dependency('threads'),
]

foreach flag : cc_other_cargs_all
  if cc.has_argument(flag)
    libuv_cargs += flag
  endif
endforeach

libuv_libs = []

libuv_src = [
    'libuv/src/fs-poll.c',
    'libuv/src/idna.c',
    'libuv/src/inet.c',
    'libuv/src/random.c',
    'libuv/src/strscpy.c',
    'libuv/src/threadpool.c',
    'libuv/src/timer.c',
    'libuv/src/uv-data-getter-setters.c',
    'libuv/src/uv-common.c',
    'libuv/src/version.c',
]

if apple or linux
    libuv_src += [
        'libuv/src/unix/async.c',
        'libuv/src/unix/core.c',
        'libuv/src/unix/dl.c',
        'libuv/src/unix/fs.c',
        'libuv/src/unix/getaddrinfo.c',
        'libuv/src/unix/getnameinfo.c',
        'libuv/src/unix/loop-watcher.c',
        'libuv/src/unix/loop.c',
        'libuv/src/unix/pipe.c',
        'libuv/src/unix/poll.c',
        'libuv/src/unix/process.c',
        'libuv/src/unix/random-devurandom.c',
        'libuv/src/unix/signal.c',
        'libuv/src/unix/stream.c',
        'libuv/src/unix/tcp.c',
        'libuv/src/unix/thread.c',
        'libuv/src/unix/tty.c',
        'libuv/src/unix/udp.c',
        'libuv/src/unix/proctitle.c'
    ]
endif


if apple
    libuv_src += [
        'libuv/src/unix/bsd-ifaddrs.c',
        'libuv/src/unix/kqueue.c',
        'libuv/src/unix/random-getentropy.c',
        'libuv/src/unix/darwin-proctitle.c',
        'libuv/src/unix/darwin.c',
        'libuv/src/unix/fsevents.c',
    ]

    libuv_cargs += [
        '-D_DARWIN_UNLIMITED_SELECT=1',
        '-D_DARWIN_USE_64_BIT_INODE=1',
    ]
endif


if linux
  libuv_cargs += [
    '-D_GNU_SOURCE',
    '-D_POSIX_C_SOURCE=200112',
  ]
  libuv_libs += ['dl', 'rt']

  libuv_src += [
    'libuv/src/unix/linux-core.c',
    'libuv/src/unix/linux-inotify.c',
    'libuv/src/unix/linux-syscalls.c',
    'libuv/src/unix/procfs-exepath.c',
    'libuv/src/unix/random-getrandom.c',
    'libuv/src/unix/random-sysctl-linux.c',
    'libuv/src/unix/epoll.c',
  ]

endif

foreach lib : libuv_libs
  libuv_deps += cc.find_library(lib, required: true)
endforeach

libuv_public_inc = include_directories('libuv/include')
libuv_private_inc = include_directories('libuv/src')
libuv_inc = [libuv_public_inc, libuv_private_inc]

libuv = static_library('uv',
  libuv_src,
  c_args: libuv_cargs,
  dependencies: libuv_deps,
  include_directories: libuv_inc,
)

libuv_dep = declare_dependency(
  dependencies: libuv_deps,
  link_with: libuv,
  include_directories: libuv_public_inc,
)

php_include_dir = run_command('php-config', '--include-dir', check: true).stdout().strip()
# php_lib = run_command('php-config', '--ldflags', check: true).stdout().strip()

# ldflags = php_lib.split(' ')

php_include_dir_all = include_directories(php_include_dir)
php_include_dir_main = include_directories(php_include_dir + '/main')
php_include_dir_Zend = include_directories(php_include_dir + '/Zend')
php_include_dir_TSRM = include_directories(php_include_dir + '/TSRM')
php_include_dir_ext = include_directories(php_include_dir + '/ext')

incdir = [
  libuv_public_inc,
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

library('php_uv',
  sources: SOURCES,
  include_directories: incdir,
  name_prefix: '',
  dependencies: [
    libuv_dep
  ],
  # c_args: ldflags
)
