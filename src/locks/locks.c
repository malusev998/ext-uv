#include <php.h>
#include "../locks.h"
#include "php_lock.h"
#include "parsing.h"
#include "init.h"

void php_uv_lock_init(enum php_uv_lock_type lock_type, INTERNAL_FUNCTION_PARAMETERS)
{
	php_uv_lock_t* lock = NULL;
	int error = 0;

	switch (lock_type) {
	case IS_UV_RWLOCK:
	case IS_UV_RWLOCK_WR:
	case IS_UV_RWLOCK_RD:
	{
		PHP_UV_INIT_LOCK(lock, IS_UV_RWLOCK);
		error = uv_rwlock_init(PHP_UV_LOCK_RWLOCK_P(lock));
	}
	break;
	case IS_UV_MUTEX:
	{
		PHP_UV_INIT_LOCK(lock, IS_UV_MUTEX);
		error = uv_mutex_init(PHP_UV_LOCK_MUTEX_P(lock));
	}
	break;
	case IS_UV_SEMAPHORE:
	{
		zend_long val = 0;

		if (zend_parse_parameters(ZEND_NUM_ARGS(),
			"l", &val) == FAILURE) {
			return;
		}

		PHP_UV_INIT_LOCK(lock, IS_UV_SEMAPHORE);
		error = uv_sem_init(PHP_UV_LOCK_SEM_P(lock), (int)val);
	}
	break;
	default:
		php_error_docref(NULL, E_ERROR, "unexpected type");
		break;
	}

	if (error == 0) {
		RETURN_OBJ(&lock->std);
	}
	else {
		OBJ_RELEASE(&lock->std);
		RETURN_FALSE;
	}
}

void php_uv_lock_lock(enum php_uv_lock_type lock_type, INTERNAL_FUNCTION_PARAMETERS)
{
	php_uv_lock_t* lock;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		UV_PARAM_OBJ(lock, php_uv_lock_t, uv_lock_ce)
		ZEND_PARSE_PARAMETERS_END();

	switch (lock_type) {
	case IS_UV_RWLOCK:
	case IS_UV_RWLOCK_RD:
	{
		if (lock->locked == 0x01) {
			zend_error(E_WARNING, "Cannot acquire a read lock while holding a write lock");
			RETURN_FALSE;
		}

		uv_rwlock_rdlock(PHP_UV_LOCK_RWLOCK_P(lock));
		if (!lock->locked++) {
			lock->locked = 0x02;
		}
	}
	break;
	case IS_UV_RWLOCK_WR:
	{
		if (lock->locked) {
			zend_error(E_WARNING, "Cannot acquire a write lock when already holding a lock");
			RETURN_FALSE;
		}

		uv_rwlock_wrlock(PHP_UV_LOCK_RWLOCK_P(lock));
		lock->locked = 0x01;
	}
	break;
	case IS_UV_MUTEX:
	{
		uv_mutex_lock(PHP_UV_LOCK_MUTEX_P(lock));
		lock->locked = 0x01;
	}
	break;
	case IS_UV_SEMAPHORE:
	{
		uv_sem_post(PHP_UV_LOCK_SEM_P(lock));
	}
	break;
	default:
		php_error_docref(NULL, E_ERROR, "unexpected type");
		break;
	}
}

void php_uv_lock_unlock(enum php_uv_lock_type  lock_type, INTERNAL_FUNCTION_PARAMETERS)
{
	php_uv_lock_t* lock;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		UV_PARAM_OBJ(lock, php_uv_lock_t, uv_lock_ce)
		ZEND_PARSE_PARAMETERS_END();

	switch (lock_type) {
	case IS_UV_RWLOCK:
	case IS_UV_RWLOCK_RD:
	{
		if (lock->locked > 0x01) {
			uv_rwlock_rdunlock(PHP_UV_LOCK_RWLOCK_P(lock));
			if (--lock->locked == 0x01) {
				lock->locked = 0x00;
			}
		}
	}
	break;
	case IS_UV_RWLOCK_WR:
	{
		if (lock->locked == 0x01) {
			uv_rwlock_wrunlock(PHP_UV_LOCK_RWLOCK_P(lock));
			lock->locked = 0x00;
		}
	}
	break;
	case IS_UV_MUTEX:
	{
		if (lock->locked == 0x01) {
			uv_mutex_unlock(PHP_UV_LOCK_MUTEX_P(lock));
			lock->locked = 0x00;
		}
	}
	break;
	case IS_UV_SEMAPHORE:
	{
		uv_sem_wait(PHP_UV_LOCK_SEM_P(lock));
	}
	break;
	default:
		php_error_docref(NULL, E_ERROR, "unexpected type");
		break;
	}
}

void php_uv_lock_trylock(enum php_uv_lock_type lock_type, INTERNAL_FUNCTION_PARAMETERS)
{
	php_uv_lock_t* lock;
	int error = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		UV_PARAM_OBJ(lock, php_uv_lock_t, uv_lock_ce)
		ZEND_PARSE_PARAMETERS_END();

	switch (lock_type) {
	case IS_UV_RWLOCK:
	case IS_UV_RWLOCK_RD:
	{
		if (lock->locked == 0x01) {
			zend_error(E_WARNING, "Cannot acquire a read lock while holding a write lock");
			RETURN_FALSE;
		}

		error = uv_rwlock_tryrdlock(PHP_UV_LOCK_RWLOCK_P(lock));
		if (error == 0) {
			if (!lock->locked++) {
				lock->locked = 0x02;
			}
			RETURN_TRUE;
		}
		else {
			RETURN_FALSE;
		}
	}
	break;
	case IS_UV_RWLOCK_WR:
	{
		if (lock->locked) {
			zend_error(E_WARNING, "Cannot acquire a write lock when already holding a lock");
			RETURN_FALSE;
		}

		error = uv_rwlock_trywrlock(PHP_UV_LOCK_RWLOCK_P(lock));
		if (error == 0) {
			lock->locked = 0x01;
			RETURN_TRUE;
		}
		else {
			RETURN_FALSE;
		}
	}
	break;
	case IS_UV_MUTEX:
	{
		error = uv_mutex_trylock(PHP_UV_LOCK_MUTEX_P(lock));

		if (error == 0) {
			lock->locked = 0x01;
			RETURN_TRUE;
		}
		else {
			RETURN_FALSE;
		}
	}
	break;
	case IS_UV_SEMAPHORE:
	{
		error = uv_sem_trywait(PHP_UV_LOCK_SEM_P(lock));
		RETURN_LONG(error);
	}
	default:
		php_error_docref(NULL, E_ERROR, "unexpected type");
		break;
	}
}
