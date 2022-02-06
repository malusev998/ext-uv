#include <php.h>

#include "include/php_uv_private.h"
#include "php_uv.h"

#include "src/args/fs/uv_fs_common.h"

static php_socket_t php_uv_zval_to_valid_poll_fd(zval *ptr)
{
	php_socket_t fd = -1;
	php_stream *stream;

	/* Validate Checks */

	php_socket *socket;
	/* TODO: is this correct on windows platform? */
	if (Z_TYPE_P(ptr) == IS_RESOURCE)
	{
		if ((stream = (php_stream *)zend_fetch_resource_ex(ptr, NULL, php_file_le_stream())))
		{
			/* make sure only valid resource streams are passed - plainfiles and most php streams are invalid */
			if (stream->wrapper && !strcmp((char *)stream->wrapper->wops->label, "PHP") && (!stream->orig_path || (strncmp(stream->orig_path, "php://std", sizeof("php://std") - 1) && strncmp(stream->orig_path, "php://fd", sizeof("php://fd") - 1))))
			{
				php_error_docref(NULL, E_WARNING, "invalid resource passed, this resource is not supported");
				return -1;
			}

			/* Some streams (specifically STDIO and encrypted streams) can be cast to FDs */
			if (php_stream_cast(stream, PHP_STREAM_AS_FD_FOR_SELECT | PHP_STREAM_CAST_INTERNAL, (void *)&fd, 1) == SUCCESS && fd >= 0)
			{
				if (stream->wrapper && !strcmp((char *)stream->wrapper->wops->label, "plainfile"))
				{
					struct stat stat;
					fstat(fd, &stat);
					if (!S_ISFIFO(stat.st_mode))
					{
						php_error_docref(NULL, E_WARNING, "invalid resource passed, this plain files are not supported");
						return -1;
					}
				}
				return fd;
			}

			fd = -1;
		}
		else
		{
			php_error_docref(NULL, E_WARNING, "unhandled resource type detected.");
			fd = -1;
		}
	}
	else if (socket_ce && Z_TYPE_P(ptr) == IS_OBJECT && Z_OBJCE_P(ptr) == socket_ce && (socket = (php_socket *)((char *)(Z_OBJ_P(ptr)) - XtOffsetOf(php_socket, std))))
	{
		fd = socket->bsd_socket;
	}

	return fd;
}

static void php_uv_poll_cb(uv_poll_t *handle, int status, int events)
{
	zval params[4] = {0};
	zval retval = {0};
	php_uv_t *uv = (php_uv_t *)handle->data;
	TSRMLS_FETCH_FROM_CTX(uv->thread_ctx);

	ZVAL_OBJ(&params[0], &uv->std);
	if (status == 0)
	{
		GC_ADDREF(&uv->std);
	}
	ZVAL_LONG(&params[1], status);
	ZVAL_LONG(&params[2], events);

	if (!Z_ISUNDEF(uv->fs_fd))
	{
		ZVAL_COPY(&params[3], &uv->fs_fd);
	}
	else
	{
		PHP_UV_FD_TO_ZVAL(&params[3], uv->sock);
	}

	php_uv_do_callback2(&retval, uv, params, 4, PHP_UV_POLL_CB TSRMLS_CC);

	zval_ptr_dtor(&params[0]);
	zval_ptr_dtor(&params[1]);
	zval_ptr_dtor(&params[2]);
	zval_ptr_dtor(&params[3]);

	zval_ptr_dtor(&retval);
}

/* {{{ proto UVPoll uv_poll_init(UVLoop $loop, resource $fd)
 */
PHP_FUNCTION(uv_poll_init)
{
	zval *zstream;
	php_uv_loop_t *loop;
	php_uv_t *uv;
	unsigned long fd = 0;

	ZEND_PARSE_PARAMETERS_START(2, 2)
	UV_PARAM_OBJ(loop, php_uv_loop_t, uv_loop_ce)
	Z_PARAM_RESOURCE(zstream)
	ZEND_PARSE_PARAMETERS_END();

	PHP_UV_FETCH_UV_DEFAULT_LOOP(loop);
	fd = php_uv_zval_to_valid_poll_fd(zstream);
	PHP_UV_INIT_UV_EX(uv, uv_poll_ce, uv_poll_init, fd);
	PHP_UV_CHECK_VALID_FD(fd, zstream);

	uv->sock = fd;

	RETURN_OBJ(&uv->std);
}

/* }}} */

/* {{{ proto void uv_poll_start(UVPoll $handle, long $events, callable(UVPoll $handle, long $status, long $events, resource $fd) $callback)
 */
PHP_FUNCTION(uv_poll_start)
{
	php_uv_t *uv;
	zend_long events = 0;
	int error;
	zend_fcall_info fci = empty_fcall_info;
	zend_fcall_info_cache fcc = empty_fcall_info_cache;
	php_uv_cb_t *cb;

	ZEND_PARSE_PARAMETERS_START(3, 3)
	UV_PARAM_OBJ(uv, php_uv_t, uv_poll_ce)
	Z_PARAM_LONG(events)
	Z_PARAM_FUNC(fci, fcc)
	ZEND_PARSE_PARAMETERS_END();

	php_uv_cb_init(&cb, uv, &fci, &fcc, PHP_UV_POLL_CB);
	if (!uv_is_active(&uv->uv.handle))
	{
		PHP_UV_DEBUG_OBJ_ADD_REFCOUNT(uv_poll_start, uv);
		GC_ADDREF(&uv->std);
	}

	error = uv_poll_start(&uv->uv.poll, events, php_uv_poll_cb);
	if (error)
	{
		php_error_docref(NULL, E_ERROR, "uv_poll_start failed");
		return;
	}
}
/* }}} */

/* {{{ proto void uv_poll_stop(UVPoll $poll)
 */
PHP_FUNCTION(uv_poll_stop)
{
	php_uv_t *uv;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	UV_PARAM_OBJ(uv, php_uv_t, uv_poll_ce)
	ZEND_PARSE_PARAMETERS_END();

	if (!uv_is_active((uv_handle_t *)&uv->uv.poll))
	{
		return;
	}

	uv_poll_stop(&uv->uv.poll);

	PHP_UV_DEBUG_OBJ_DEL_REFCOUNT(uv_poll_stop, uv);
	OBJ_RELEASE(&uv->std);
}
/* }}} */
