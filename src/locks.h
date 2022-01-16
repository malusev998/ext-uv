#include <uv.h>
#include <php.h>

#ifndef PHP_UV_LOCKS_H
#define PHP_UV_LOCKS_H

enum php_uv_lock_type {
	IS_UV_RWLOCK = 1,
	IS_UV_RWLOCK_RD = 2,
	IS_UV_RWLOCK_WR = 3,
	IS_UV_MUTEX = 4,
	IS_UV_SEMAPHORE = 5,
};

typedef struct {
	zend_object std;

	int locked;
	enum php_uv_lock_type type;
	union {
		uv_rwlock_t rwlock;
		uv_mutex_t mutex;
		uv_sem_t semaphore;
	} lock;
} php_uv_lock_t;


void php_uv_create_uv_lock_class(zend_object_handlers uv_default_handlers);

PHP_FUNCTION(uv_mutex_trylock);
PHP_FUNCTION(uv_mutex_lock);
PHP_FUNCTION(uv_mutex_unlock);
PHP_FUNCTION(uv_rwlock_init);
PHP_FUNCTION(uv_rwlock_rdlock);
PHP_FUNCTION(uv_rwlock_tryrdlock);
PHP_FUNCTION(uv_rwlock_rdunlock);
PHP_FUNCTION(uv_rwlock_wrlock);
PHP_FUNCTION(uv_rwlock_trywrlock);
PHP_FUNCTION(uv_rwlock_wrunlock);
PHP_FUNCTION(uv_mutex_init);
PHP_FUNCTION(uv_sem_init);
PHP_FUNCTION(uv_sem_post);
PHP_FUNCTION(uv_sem_wait);
PHP_FUNCTION(uv_sem_trywait);

#endif