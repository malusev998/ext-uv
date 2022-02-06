#include <php.h>

#include "include/php_uv_private.h"
#include "php_uv.h"

#include "src/args/fs/uv_fs.h"

/* {{{ proto UVStdio uv_stdio_new([UV|resource|long|null $fd[, long $flags = 0]]) */
PHP_FUNCTION(uv_stdio_new)
{
	php_uv_stdio_t *stdio;
	zval *handle;
	zend_long flags = 0;
	php_socket *socket;

	php_socket_t fd = -1;
	php_stream *stream;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "|zl", &handle, &flags) == FAILURE)
	{
		return;
	}

	if (handle == NULL || Z_TYPE_P(handle) == IS_NULL)
	{
		flags = UV_IGNORE;
	}
	else if (Z_TYPE_P(handle) == IS_LONG)
	{
		fd = Z_LVAL_P(handle);
		if (flags & (UV_CREATE_PIPE | UV_INHERIT_STREAM))
		{
			php_error_docref(NULL, E_WARNING, "flags must not be UV::CREATE_PIPE or UV::INHERIT_STREAM for resources");
			RETURN_FALSE;
		}

		flags |= UV_INHERIT_FD;
	}
	else if (Z_TYPE_P(handle) == IS_RESOURCE)
	{
		if ((stream = (php_stream *)zend_fetch_resource_ex(handle, NULL, php_file_le_stream())))
		{
			if (php_stream_cast(stream, PHP_STREAM_AS_FD | PHP_STREAM_CAST_INTERNAL, (void *)&fd, 1) != SUCCESS || fd < 0)
			{
				php_error_docref(NULL, E_WARNING, "passed resource without file descriptor");
				RETURN_FALSE;
			}
		}
		else
		{
			php_error_docref(NULL, E_WARNING, "passed unexpected resource, expected file or socket");
			RETURN_FALSE;
		}
		if (flags & (UV_CREATE_PIPE | UV_INHERIT_STREAM))
		{
			php_error_docref(NULL, E_WARNING, "flags must not be UV::CREATE_PIPE or UV::INHERIT_STREAM for resources");
			RETURN_FALSE;
		}
		flags |= UV_INHERIT_FD;
	}
	else if (Z_TYPE_P(handle) == IS_OBJECT && instanceof_function(Z_OBJCE_P(handle), uv_ce))
	{
		if (flags & UV_INHERIT_FD)
		{
			php_error_docref(NULL, E_WARNING, "flags must not be UV::INHERIT_FD for UV handles");
			RETURN_FALSE;
		}
		if ((flags & (UV_CREATE_PIPE | UV_INHERIT_STREAM)) == (UV_CREATE_PIPE | UV_INHERIT_STREAM) || !(flags & (UV_CREATE_PIPE | UV_INHERIT_STREAM)))
		{
			php_error_docref(NULL, E_WARNING, "flags must be exactly one of UV::INHERIT_STREAM or UV::CREATE_PIPE for UV handles");
			RETURN_FALSE;
		}
	}
	else if (socket_ce && Z_TYPE_P(handle) == IS_OBJECT && Z_OBJCE_P(handle) == socket_ce && (socket = (php_socket *)((char *)(Z_OBJ_P(handle)) - XtOffsetOf(php_socket, std))))
	{
		fd = socket->bsd_socket;
		if (flags & (UV_CREATE_PIPE | UV_INHERIT_STREAM))
		{
			php_error_docref(NULL, E_WARNING, "flags must not be UV::CREATE_PIPE or UV::INHERIT_STREAM for socket objects");
			RETURN_FALSE;
		}
		flags |= UV_INHERIT_FD;
	}
	else
	{
		php_error_docref(NULL, E_WARNING, "passed unexpected value, expected instance of UV, file resource or socket object");
		RETURN_FALSE;
	}

	PHP_UV_INIT_GENERIC(stdio, php_uv_stdio_t, uv_stdio_ce);
	stdio->flags = flags;
	stdio->fd = fd;

	if (Z_TYPE_P(handle) == IS_RESOURCE || Z_TYPE_P(handle) == IS_OBJECT)
	{
		ZVAL_COPY(&stdio->stream, handle);
	}

	RETURN_OBJ(&stdio->std);
}
/* }}} */

/* {{{ proto bool uv_chdir(string $directory) */
PHP_FUNCTION(uv_chdir)
{
	zend_string *directory;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "S", &directory) == FAILURE)
	{
		return;
	}

	if (uv_chdir(directory->val) == 0)
	{
		RETURN_TRUE;
	}

	RETURN_FALSE;
}
/* }}} */

/* {{{ proto string uv_exepath(void) */
PHP_FUNCTION(uv_exepath)
{
	char buffer[MAXPATHLEN];
	size_t buffer_sz = sizeof(buffer) / sizeof(buffer[0]);

	if (zend_parse_parameters_none() == FAILURE)
	{
		return;
	}

	if (uv_exepath(buffer, &buffer_sz) == UV_EINVAL)
	{
		RETURN_FALSE; /* should be unreeachable */
	}

	RETURN_STRINGL(buffer, buffer_sz);
}
/* }}} */

/* {{{ proto string uv_cwd(void) */
PHP_FUNCTION(uv_cwd)
{
	if (zend_parse_parameters_none() == FAILURE)
	{
		return;
	}

	char buffer[MAXPATHLEN];
	size_t buffer_sz = MAXPATHLEN;

	uv_cwd(buffer, &buffer_sz);

	RETURN_STRING(buffer);
}
/* }}} */
