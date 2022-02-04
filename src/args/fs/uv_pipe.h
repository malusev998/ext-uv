#pragma once

#include <php.h>

/* {{{ proto UVPipe uv_pipe_init([UVLoop $loop = uv_default_loop(), bool $ipc = false]) */
PHP_FUNCTION(uv_pipe_init);
/* }}} */

/* {{{ proto long|false uv_pipe_open(UVPipe $handle, resource|long $pipe) */
PHP_FUNCTION(uv_pipe_open);
/* }}} */

/* {{{ proto long uv_pipe_bind(UVPipe $handle, string $name) */
PHP_FUNCTION(uv_pipe_bind);
/* }}} */

/* {{{ proto void uv_pipe_connect(UVPipe $handle, string $path, callable(UVPipe $handle, long $status) $callback) */
PHP_FUNCTION(uv_pipe_connect);
/* }}} */

/* {{{ proto void uv_pipe_pending_instances(UVPipe $handle, long $count) */
PHP_FUNCTION(uv_pipe_pending_instances);
/* }}} */

/* {{{ proto void uv_pipe_pending_count(UVPipe $handle) */
PHP_FUNCTION(uv_pipe_pending_count);
/* }}} */

/* {{{ proto void uv_pipe_pending_type(UVPipe $handle) */
PHP_FUNCTION(uv_pipe_pending_type);
/* }}} */
