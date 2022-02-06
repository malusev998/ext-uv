#pragma once

#include <php.h>

/* {{{ proto UVAsync uv_async_init(UVLoop $loop, callable(UVAsync $handle) $callback) */
PHP_FUNCTION(uv_async_init);
/* }}} */

/* {{{ proto void uv_async_send(UVAsync $handle) */
PHP_FUNCTION(uv_async_send);
/* }}} */
