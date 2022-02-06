#include <php.h>

#include "include/php_uv_private.h"
#include "php_uv.h"

#include "src/args/fs/uv_fs_poll.h"

zend_class_entry *uv_fs_poll_ce;

static zval php_uv_stat_to_zval(const uv_stat_t *stat)
{
	zval result = {0};
	array_init(&result);

	add_assoc_long_ex(&result, ZEND_STRL("dev"), stat->st_dev);
	add_assoc_long_ex(&result, ZEND_STRL("ino"), stat->st_ino);
	add_assoc_long_ex(&result, ZEND_STRL("mode"), stat->st_mode);
	add_assoc_long_ex(&result, ZEND_STRL("nlink"), stat->st_nlink);
	add_assoc_long_ex(&result, ZEND_STRL("uid"), stat->st_uid);
	add_assoc_long_ex(&result, ZEND_STRL("gid"), stat->st_gid);
	add_assoc_long_ex(&result, ZEND_STRL("rdev"), stat->st_rdev);
	add_assoc_long_ex(&result, ZEND_STRL("size"), stat->st_size);
	add_assoc_long_ex(&result, ZEND_STRL("blksize"), stat->st_blksize);
	add_assoc_long_ex(&result, ZEND_STRL("blocks"), stat->st_blocks);
	add_assoc_long_ex(&result, ZEND_STRL("atime"), stat->st_atim.tv_sec);
	add_assoc_long_ex(&result, ZEND_STRL("mtime"), stat->st_mtim.tv_sec);
	add_assoc_long_ex(&result, ZEND_STRL("ctime"), stat->st_ctim.tv_sec);

	return result;
}

static void php_uv_fs_poll_cb(uv_fs_poll_t *handle, int status, const uv_stat_t *prev, const uv_stat_t *curr)
{
	zval params[4] = {0};
	zval retval = {0};
	php_uv_t *uv = (php_uv_t *)handle->data;
	TSRMLS_FETCH_FROM_CTX(uv->thread_ctx);

	ZVAL_OBJ(&params[0], &uv->std);
	GC_ADDREF(&uv->std);
	ZVAL_LONG(&params[1], status);
	params[2] = php_uv_stat_to_zval(prev);
	params[3] = php_uv_stat_to_zval(curr);

	php_uv_do_callback2(&retval, uv, params, 4, PHP_UV_FS_POLL_CB TSRMLS_CC);

	zval_ptr_dtor(&params[0]);
	zval_ptr_dtor(&params[1]);
	zval_ptr_dtor(&params[2]);
	zval_ptr_dtor(&params[3]);

	zval_ptr_dtor(&retval);
}

/* {{{ proto UVFsPoll uv_fs_poll_init([UVLoop $loop = uv_default_loop()]) */
PHP_FUNCTION(uv_fs_poll_init)
{
	php_uv_loop_t *loop = NULL;
	php_uv_t *uv;

	ZEND_PARSE_PARAMETERS_START(0, 1)
	Z_PARAM_OPTIONAL
	UV_PARAM_OBJ_NULL(loop, php_uv_loop_t, uv_loop_ce)
	ZEND_PARSE_PARAMETERS_END();

	PHP_UV_FETCH_UV_DEFAULT_LOOP(loop);
	PHP_UV_INIT_UV_EX(uv, uv_fs_poll_ce, uv_fs_poll_init);

	RETURN_OBJ(&uv->std);
}
/* }}} */

/* {{{ proto uv uv_fs_poll_start(UVFsPoll $handle, callable(UVFsPoll $handle, long $status, array $prev_stat, array $cur_stat) $callback, string $path, long $interval) */
PHP_FUNCTION(uv_fs_poll_start)
{
	php_uv_t *uv;
	zend_string *path;
	zend_long interval = 0;
	int error;
	zend_fcall_info fci = empty_fcall_info;
	zend_fcall_info_cache fcc = empty_fcall_info_cache;
	php_uv_cb_t *cb;

	ZEND_PARSE_PARAMETERS_START(4, 4)
	UV_PARAM_OBJ(uv, php_uv_t, uv_fs_poll_ce)
	Z_PARAM_FUNC(fci, fcc)
	Z_PARAM_STR(path)
	Z_PARAM_LONG(interval)
	ZEND_PARSE_PARAMETERS_END();

	php_uv_cb_init(&cb, uv, &fci, &fcc, PHP_UV_FS_POLL_CB);
	GC_ADDREF(&uv->std);
	PHP_UV_DEBUG_OBJ_ADD_REFCOUNT(uv_fs_poll_start, uv);

	error = uv_fs_poll_start(&uv->uv.fs_poll, php_uv_fs_poll_cb, (const char *)path->val, interval);
	if (error)
	{
		php_error_docref(NULL, E_ERROR, "uv_fs_poll_start failed");
		OBJ_RELEASE(&uv->std);
	}
}
/* }}} */

/* {{{ proto void uv_fs_poll_stop(UVFsPoll $poll) */
PHP_FUNCTION(uv_fs_poll_stop)
{
	php_uv_t *uv;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	UV_PARAM_OBJ(uv, php_uv_t, uv_fs_poll_ce)
	ZEND_PARSE_PARAMETERS_END();

	if (!uv_is_active(&uv->uv.handle))
	{
		return;
	}

	uv_fs_poll_stop(&uv->uv.fs_poll);

	PHP_UV_DEBUG_OBJ_DEL_REFCOUNT(uv_fs_poll_stop, uv);
	OBJ_RELEASE(&uv->std);
}
/* }}} */
