#pragma once

#include <php.h>

/* {{{ proto UVLock uv_rwlock_init(void) */
PHP_FUNCTION(uv_rwlock_init);
/* }}} */

/* {{{ proto null|false uv_rwlock_rdlock(UVLock $handle) */
PHP_FUNCTION(uv_rwlock_rdlock);
/* }}} */

/* {{{ proto bool uv_rwlock_tryrdlock(UVLock $handle) */
PHP_FUNCTION(uv_rwlock_tryrdlock);
/* }}} */

/* {{{ proto void uv_rwlock_rdunlock(UVLock $handle) */
PHP_FUNCTION(uv_rwlock_rdunlock);
/* }}} */

/* {{{ proto null|false uv_rwlock_wrlock(UVLock $handle) */
PHP_FUNCTION(uv_rwlock_wrlock);
/* }}} */

/* {{{ proto bool uv_rwlock_trywrlock(UVLock $handle) */
PHP_FUNCTION(uv_rwlock_trywrlock);
/* }}} */

/* {{{ proto void uv_rwlock_wrunlock(UVLock $handle) */
PHP_FUNCTION(uv_rwlock_wrunlock);
/* }}} */
