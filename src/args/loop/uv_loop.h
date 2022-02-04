#pragma once

#include <php.h>

#include "uv_prepare.h"
#include "uv_idle.h"
#include "uv_check.h"

/* {{{ proto UVLoop uv_default_loop() */
PHP_FUNCTION(uv_default_loop);
/* }}} */

/* {{{ proto UVLoop uv_loop_new() */
PHP_FUNCTION(uv_loop_new);
/* }}} */

/* {{{ proto bool uv_walk(UVLoop $loop, callable $closure[, array $opaque]) */
PHP_FUNCTION(uv_walk);
/* }}} */

/* {{{ proto void uv_unref(UV $uv_t) */
PHP_FUNCTION(uv_unref);
/* }}} */

/* {{{ proto void uv_update_time([UVLoop $uv_loop = uv_default_loop()]) */
PHP_FUNCTION(uv_update_time);
/* }}} */

/* {{{ proto void uv_ref(UV $uv_handle) */
PHP_FUNCTION(uv_ref);
/* }}} */

/* {{{ proto bool uv_is_active(UV $handle)*/
PHP_FUNCTION(uv_is_active);
/* }}} */

/* {{{ proto bool uv_is_closing(UV $handle) */
PHP_FUNCTION(uv_is_closing);
/* }}} */

/* {{{ proto void uv_run([UVLoop $uv_loop = uv_default_loop(), long $run_mode = UV::RUN_DEFAULT]) */
PHP_FUNCTION(uv_run);
/* }}} */

/* {{{ proto void uv_stop([UVLoop $uv_loop = uv_default_loop()])*/
PHP_FUNCTION(uv_stop);
/* }}} */

/* {{{ proto void uv_loop_delete(UVLoop $uv_loop) */
PHP_FUNCTION(uv_loop_delete);
/* }}} */

/* {{{ proto long uv_now([UVLoop $uv_loop = uv_default_loop()]) */
PHP_FUNCTION(uv_now);
/* }}} */

/* {{{ proto void uv_close(UV $handle, callable(UV $handle) $callback) */
PHP_FUNCTION(uv_close);
/* }}} */
