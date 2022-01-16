#include <php.h>

#include "parsing.h"
#include "php_lock.h"
#include "register.h"

#include "../locks.h"

zend_class_entry* uv_lock_ce;
zend_object_handlers uv_lock_handlers;

static zend_object* php_uv_create_uv_lock(zend_class_entry* ce);
static void destruct_uv_lock(zend_object* obj);

void php_uv_create_uv_lock_class(zend_object_handlers uv_default_handlers) {
	uv_lock_ce = php_uv_register_internal_class("UVLock");
	uv_lock_ce->create_object = php_uv_create_uv_lock;
	memcpy(&uv_lock_handlers, &uv_default_handlers, sizeof(zend_object_handlers));
	uv_lock_handlers.dtor_obj = destruct_uv_lock;
}

static zend_object* php_uv_create_uv_lock(zend_class_entry* ce) {
	php_uv_lock_t* lock = emalloc(sizeof(php_uv_lock_t));
	zend_object_std_init(&lock->std, ce);
	lock->std.handlers = &uv_lock_handlers;

	lock->locked = 0;

	return &lock->std;
}


static void destruct_uv_lock(zend_object* obj)
{
	php_uv_lock_t* lock = (php_uv_lock_t*)obj;

	if (lock->type == IS_UV_RWLOCK) {
		if (lock->locked == 0x01) {
			php_error_docref(NULL, E_NOTICE, "uv_rwlock: still locked resource detected; forcing wrunlock");
			uv_rwlock_wrunlock(PHP_UV_LOCK_RWLOCK_P(lock));
		}
		else if (lock->locked) {
			php_error_docref(NULL, E_NOTICE, "uv_rwlock: still locked resource detected; forcing rdunlock");
			while (--lock->locked > 0) {
				uv_rwlock_rdunlock(PHP_UV_LOCK_RWLOCK_P(lock));
			}
		}
		uv_rwlock_destroy(PHP_UV_LOCK_RWLOCK_P(lock));
	}
	else if (lock->type == IS_UV_MUTEX) {
		if (lock->locked == 0x01) {
			php_error_docref(NULL, E_NOTICE, "uv_mutex: still locked resource detected; forcing unlock");
			uv_mutex_unlock(PHP_UV_LOCK_MUTEX_P(lock));
		}
		uv_mutex_destroy(PHP_UV_LOCK_MUTEX_P(lock));
	}
	else if (lock->type == IS_UV_SEMAPHORE) {
		if (lock->locked == 0x01) {
			php_error_docref(NULL, E_NOTICE, "uv_sem: still locked resource detected; forcing unlock");
			uv_sem_post(PHP_UV_LOCK_SEM_P(lock));
		}
		uv_sem_destroy(PHP_UV_LOCK_SEM_P(lock));
	}
}
