#include <php.h>

#include "include/php_uv_private.h"

extern void php_uv_handle_open(int (*open_cb)(uv_handle_t *, long), zend_class_entry *ce, INTERNAL_FUNCTION_PARAMETERS);

static void php_uv_pipe_connect_cb(uv_connect_t *req, int status)
{
	zval retval = {0};
	zval params[2] = {0};
	php_uv_t *uv = (php_uv_t *)req->data;
	TSRMLS_FETCH_FROM_CTX(uv->thread_ctx);

	ZVAL_OBJ(&params[0], &uv->std);
	ZVAL_LONG(&params[1], status);

	php_uv_do_callback2(&retval, uv, params, 2, PHP_UV_PIPE_CONNECT_CB TSRMLS_CC);

	// PHP_UV_DEBUG_OBJ_DEL_REFCOUNT(uv_pipe_connect_cb, uv);
	zval_ptr_dtor(&params[0]);
	zval_ptr_dtor(&params[1]);

	zval_ptr_dtor(&retval);
	efree(req);
}

/* {{{ proto UVPipe uv_pipe_init([UVLoop $loop = uv_default_loop(), bool $ipc = false])
 */
PHP_FUNCTION(uv_pipe_init)
{
	php_uv_t *uv;
	php_uv_loop_t *loop = NULL;
	zend_bool ipc = 0;

	ZEND_PARSE_PARAMETERS_START(0, 2)
	Z_PARAM_OPTIONAL
	UV_PARAM_OBJ_NULL(loop, php_uv_loop_t, uv_loop_ce)
	Z_PARAM_BOOL(ipc)
	ZEND_PARSE_PARAMETERS_END();

	PHP_UV_FETCH_UV_DEFAULT_LOOP(loop);

	PHP_UV_INIT_UV_EX(uv, uv_pipe_ce, uv_pipe_init, (int)ipc);

	RETURN_OBJ(&uv->std);
}
/* }}} */

/* {{{ proto long|false uv_pipe_open(UVPipe $handle, resource|long $pipe)
 */
PHP_FUNCTION(uv_pipe_open)
{
	php_uv_handle_open((int (*)(uv_handle_t *, long))uv_pipe_open, uv_pipe_ce, INTERNAL_FUNCTION_PARAM_PASSTHRU);
}
/* }}} */

/* {{{ proto long uv_pipe_bind(UVPipe $handle, string $name)
 */
PHP_FUNCTION(uv_pipe_bind)
{
	php_uv_t *uv;
	zend_string *name;
	int error;

	ZEND_PARSE_PARAMETERS_START(2, 2)
	UV_PARAM_OBJ(uv, php_uv_t, uv_pipe_ce)
	Z_PARAM_STR(name)
	ZEND_PARSE_PARAMETERS_END();

	error = uv_pipe_bind(&uv->uv.pipe, name->val);
	if (error)
	{
		php_error_docref(NULL, E_WARNING, "%s", php_uv_strerror(error));
	}

	RETURN_LONG(error);
}
/* }}} */

/* {{{ proto void uv_pipe_connect(UVPipe $handle, string $path, callable(UVPipe $handle, long $status) $callback)
 */
PHP_FUNCTION(uv_pipe_connect)
{
	php_uv_t *uv;
	zend_string *name;
	uv_connect_t *req;
	zend_fcall_info fci = empty_fcall_info;
	zend_fcall_info_cache fcc = empty_fcall_info_cache;
	php_uv_cb_t *cb;

	ZEND_PARSE_PARAMETERS_START(3, 3)
	UV_PARAM_OBJ(uv, php_uv_t, uv_pipe_ce)
	Z_PARAM_STR(name)
	Z_PARAM_FUNC(fci, fcc)
	ZEND_PARSE_PARAMETERS_END();

	GC_ADDREF(&uv->std);
	// PHP_UV_DEBUG_OBJ_ADD_REFCOUNT(uv_pipe_connect, uv);

	req = (uv_connect_t *)emalloc(sizeof(uv_connect_t));
	php_uv_cb_init(&cb, uv, &fci, &fcc, PHP_UV_PIPE_CONNECT_CB);

	req->data = uv;
	uv_pipe_connect(req, &uv->uv.pipe, name->val, php_uv_pipe_connect_cb);
}
/* }}} */

/* {{{ proto void uv_pipe_pending_instances(UVPipe $handle, long $count)
 */
PHP_FUNCTION(uv_pipe_pending_instances)
{
	php_uv_t *uv;
	zend_long count;

	ZEND_PARSE_PARAMETERS_START(2, 2)
	UV_PARAM_OBJ(uv, php_uv_t, uv_pipe_ce)
	Z_PARAM_LONG(count)
	ZEND_PARSE_PARAMETERS_END();

	uv_pipe_pending_instances(&uv->uv.pipe, count);
}
/* }}} */

/* {{{ proto void uv_pipe_pending_count(UVPipe $handle)
 */
PHP_FUNCTION(uv_pipe_pending_count)
{
	php_uv_t *uv;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	UV_PARAM_OBJ(uv, php_uv_t, uv_pipe_ce)
	ZEND_PARSE_PARAMETERS_END();

	RETURN_LONG(uv_pipe_pending_count(&uv->uv.pipe));
}
/* }}} */

/* {{{ proto void uv_pipe_pending_type(UVPipe $handle)
 */
PHP_FUNCTION(uv_pipe_pending_type)
{
	php_uv_t *uv;
	uv_handle_type ret;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	UV_PARAM_OBJ(uv, php_uv_t, uv_pipe_ce)
	ZEND_PARSE_PARAMETERS_END();

	ret = uv_pipe_pending_type(&uv->uv.pipe);
	RETURN_LONG(ret);
}
/* }}} */
