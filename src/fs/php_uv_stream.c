#include <php.h>
#include <uv.h>

#include "include/php_uv_private.h"
#include "php_uv.h"

typedef struct
{
	uv_write_t req;
	uv_buf_t buf;
	php_uv_cb_t *cb;
} write_req_t;

zend_class_entry *uv_stream_ce;

#define PHP_UV_INIT_WRITE_REQ(w, uv, str, strlen, cb)    \
	w = (write_req_t *)emalloc(sizeof(write_req_t));     \
	w->req.data = uv;                                    \
	w->buf = uv_buf_init(estrndup(str, strlen), strlen); \
	w->cb = cb;

static void php_uv_read_alloc(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf)
{
	buf->base = emalloc(suggested_size);
	buf->len = suggested_size;
}

static void php_uv_free_write_req(write_req_t *wr)
{
	if (wr->cb)
	{
		if (ZEND_FCI_INITIALIZED(wr->cb->fci))
		{
			zval_ptr_dtor(&wr->cb->fci.function_name);
			if (wr->cb->fci.object != NULL)
			{
				OBJ_RELEASE(wr->cb->fci.object);
			}
		}

		efree(wr->cb);
	}
	if (wr->buf.base)
	{
		efree(wr->buf.base);
	}
	efree(wr);
}

static php_uv_cb_t *php_uv_cb_init_dynamic(php_uv_t *uv, zend_fcall_info *fci, zend_fcall_info_cache *fcc)
{
	php_uv_cb_t *cb = emalloc(sizeof(php_uv_cb_t));

	memcpy(&cb->fci, fci, sizeof(zend_fcall_info));
	memcpy(&cb->fcc, fcc, sizeof(zend_fcall_info_cache));

	if (ZEND_FCI_INITIALIZED(*fci))
	{
		Z_TRY_ADDREF(cb->fci.function_name);
		if (fci->object)
		{
			GC_ADDREF(cb->fci.object);
		}
	}

	return cb;
}

static void php_uv_write_cb(uv_write_t *req, int status)
{
	write_req_t *wr = (write_req_t *)req;
	zval retval = {0};
	zval params[2] = {0};
	php_uv_t *uv = (php_uv_t *)req->handle->data;
	TSRMLS_FETCH_FROM_CTX(uv->thread_ctx);

	ZVAL_OBJ(&params[0], &uv->std);
	ZVAL_LONG(&params[1], status);

	php_uv_do_callback(&retval, wr->cb, params, 2 TSRMLS_CC);

	if (EG(exception))
	{
		uv_stop(uv->uv.handle.loop);
	}

	zval_ptr_dtor(&params[0]);
	zval_ptr_dtor(&params[1]);
	zval_ptr_dtor(&retval);

	php_uv_free_write_req(wr);
}

static void php_uv_shutdown_cb(uv_shutdown_t *handle, int status)
{
	zval retval = {0};
	zval params[2] = {0};
	php_uv_t *uv = (php_uv_t *)handle->data;
	TSRMLS_FETCH_FROM_CTX(uv->thread_ctx);

	ZVAL_OBJ(&params[0], &uv->std);
	ZVAL_LONG(&params[1], status);

	php_uv_do_callback2(&retval, uv, params, 2, PHP_UV_SHUTDOWN_CB TSRMLS_CC);

	PHP_UV_DEBUG_OBJ_DEL_REFCOUNT(uv_shutdown_cb, uv);
	zval_ptr_dtor(&params[0]);
	zval_ptr_dtor(&params[1]);

	zval_ptr_dtor(&retval);
}

static void php_uv_read_cb(uv_stream_t *handle, ssize_t nread, const uv_buf_t *buf)
{
	zval retval = {0};
	zval params[2] = {0};
	php_uv_t *uv = (php_uv_t *)handle->data;
	TSRMLS_FETCH_FROM_CTX(uv->thread_ctx);

	PHP_UV_DEBUG_PRINT("uv_read_cb\n");

	ZVAL_OBJ(&params[0], &uv->std);
	if (nread > 0)
	{ // uv disables itself when it reaches EOF/error
		GC_ADDREF(&uv->std);
		PHP_UV_DEBUG_OBJ_ADD_REFCOUNT(uv_read_cb, uv);
	}

	if (nread > 0)
	{
		ZVAL_STRINGL(&params[1], buf->base, nread);
	}
	else
	{
		ZVAL_LONG(&params[1], nread);
	}

	php_uv_do_callback2(&retval, uv, params, 2, PHP_UV_READ_CB TSRMLS_CC);

	PHP_UV_DEBUG_OBJ_DEL_REFCOUNT(uv_read_cb, uv);
	zval_ptr_dtor(&params[0]);
	zval_ptr_dtor(&params[1]);

	zval_ptr_dtor(&retval);

	if (buf->base)
	{
		efree(buf->base);
	}
}

