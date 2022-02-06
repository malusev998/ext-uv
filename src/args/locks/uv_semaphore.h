#pragma once

#include <php.h>

/* {{{ proto UVLock uv_sem_init(long $value) */
PHP_FUNCTION(uv_sem_init);
/* }}} */

/* {{{ proto void uv_sem_post(UVLock $sem) */
PHP_FUNCTION(uv_sem_post);
/* }}} */

/* {{{ proto void uv_sem_wait(UVLock $sem) */
PHP_FUNCTION(uv_sem_wait);
/* }}} */

/* {{{ proto long uv_sem_trywait(UVLock $sem) */
PHP_FUNCTION(uv_sem_trywait);
/* }}} */
