#pragma once

#include <php.h>

/* {{{ proto UVFsPoll uv_fs_poll_init([UVLoop $loop = uv_default_loop()]) */
PHP_FUNCTION(uv_fs_poll_init);
/* }}} */

/* {{{ proto uv uv_fs_poll_start(UVFsPoll $handle, callable(UVFsPoll $handle, long $status, array $prev_stat, array $cur_stat) $callback, string $path, long $interval) */
PHP_FUNCTION(uv_fs_poll_start);
/* }}} */

/* {{{ proto void uv_fs_poll_stop(UVFsPoll $poll) */
PHP_FUNCTION(uv_fs_poll_stop);
/* }}} */