/* unused: static void php_uv_read2_cb(uv_pipe_t* handle, ssize_t nread, uv_buf_t buf, uv_handle_type pending); */

/* {{{ proto void uv_write(UVStream $handle, string $data[, callable(UVStream $handle, long $status) $callback = function() {}]) */
PHP_FUNCTION(uv_write)
{
	zend_string *data;
	int r;
	php_uv_t *uv;
	write_req_t *w;
	zend_fcall_info fci = empty_fcall_info;
	zend_fcall_info_cache fcc = empty_fcall_info_cache;
	php_uv_cb_t *cb;

	ZEND_PARSE_PARAMETERS_START(2, 3)
	UV_PARAM_OBJ(uv, php_uv_t, uv_stream_ce)
	Z_PARAM_STR(data)
	Z_PARAM_OPTIONAL
	Z_PARAM_FUNC_EX(fci, fcc, 1, 0)
	ZEND_PARSE_PARAMETERS_END();

	cb = php_uv_cb_init_dynamic(uv, &fci, &fcc);
	PHP_UV_INIT_WRITE_REQ(w, uv, data->val, data->len, cb)

	r = uv_write(&w->req, &uv->uv.stream, &w->buf, 1, php_uv_write_cb);
	if (r)
	{
		php_uv_free_write_req(w);
		php_error_docref(NULL, E_WARNING, "write failed");
	}
	else
	{
		GC_ADDREF(&uv->std);
		PHP_UV_DEBUG_OBJ_ADD_REFCOUNT(uv_write, uv);
	}
}
/* }}} */

/* {{{ proto void uv_write2(UvStream $handle, string $data, UVTcp|UvPipe $send, callable(UVStream $handle, long $status) $callback)*/
PHP_FUNCTION(uv_write2)
{
	zend_string *data;
	int r;
	php_uv_t *uv, *send;
	write_req_t *w;
	zend_fcall_info fci = empty_fcall_info;
	zend_fcall_info_cache fcc = empty_fcall_info_cache;
	php_uv_cb_t *cb;

	ZEND_PARSE_PARAMETERS_START(4, 4)
	UV_PARAM_OBJ(uv, php_uv_t, uv_stream_ce)
	Z_PARAM_STR(data)
	UV_PARAM_OBJ(send, php_uv_t, uv_tcp_ce, uv_pipe_ce)
	Z_PARAM_FUNC(fci, fcc)
	ZEND_PARSE_PARAMETERS_END();

	cb = php_uv_cb_init_dynamic(uv, &fci, &fcc);
	PHP_UV_INIT_WRITE_REQ(w, uv, data->val, data->len, cb);

	r = uv_write2(&w->req, &uv->uv.stream, &w->buf, 1, &send->uv.stream, php_uv_write_cb);
	if (r)
	{
		php_uv_free_write_req(w);
		php_error_docref(NULL, E_ERROR, "write2 failed");
	}
	else
	{
		GC_ADDREF(&uv->std);
		PHP_UV_DEBUG_OBJ_ADD_REFCOUNT(uv_write2, uv);
	}
}
/* }}} */

/* {{{ proto bool uv_is_readable(UVStream $handle) */
PHP_FUNCTION(uv_is_readable)
{
	php_uv_t *uv;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	UV_PARAM_OBJ(uv, php_uv_t, uv_stream_ce)
	ZEND_PARSE_PARAMETERS_END();

	RETURN_BOOL(uv_is_readable(&uv->uv.stream));
}
/* }}} */

/* {{{ proto bool uv_is_writable(UVStream $handle) */
PHP_FUNCTION(uv_is_writable)
{
	php_uv_t *uv;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	UV_PARAM_OBJ(uv, php_uv_t, uv_stream_ce)
	ZEND_PARSE_PARAMETERS_END();

	RETURN_BOOL(uv_is_writable(&uv->uv.stream));
}
/* }}} */

