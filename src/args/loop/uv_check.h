#pragma once

#include <php.h>

/* {{{ proto UVCheck uv_check_init([UVLoop $loop]) */
PHP_FUNCTION(uv_check_init);
/* }}} */

/* {{{ proto void uv_check_start(UVCheck $handle, callable(UVCheck $handle) $callback) */
PHP_FUNCTION(uv_check_start);
/* }}} */

/* {{{ proto void uv_check_stop(UVCheck $handle) */
PHP_FUNCTION(uv_check_stop);
/* }}} */
