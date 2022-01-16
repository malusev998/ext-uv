#include <php.h>
#include "../locks.h"
#include "php_lock.h"

/* {{{ proto UVLock uv_sem_init(long $value)
*/
PHP_FUNCTION(uv_sem_init)
{
	php_uv_lock_init(IS_UV_SEMAPHORE, INTERNAL_FUNCTION_PARAM_PASSTHRU);
}
/* }}} */

/* {{{ proto void uv_sem_post(UVLock $sem)
*/
PHP_FUNCTION(uv_sem_post)
{
	php_uv_lock_lock(IS_UV_SEMAPHORE, INTERNAL_FUNCTION_PARAM_PASSTHRU);
}
/* }}} */

/* {{{ proto void uv_sem_wait(UVLock $sem)
*/
PHP_FUNCTION(uv_sem_wait)
{
	php_uv_lock_unlock(IS_UV_SEMAPHORE, INTERNAL_FUNCTION_PARAM_PASSTHRU);
}
/* }}} */

/* {{{ proto long uv_sem_trywait(UVLock $sem)
*/
PHP_FUNCTION(uv_sem_trywait)
{
	php_uv_lock_trylock(IS_UV_SEMAPHORE, INTERNAL_FUNCTION_PARAM_PASSTHRU);
}
/* }}} */
