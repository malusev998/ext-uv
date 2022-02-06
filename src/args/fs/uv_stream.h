#pragma once

#include <php.h>

static void php_uv_read_alloc(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf);

/* {{{ proto void uv_write(UVStream $handle, string $data[, callable(UVStream $handle, long $status) $callback = function() {}]) */
PHP_FUNCTION(uv_write);
/* }}} */

/* {{{ proto void uv_write2(UvStream $handle, string $data, UVTcp|UvPipe $send, callable(UVStream $handle, long $status) $callback)*/
PHP_FUNCTION(uv_write2);
/* }}} */

/* {{{ proto bool uv_is_readable(UVStream $handle) */
PHP_FUNCTION(uv_is_readable);
/* }}} */

/* {{{ proto bool uv_is_writable(UVStream $handle) */
PHP_FUNCTION(uv_is_writable);
/* }}} */

/* {{{ proto void uv_shutdown(UVStream $handle, callable(UVStream $handle, long $status) $callback) */
PHP_FUNCTION(uv_shutdown);
/* }}} */

/* {{{ proto void uv_read_start(UVStream $handle, callable(UVStream $handle, string|long $read) $callback) */
PHP_FUNCTION(uv_read_start);
/* }}} */

/* {{{ proto void uv_read_stop(UVStream $handle) */
PHP_FUNCTION(uv_read_stop);
/* }}} */
