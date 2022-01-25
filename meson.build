project('php-uv', 'c', version: '0.3.0')

php_include_dir = run_command('php-config', '--include-dir', check: true).stdout().strip()

message(php_include_dir)

incdir = include_directories(
    'include',
    php_include_dir,
    php_include_dir + '/main',
    php_include_dir + '/Zend',
    php_include_dir + '/TSRM',
    php_include_dir + '/ext',
)

LIBUV_LOCKS_SRC = [
    './src/locks/locks.c',
    './src/locks/mutex.c',
    './src/locks/php_lock.c',
    './src/locks/rwlock.c',
    './src/locks/semaphore.c',
]

LIBUV_FS_SRC = [
    './src/parsing.c',
    './src/register_class.c',
    './src/fs/fd.c',
]

ROOT_SRC = [
    './php_uv.c',
    './uv.c',
]

have_libuv = '0'

SOURCES = LIBUV_FS_SRC + LIBUV_LOCKS_SRC + ROOT_SRC

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


library('php_uv', sources: SOURCES, include_directories: incdir, name_prefix: '')
