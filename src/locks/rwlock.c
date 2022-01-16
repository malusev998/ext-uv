#include <php.h>

#include "../locks.h"
#include "php_lock.h"

/* {{{ proto UVLock uv_rwlock_init(void)
*/
PHP_FUNCTION(uv_rwlock_init)
{
	php_uv_lock_init(IS_UV_RWLOCK, INTERNAL_FUNCTION_PARAM_PASSTHRU);
}
/* }}} */

/* {{{ proto null|false uv_rwlock_rdlock(UVLock $handle)
*/
PHP_FUNCTION(uv_rwlock_rdlock)
{
	php_uv_lock_lock(IS_UV_RWLOCK_RD, INTERNAL_FUNCTION_PARAM_PASSTHRU);
}
/* }}} */

/* {{{ proto bool uv_rwlock_tryrdlock(UVLock $handle)
*/
PHP_FUNCTION(uv_rwlock_tryrdlock)
{
	php_uv_lock_trylock(IS_UV_RWLOCK_RD, INTERNAL_FUNCTION_PARAM_PASSTHRU);
}
/* }}} */

/* {{{ proto void uv_rwlock_rdunlock(UVLock $handle)
*/
PHP_FUNCTION(uv_rwlock_rdunlock)
{
	php_uv_lock_unlock(IS_UV_RWLOCK_RD, INTERNAL_FUNCTION_PARAM_PASSTHRU);
}
/* }}} */

/* {{{ proto null|false uv_rwlock_wrlock(UVLock $handle)
*/
PHP_FUNCTION(uv_rwlock_wrlock)
{
	php_uv_lock_lock(IS_UV_RWLOCK_WR, INTERNAL_FUNCTION_PARAM_PASSTHRU);
}
/* }}} */

/* {{{ proto bool uv_rwlock_trywrlock(UVLock $handle)
*/
PHP_FUNCTION(uv_rwlock_trywrlock)
{
	php_uv_lock_trylock(IS_UV_RWLOCK_WR, INTERNAL_FUNCTION_PARAM_PASSTHRU);
}
/* }}} */

/* {{{ proto void uv_rwlock_wrunlock(UVLock $handle)
*/
PHP_FUNCTION(uv_rwlock_wrunlock)
{
	php_uv_lock_unlock(IS_UV_RWLOCK_WR, INTERNAL_FUNCTION_PARAM_PASSTHRU);
}
/* }}} */
