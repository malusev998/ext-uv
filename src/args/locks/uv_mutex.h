#pragma once

#include <php.h>

/* {{{ proto UVLock uv_mutex_init(void) */
PHP_FUNCTION(uv_mutex_init);

/* {{{ proto void uv_mutex_lock(UVLock $lock) */
PHP_FUNCTION(uv_mutex_lock);
/* }}} */

/* {{{ proto bool uv_mutex_trylock(UVLock $lock) */
PHP_FUNCTION(uv_mutex_trylock);
/* }}} */

/* {{{ void uv_mutex_unlock(UVLock $lock) */
PHP_FUNCTION(uv_mutex_unlock);
/* }}} */
