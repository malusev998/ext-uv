#include <php.h>

#include "init.h"
#include "../locks.h"

#ifndef PHP_UV_LOCKS_COMMON_H
#define PHP_UV_LOCKS_COMMON_H

extern zend_class_entry* uv_lock_ce;
extern zend_object_handlers uv_lock_handlers;

#define PHP_UV_LOCK_RWLOCK_P(_lock) &_lock->lock.rwlock
#define PHP_UV_LOCK_MUTEX_P(_lock) &_lock->lock.mutex
#define PHP_UV_LOCK_SEM_P(_lock) &_lock->lock.semaphore

#define PHP_UV_INIT_LOCK(lock, lock_type) \
	PHP_UV_INIT_GENERIC(lock, php_uv_lock_t, uv_lock_ce); \
	lock->type = lock_type;

void php_uv_lock_init(enum php_uv_lock_type lock_type, INTERNAL_FUNCTION_PARAMETERS);
void php_uv_lock_lock(enum php_uv_lock_type lock_type, INTERNAL_FUNCTION_PARAMETERS);
void php_uv_lock_unlock(enum php_uv_lock_type  lock_type, INTERNAL_FUNCTION_PARAMETERS);
void php_uv_lock_trylock(enum php_uv_lock_type lock_type, INTERNAL_FUNCTION_PARAMETERS);
#endif