#pragma once

#include <php.h>

/* {{{ proto UVTimer uv_timer_init([UVLoop $loop = uv_default_loop()]) */
PHP_FUNCTION(uv_timer_init);
/* }}} */

/* {{{ proto void uv_timer_start(UVTimer $timer, long $timeout, long $repeat[, callable(UVTimer $timer) $callback = function() {}]) */
PHP_FUNCTION(uv_timer_start);
/* }}} */

/* {{{ proto void uv_timer_stop(UVTimer $timer) */
PHP_FUNCTION(uv_timer_stop);
/* }}} */

/* {{{ proto void uv_timer_again(UVTimer $timer) */
PHP_FUNCTION(uv_timer_again);
/* }}} */

/* {{{ proto void uv_timer_set_repeat(UVTimer $timer, long $repeat) */
PHP_FUNCTION(uv_timer_set_repeat);
/* }}} */

/* {{{ proto long uv_timer_get_repeat(UVTimer $timer) */
PHP_FUNCTION(uv_timer_get_repeat);
/* }}} */
