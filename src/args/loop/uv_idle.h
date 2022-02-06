#pragma once

#include <php.h>

/* {{{ proto UVIdle uv_idle_init([UVLoop $loop = uv_default_loop()]) */
PHP_FUNCTION(uv_idle_init);
/* }}} */

/* {{{ proto void uv_idle_start(UVIdle $idle, callable $callback) */
PHP_FUNCTION(uv_idle_start);
/* }}} */

/* {{{ proto void uv_idle_stop(UVIdle $idle) */
PHP_FUNCTION(uv_idle_stop);
/* }}} */
