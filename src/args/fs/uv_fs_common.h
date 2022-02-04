#pragma once

#include <php.h>

#define PHP_UV_CHECK_VALID_FD(fd, zstream)                                                  \
	if (fd < 0)                                                                             \
	{                                                                                       \
		php_error_docref(NULL, E_WARNING, "invalid variable passed. can't convert to fd."); \
		PHP_UV_DEINIT_UV(uv);                                                               \
		RETURN_FALSE;                                                                       \
	}                                                                                       \
	if (Z_ISUNDEF(uv->fs_fd))                                                               \
	{                                                                                       \
		ZVAL_COPY(&uv->fs_fd, zstream);                                                     \
	}

#define PHP_UV_FD_TO_ZVAL(zv, fd)                                       \
	{                                                                   \
		php_stream *_stream = php_stream_fopen_from_fd(fd, "w+", NULL); \
		zval *_z = (zv);                                                \
		php_stream_to_zval(_stream, _z);                                \
	}

/* {{{ proto void uv_fs_open(UVLoop $loop, string $path, long $flag, long $mode, callable(long|resource $file_or_result) $callback)*/
PHP_FUNCTION(uv_fs_open);
/* }}} */

/* {{{ proto void uv_fs_read(UVLoop $loop, resource $fd, long $offset, long $length, callable(resource $fd, string|long $read) $callback) */
PHP_FUNCTION(uv_fs_read);
/* }}} */

/* {{{ proto void uv_fs_close(UVLoop $loop, resource $fd[, callable(bool $success) $callback]) */
PHP_FUNCTION(uv_fs_close);
/* }}} */

/* {{{ proto void uv_fs_write(UVLoop $loop, resource $fd, string $buffer[, long $offset = -1[, callable(resource $fd, long $result) $callback]]) */
PHP_FUNCTION(uv_fs_write);
/* }}} */

/* {{{ proto void uv_fs_fsync(UVLoop $loop, resource $fd[, callable(resource $fd, long $result) $callback]) */
PHP_FUNCTION(uv_fs_fsync);
/* }}} */

/* {{{ proto void uv_fs_fdatasync(UVLoop $loop, resource $fd[, callable(resource $fd, long $result) $callback]) */
PHP_FUNCTION(uv_fs_fdatasync);
/* }}} */

/* {{{ proto void uv_fs_ftruncate(UVLoop $loop, resource $fd, long $offset[, callable(resource $fd, long $result) $callback]) */
PHP_FUNCTION(uv_fs_ftruncate);
/* }}} */

/* {{{ proto void uv_fs_mkdir(UVLoop $loop, string $path, long $mode[, callable(long $result) $callback])*/
PHP_FUNCTION(uv_fs_mkdir);
/* }}} */

/* {{{ proto void uv_fs_rmdir(UVLoop $loop, string $path[, callable(long $result) $callback]) */
PHP_FUNCTION(uv_fs_rmdir);
/* }}} */

/* {{{ proto void uv_fs_unlink(UVLoop $loop, string $path[, callable(long $result) $callback]) */
PHP_FUNCTION(uv_fs_unlink);
/* }}} */

/* {{{ proto void uv_fs_rename(UVLoop $loop, string $from, string $to[, callable(long $result) $callback]) */
PHP_FUNCTION(uv_fs_rename);
/* }}} */

/* {{{ proto void uv_fs_utime(UVLoop $loop, string $path, long $utime, long $atime[, callable(long $result) $callback]) */
PHP_FUNCTION(uv_fs_utime);
/* }}} */

/* {{{ proto void uv_fs_futime(UVLoop $loop, zval $fd, long $utime, long $atime[, callable(long $result) $callback]) */
PHP_FUNCTION(uv_fs_futime);
/* }}} */

/* {{{ proto void uv_fs_chmod(UVLoop $loop, string $path, long $mode[, callable(long $result) $callback]) */
PHP_FUNCTION(uv_fs_chmod);
/* }}} */

/* {{{ proto void uv_fs_fchmod(UVLoop $loop, zval $fd, long $mode[, callable(long $result) $callback]) */
PHP_FUNCTION(uv_fs_fchmod);
/* }}} */

/* {{{ proto void uv_fs_chown(UVLoop $loop, string $path, long $uid, long $gid[, callable(long $result) $callback]) */
PHP_FUNCTION(uv_fs_chown);
/* }}} */

/* {{{ proto void uv_fs_fchown(UVLoop $loop, zval $fd, long $uid, $long $gid[, callable(long $result) $callback]) */
PHP_FUNCTION(uv_fs_fchown);
/* }}} */

/* {{{ proto void uv_fs_link(UVLoop $loop, string $from, string $to[, callable(long $result) $callback]) */
PHP_FUNCTION(uv_fs_link);
/* }}} */

/* {{{ proto void uv_fs_symlink(UVLoop $loop, string $from, string $to, long $flags[, callable(long $result) $callback]) */
PHP_FUNCTION(uv_fs_symlink);
/* }}} */

/* {{{ proto void uv_fs_readlink(UVLoop $loop, string $path, callable(string|long $result_or_link_contents) $callback) */
PHP_FUNCTION(uv_fs_readlink);
/* }}} */

/* {{{ proto void uv_fs_stat(UVLoop $loop, string $path, callable(long|array $result_or_stat) $callback) */
PHP_FUNCTION(uv_fs_stat);
/* }}} */

/* {{{ proto void uv_fs_lstat(UVLoop $loop, string $path, callable(long|array $result_or_stat) $callback) */
PHP_FUNCTION(uv_fs_lstat);
/* }}} */

/* {{{ proto void uv_fs_fstat(UVLoop $loop, resource $fd, callable(resource $fd, array $stat) $callback) */
PHP_FUNCTION(uv_fs_fstat);
/* }}} */

/* {{{ proto void uv_fs_readdir(UVLoop $loop, string $path, callable(long|array $result_or_dir_contents) $callback[, long $flags = 0]) */
PHP_FUNCTION(uv_fs_readdir);
/* }}} */

/* {{{ proto void uv_fs_scandir(UVLoop $loop, string $path, callable(long|array $result_or_dir_contents) $callback[, long $flags = 0]) */
PHP_FUNCTION(uv_fs_scandir);
/* }}} */
