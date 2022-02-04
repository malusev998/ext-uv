#pragma once

#include <php.h>

/* {{{ proto resource uv_signal_init([UVLoop $uv_loop = uv_default_loop()]) */
PHP_FUNCTION(uv_signal_init);
/* }}} */

/* {{{ proto void uv_signal_start(UVSignal $sig_handle, callable(UVSignal $sig_handle, long $sig_num) $sig_callback, int $sig_num) */
PHP_FUNCTION(uv_signal_start);
/* }}} */

/* {{{ proto int uv_signal_stop(UVSignal $sig_handle) */
PHP_FUNCTION(uv_signal_stop);
/* }}} */
