#include <php.h>

#include "include/php_uv_private.h"
#include "php_uv.h"

int php_uv_do_callback(zval *retval_ptr, php_uv_cb_t *callback, zval *params, int param_count TSRMLS_DC)
{
	int error;

	if (ZEND_FCI_INITIALIZED(callback->fci))
	{
		callback->fci.params = params;
		callback->fci.retval = retval_ptr;
		callback->fci.param_count = param_count;

		error = zend_call_function(&callback->fci, &callback->fcc);
	}
	else
	{
		error = -1;
	}

	return error;
}

int php_uv_do_callback2(zval *retval_ptr, php_uv_t *uv, zval *params, int param_count, enum php_uv_callback_type type TSRMLS_DC)
{
	int error = 0;
	if (ZEND_FCI_INITIALIZED(uv->callback[type]->fci))
	{
		uv->callback[type]->fci.params = params;
		uv->callback[type]->fci.retval = retval_ptr;
		uv->callback[type]->fci.param_count = param_count;
		if (zend_call_function(&uv->callback[type]->fci, &uv->callback[type]->fcc) != SUCCESS)
		{
			error = -1;
		}
	}
	else
	{
		error = -2;
	}
	// zend_fcall_info_args_clear(&uv->callback[type]->fci, 0);

	if (EG(exception))
	{
		switch (type)
		{
		case PHP_UV_FS_CB:
			uv_stop(uv->uv.fs.loop);
			break;
		case PHP_UV_GETADDR_CB:
			uv_stop(uv->uv.addrinfo.loop);
			break;
		case PHP_UV_AFTER_WORK_CB:
			uv_stop(uv->uv.work.loop);
			break;
		case PHP_UV_SHUTDOWN_CB:
			uv_stop(uv->uv.shutdown.handle->loop);
			break;
		case PHP_UV_SEND_CB:
			uv_stop(uv->uv.udp_send.handle->loop);
			break;
		case PHP_UV_CONNECT_CB:
		case PHP_UV_PIPE_CONNECT_CB:
			uv_stop(uv->uv.connect.handle->loop);
			break;
		default:
			uv_stop(uv->uv.handle.loop);
		}
	}

	return error;
}

int php_uv_do_callback3(zval *retval_ptr, php_uv_t *uv, zval *params, int param_count, enum php_uv_callback_type type)
{
	return 0;
	/*
	int error = 0;
	void *tsrm_ls, *old;
	zend_op_array *ops;
	zend_function fn, *old_fn;

	if (ZEND_FCI_INITIALIZED(uv->callback[type]->fci))
	{
		tsrm_ls = tsrm_new_interpreter_context();
		old = tsrm_set_interpreter_context(tsrm_ls);

		PG(expose_php) = 0;
		PG(auto_globals_jit) = 0;

		php_request_startup();
		EG(current_execute_data) = NULL;
		EG(current_module) = phpext_uv_ptr;

		uv->callback[type]->fci.params = params;
		uv->callback[type]->fci.retval = retval_ptr;
		uv->callback[type]->fci.param_count = param_count;
		uv->callback[type]->fci.object = NULL;
		uv->callback[type]->fci.size = sizeof(zend_fcall_info);

		uv->callback[type]->fcc.calling_scope = NULL;
		uv->callback[type]->fcc.called_scope = NULL;
		uv->callback[type]->fcc.object = NULL;

		if (!ZEND_USER_CODE(uv->callback[type]->fcc.function_handler->type))
		{
			return error = -2;
		}

		fn = *(old_fn = uv->callback[type]->fcc.function_handler);
		uv->callback[type]->fcc.function_handler = &fn;

		ops = &fn.op_array;
		ZEND_MAP_PTR_SET(ops->run_time_cache, NULL);
		if (ops->fn_flags)
		{
			ops->fn_flags &= ~ZEND_ACC_CLOSURE;
			ops->prototype = NULL;
		}

		zend_try
		{
			if (zend_call_function(&uv->callback[type]->fci, &uv->callback[type]->fcc) != SUCCESS)
			{
				error = -1;
			}
		}
		zend_catch
		{
			error = -1;
		}
		zend_end_try();

		uv->callback[type]->fcc.function_handler = old_fn;

		php_request_shutdown(NULL);
		tsrm_set_interpreter_context(old);
		tsrm_free_interpreter_context(tsrm_ls);
	}
	else
	{
		error = -2;
	}

	// zend_fcall_info_args_clear(&uv->callback[type]->fci, 0);

	return error;
	*/
}
