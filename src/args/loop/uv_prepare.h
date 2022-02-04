#pragma once

#include <php.h>

/* {{{ proto UVPrepare uv_prepare_init(UVLoop $loop) */
PHP_FUNCTION(uv_prepare_init);
/* }}} */

/* {{{ proto long uv_prepare_start(UVPrepare $handle, callable(UVPrepare $handle) $callback) */
PHP_FUNCTION(uv_prepare_start);
/* }}} */

/* {{{ proto long uv_prepare_stop(UVPrepare $handle) */
PHP_FUNCTION(uv_prepare_stop);
/* }}} */

