#include <php.h>

#include "../locks.h"
#include "php_lock.h"


/* {{{ proto UVLock uv_mutex_init(void)
*/
PHP_FUNCTION(uv_mutex_init)
{
	php_uv_lock_init(IS_UV_MUTEX, INTERNAL_FUNCTION_PARAM_PASSTHRU);
}
/* }}} */


/* {{{ proto bool uv_mutex_trylock(UVLock $lock)
*/
PHP_FUNCTION(uv_mutex_trylock)
{
	php_uv_lock_trylock(IS_UV_MUTEX, INTERNAL_FUNCTION_PARAM_PASSTHRU);
}
/* }}} */


/* {{{ proto void uv_mutex_lock(UVLock $lock)
*/
PHP_FUNCTION(uv_mutex_lock)
{
	php_uv_lock_lock(IS_UV_MUTEX, INTERNAL_FUNCTION_PARAM_PASSTHRU);
}
/* }}} */


/* {{{ void uv_mutex_unlock(UVLock $lock)

##### *Description*

unlock mutex

##### *Parameters*

*UVLock $lock*: uv resource handle (uv mutex)

##### *Return Value*

*void *:

##### *Example*

*/
PHP_FUNCTION(uv_mutex_unlock)
{
	php_uv_lock_unlock(IS_UV_MUTEX, INTERNAL_FUNCTION_PARAM_PASSTHRU);
}
/* }}} */

