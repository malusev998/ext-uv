#pragma once

#include <php.h>

/* {{{ proto UVProcess|long uv_spawn(UVLoop $loop, string $command, array $args, array $stdio, string $cwd, array $env, callable(UVProcess $process, long $exit_status, long $term_signal) $callback[, long $flags = 0, array $options = []]) */
PHP_FUNCTION(uv_spawn);
/* }}} */

/* {{{ proto void uv_process_kill(UVProcess $handle, long $signal) */
PHP_FUNCTION(uv_process_kill);
/* }}} */

/* {{{ proto void uv_process_get_pid(UVProcess $handle) */
PHP_FUNCTION(uv_process_get_pid);
/* }}} */

/* {{{ proto void uv_kill(long $pid, long $signal) */
PHP_FUNCTION(uv_kill);
/* }}} */
