#pragma once

#include "php_uv.h"

php_uv_loop_t *php_uv_default_loop();
void destruct_uv(zend_object *obj);
void clean_uv_handle(php_uv_t *uv);

#define PHP_UV_FETCH_UV_DEFAULT_LOOP(loop) \
	if (loop == NULL)                      \
	{                                      \
		loop = php_uv_default_loop();      \
	}

#define PHP_UV_DEINIT_UV(uv) \
	clean_uv_handle(uv);     \
	OBJ_RELEASE(&uv->std);

#define PHP_UV_INIT_GENERIC(dest, type, ce) \
	do                                      \
	{                                       \
		zval zv;                            \
		object_init_ex(&zv, ce);            \
		dest = (type *)Z_OBJ(zv);           \
	} while (0)

#define PHP_UV_INIT_UV(uv, ce) PHP_UV_INIT_GENERIC(uv, php_uv_t, ce)

#define PHP_UV_INIT_UV_EX(_uv, ce, cb, ...)                          \
	do                                                               \
	{                                                                \
		int r;                                                       \
		PHP_UV_INIT_UV(_uv, ce);                                     \
		r = cb(&loop->loop, (void *)&_uv->uv.handle, ##__VA_ARGS__); \
		if (r)                                                       \
		{                                                            \
			PHP_UV_DEINIT_UV(_uv);                                   \
			php_error_docref(NULL, E_WARNING, #cb " failed");        \
			RETURN_FALSE;                                            \
		}                                                            \
	} while (0)
