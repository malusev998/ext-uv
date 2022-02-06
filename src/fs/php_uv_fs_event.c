#include <php.h>

#include "include/php_uv_private.h"
#include "php_uv.h"
#include "src/args/fs/uv_fs_event.h"

zend_class_entry *uv_fs_event_ce;

static void php_uv_fs_event_cb(uv_fs_event_t *req, const char *filename, int events, int status)
{
	zval params[4] = {0};
	zval retval = {0};
	php_uv_t *uv = (php_uv_t *)req->data;
	TSRMLS_FETCH_FROM_CTX(uv->thread_ctx);

	ZVAL_OBJ(&params[0], &uv->std);
	GC_ADDREF(&uv->std);
	if (filename)
	{
		ZVAL_STRING(&params[1], filename);
	}
	else
	{
		ZVAL_NULL(&params[1]);
	}
	ZVAL_LONG(&params[2], events);
	ZVAL_LONG(&params[3], status);

	php_uv_do_callback2(&retval, uv, params, 4, PHP_UV_FS_EVENT_CB TSRMLS_CC);

	zval_ptr_dtor(&params[0]);
	zval_ptr_dtor(&params[1]);
	zval_ptr_dtor(&params[2]);
	zval_ptr_dtor(&params[3]);

	zval_ptr_dtor(&retval);
}

/* {{{ proto UVFsEvent uv_fs_event_init(UVLoop $loop, string $path, callable(UVFsEvent $handle, string|null $filename, long $events, long $status) $callback[, long $flags = 0]) */
PHP_FUNCTION(uv_fs_event_init)
{
	int error;
	php_uv_loop_t *loop;
	php_uv_t *uv;
	zend_string *path;
	zend_long flags = 0;
	zend_fcall_info fci = empty_fcall_info;
	zend_fcall_info_cache fcc = empty_fcall_info_cache;
	php_uv_cb_t *cb;

	ZEND_PARSE_PARAMETERS_START(3, 4)
	UV_PARAM_OBJ(loop, php_uv_loop_t, uv_loop_ce)
	Z_PARAM_STR(path)
	Z_PARAM_FUNC(fci, fcc)
	Z_PARAM_OPTIONAL
	Z_PARAM_LONG(flags)
	ZEND_PARSE_PARAMETERS_END();

	PHP_UV_FETCH_UV_DEFAULT_LOOP(loop);
	PHP_UV_INIT_UV_EX(uv, uv_fs_event_ce, uv_fs_event_init);

	php_uv_cb_init(&cb, uv, &fci, &fcc, PHP_UV_FS_EVENT_CB);

	error = uv_fs_event_start(&uv->uv.fs_event, php_uv_fs_event_cb, path->val, flags);

	if (error < 0)
	{
		php_error_docref(NULL, E_ERROR, "uv_fs_event_start failed");
		OBJ_RELEASE(&uv->std);
		return;
	}

	RETURN_OBJ(&uv->std);
}
/* }}} */