/* {{{ proto void uv_shutdown(UVStream $handle, callable(UVStream $handle, long $status) $callback) */
PHP_FUNCTION(uv_shutdown)
{
	php_uv_t *uv;
	uv_shutdown_t *shutdown;
	zend_fcall_info fci = empty_fcall_info;
	zend_fcall_info_cache fcc = empty_fcall_info_cache;
	php_uv_cb_t *cb;
	int r = 0;

	ZEND_PARSE_PARAMETERS_START(1, 2)
	UV_PARAM_OBJ(uv, php_uv_t, uv_stream_ce)
	Z_PARAM_OPTIONAL
	Z_PARAM_FUNC_EX(fci, fcc, 1, 0)
	ZEND_PARSE_PARAMETERS_END();

	php_uv_cb_init(&cb, uv, &fci, &fcc, PHP_UV_SHUTDOWN_CB);

	GC_ADDREF(&uv->std);
	PHP_UV_DEBUG_OBJ_ADD_REFCOUNT(uv_shutdown, uv);
	shutdown = emalloc(sizeof(uv_shutdown_t));
	shutdown->data = uv;

	r = uv_shutdown(shutdown, &uv->uv.stream, (uv_shutdown_cb)php_uv_shutdown_cb);
	if (r)
	{
		php_error_docref(NULL, E_WARNING, "%s", php_uv_strerror(r));
		efree(&shutdown);
	}
}
/* }}} */

/* {{{ proto void uv_read_start(UVStream $handle, callable(UVStream $handle, string|long $read) $callback) */
PHP_FUNCTION(uv_read_start)
{
	php_uv_t *uv;
	zend_fcall_info fci = empty_fcall_info;
	zend_fcall_info_cache fcc = empty_fcall_info_cache;
	php_uv_cb_t *cb;
	int r;
	uv_os_fd_t fd;

	PHP_UV_DEBUG_PRINT("uv_read_start\n");

	ZEND_PARSE_PARAMETERS_START(2, 2)
	UV_PARAM_OBJ(uv, php_uv_t, uv_stream_ce)
	Z_PARAM_FUNC(fci, fcc)
	ZEND_PARSE_PARAMETERS_END();

	if (uv_fileno(&uv->uv.handle, &fd) != 0)
	{
		php_error_docref(NULL, E_WARNING, "passed UV handle is not initialized yet");
		return;
	}

	GC_ADDREF(&uv->std);
	PHP_UV_DEBUG_OBJ_ADD_REFCOUNT(uv_read_start, uv);

	php_uv_cb_init(&cb, uv, &fci, &fcc, PHP_UV_READ_CB);

	r = uv_read_start(&uv->uv.stream, php_uv_read_alloc, php_uv_read_cb);
	if (r)
	{
		php_error_docref(NULL, E_NOTICE, "read failed");
		OBJ_RELEASE(&uv->std);
	}
}
/* }}} */

/* {{{ proto void uv_read_stop(UVStream $handle) */
PHP_FUNCTION(uv_read_stop)
{
	php_uv_t *uv;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	UV_PARAM_OBJ(uv, php_uv_t, uv_stream_ce)
	ZEND_PARSE_PARAMETERS_END();

	if (!uv_is_active(&uv->uv.handle))
	{
		return;
	}

	uv_read_stop(&uv->uv.stream);

	PHP_UV_DEBUG_OBJ_DEL_REFCOUNT(uv_read_stop, uv);
	OBJ_RELEASE(&uv->std);
}
/* }}} */

/* unused
static void php_uv_read2_cb(uv_pipe_t* handle, ssize_t nread, uv_buf_t buf, uv_handle_type pending)
{
	zval retval = {0};
	zval params[3] = {0};
	php_uv_t *uv = (php_uv_t*)handle->data;
	TSRMLS_FETCH_FROM_CTX(uv->thread_ctx);

	PHP_UV_DEBUG_PRINT("uv_read2_cb\n");

	ZVAL_OBJ(&params[0], &uv->std);
	if (nread > 0) { // uv disables itself when it reaches EOF/error
		GC_ADDREF(&uv->std);
		PHP_UV_DEBUG_OBJ_ADD_REFCOUNT(uv_read2_cb, uv);
	}
	if (nread > 0) {
		ZVAL_STRINGL(&params[1], buf.base,nread);
	} else {
		ZVAL_LONG(&params[1], nread);
	}
	ZVAL_LONG(&params[2], pending);

	php_uv_do_callback2(&retval, uv, params, 3, PHP_UV_READ2_CB TSRMLS_CC);

	PHP_UV_DEBUG_OBJ_DEL_REFCOUNT(uv_read2_cb, uv);
	zval_ptr_dtor(&params[0]);
	zval_ptr_dtor(&params[1]);
	zval_ptr_dtor(&params[2]);

	zval_ptr_dtor(&retval);

	if (buf.base) {
		efree(buf.base);
	}
}
*/
