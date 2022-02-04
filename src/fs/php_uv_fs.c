#include <php.h>
#include <php_network.h>

#include <ext/sockets/php_sockets.h>

#include "include/php_uv_private.h"
#include "php_uv.h"
#include "src/args/fs/uv_fs.h"

zend_class_entry *uv_fs_ce;

static php_socket_t php_uv_zval_to_fd(zval *ptr);
static zval php_uv_make_stat(const uv_stat_t *s);
static void php_uv_fs_cb(uv_fs_t *req);

#define PHP_UV_FS_ASYNC(loop, func, ...)                                                 \
	error = uv_fs_##func(&loop->loop, (uv_fs_t *)&uv->uv.fs, __VA_ARGS__, php_uv_fs_cb); \
	if (error)                                                                           \
	{                                                                                    \
		PHP_UV_DEINIT_UV(uv);                                                            \
		php_error_docref(NULL, E_WARNING, "uv_" #func " failed");                        \
		return;                                                                          \
	}

#define PHP_UV_ZVAL_TO_FD(fd, zstream)     \
	{                                      \
		fd = php_uv_zval_to_fd(zstream);   \
		PHP_UV_CHECK_VALID_FD(fd, zstream) \
	}

static void php_uv_fs_common(uv_fs_type fs_type, INTERNAL_FUNCTION_PARAMETERS)
{
	int error = 0;
	php_uv_loop_t *loop;
	php_uv_t *uv;
	zend_fcall_info fci = empty_fcall_info;
	zend_fcall_info_cache fcc = empty_fcall_info_cache;
	php_uv_cb_t *cb;

#define PHP_UV_FS_PARSE_PARAMETERS_EX(num, params, required_cb) \
	ZEND_PARSE_PARAMETERS_START(1 + num + required_cb, 2 + num) \
	UV_PARAM_OBJ(loop, php_uv_loop_t, uv_loop_ce)               \
	params if (!required_cb){                                   \
		Z_PARAM_OPTIONAL} Z_PARAM_FUNC_EX(fci, fcc, 1, 0)       \
		ZEND_PARSE_PARAMETERS_END()

#define PHP_UV_FS_PARSE_PARAMETERS(num, params) PHP_UV_FS_PARSE_PARAMETERS_EX(num, params, 0)

#define PHP_UV_FS_SETUP()               \
	PHP_UV_INIT_UV(uv, uv_fs_ce);       \
	PHP_UV_FETCH_UV_DEFAULT_LOOP(loop); \
	php_uv_cb_init(&cb, uv, &fci, &fcc, PHP_UV_FS_CB);

#define PHP_UV_FS_SETUP_AND_EXECUTE(command, ...) \
	PHP_UV_FS_SETUP();                            \
	PHP_UV_FS_ASYNC(loop, command, __VA_ARGS__);

	switch (fs_type)
	{
	case UV_FS_SYMLINK:
	{
		zend_string *from, *to;
		zend_long flags;

		PHP_UV_FS_PARSE_PARAMETERS(3, Z_PARAM_STR(from) Z_PARAM_STR(to) Z_PARAM_LONG(flags));
		PHP_UV_FS_SETUP_AND_EXECUTE(symlink, from->val, to->val, flags);
		break;
	}
	case UV_FS_LINK:
	{
		zend_string *from, *to;

		PHP_UV_FS_PARSE_PARAMETERS(2, Z_PARAM_STR(from) Z_PARAM_STR(to));
		PHP_UV_FS_SETUP_AND_EXECUTE(link, from->val, to->val);
		break;
	}
	case UV_FS_CHMOD:
	{
		zend_long mode;
		zend_string *path;

		PHP_UV_FS_PARSE_PARAMETERS(2, Z_PARAM_STR(path) Z_PARAM_LONG(mode));
		PHP_UV_FS_SETUP_AND_EXECUTE(chmod, path->val, mode);
		break;
	}
	case UV_FS_FCHMOD:
	{
		zval *zstream;
		zend_long mode;
		unsigned long fd;

		PHP_UV_FS_PARSE_PARAMETERS(2, Z_PARAM_RESOURCE(zstream) Z_PARAM_LONG(mode));
		PHP_UV_FS_SETUP();
		PHP_UV_ZVAL_TO_FD(fd, zstream);
		uv->fs_fd = *zstream;
		Z_ADDREF(uv->fs_fd);
		PHP_UV_FS_ASYNC(loop, fchmod, fd, mode);
		break;
	}
	case UV_FS_RENAME:
	{
		zend_string *from, *to;

		PHP_UV_FS_PARSE_PARAMETERS(2, Z_PARAM_STR(from) Z_PARAM_STR(to));
		PHP_UV_FS_SETUP_AND_EXECUTE(rename, from->val, to->val);
		break;
	}
	case UV_FS_UNLINK:
	{
		zend_string *path;

		PHP_UV_FS_PARSE_PARAMETERS(1, Z_PARAM_STR(path));
		PHP_UV_FS_SETUP_AND_EXECUTE(unlink, path->val);
		break;
	}
	case UV_FS_RMDIR:
	{
		zend_string *path;

		PHP_UV_FS_PARSE_PARAMETERS(1, Z_PARAM_STR(path));
		PHP_UV_FS_SETUP_AND_EXECUTE(rmdir, path->val);
		break;
	}
	case UV_FS_MKDIR:
	{
		zend_string *path;
		zend_long mode;

		PHP_UV_FS_PARSE_PARAMETERS(2, Z_PARAM_STR(path) Z_PARAM_LONG(mode));
		PHP_UV_FS_SETUP_AND_EXECUTE(mkdir, path->val, mode);
		break;
	}
	case UV_FS_FTRUNCATE:
	{
		zval *zstream = NULL;
		zend_long offset = 0;
		unsigned long fd;

		PHP_UV_FS_PARSE_PARAMETERS(2, Z_PARAM_RESOURCE(zstream) Z_PARAM_LONG(offset));
		PHP_UV_FS_SETUP()
		PHP_UV_ZVAL_TO_FD(fd, zstream);
		uv->fs_fd = *zstream;
		Z_ADDREF(uv->fs_fd);
		PHP_UV_FS_ASYNC(loop, ftruncate, fd, offset);
		break;
	}
	case UV_FS_FDATASYNC:
	{
		zval *zstream = NULL;
		unsigned long fd;

		PHP_UV_FS_PARSE_PARAMETERS(1, Z_PARAM_RESOURCE(zstream));
		PHP_UV_FS_SETUP()
		PHP_UV_ZVAL_TO_FD(fd, zstream);
		uv->fs_fd = *zstream;
		Z_ADDREF(uv->fs_fd);
		PHP_UV_FS_ASYNC(loop, fdatasync, fd);
		break;
	}
	case UV_FS_FSYNC:
	{
		zval *zstream = NULL;
		unsigned long fd;

		PHP_UV_FS_PARSE_PARAMETERS(1, Z_PARAM_RESOURCE(zstream));
		PHP_UV_FS_SETUP()
		PHP_UV_ZVAL_TO_FD(fd, zstream);
		uv->fs_fd = *zstream;
		Z_ADDREF(uv->fs_fd);
		PHP_UV_FS_ASYNC(loop, fsync, fd);
		break;
	}
	case UV_FS_CLOSE:
	{
		zval *zstream = NULL;
		unsigned long fd;

		PHP_UV_FS_PARSE_PARAMETERS(1, Z_PARAM_RESOURCE(zstream));
		PHP_UV_FS_SETUP()
		PHP_UV_ZVAL_TO_FD(fd, zstream);
		uv->fs_fd = *zstream;
		Z_ADDREF(uv->fs_fd);
		PHP_UV_FS_ASYNC(loop, close, fd);
		break;
	}
	case UV_FS_CHOWN:
	{
		zend_long uid, gid;
		zend_string *path;

		PHP_UV_FS_PARSE_PARAMETERS(3, Z_PARAM_STR(path) Z_PARAM_LONG(uid) Z_PARAM_LONG(gid));
		PHP_UV_FS_SETUP_AND_EXECUTE(chown, path->val, uid, gid);
		break;
	}
	case UV_FS_FCHOWN:
	{
		zval *zstream = NULL;
		zend_long uid, gid;
		unsigned long fd;

		PHP_UV_FS_PARSE_PARAMETERS(3, Z_PARAM_RESOURCE(zstream) Z_PARAM_LONG(uid) Z_PARAM_LONG(gid));
		PHP_UV_FS_SETUP()
		PHP_UV_ZVAL_TO_FD(fd, zstream);
		uv->fs_fd = *zstream;
		Z_ADDREF(uv->fs_fd);
		PHP_UV_FS_ASYNC(loop, fchown, fd, uid, gid);
		break;
	}
	case UV_FS_OPEN:
	{
		zend_string *path;
		zend_long flag, mode;

		PHP_UV_FS_PARSE_PARAMETERS_EX(3, Z_PARAM_STR(path) Z_PARAM_LONG(flag) Z_PARAM_LONG(mode), 1);
		PHP_UV_FS_SETUP_AND_EXECUTE(open, path->val, flag, mode);
		break;
	}
	case UV_FS_SCANDIR:
	{
		zend_string *path;
		zend_long flags = 0;

		ZEND_PARSE_PARAMETERS_START(3, 4)
		UV_PARAM_OBJ(loop, php_uv_loop_t, uv_loop_ce)
		Z_PARAM_STR(path)
		Z_PARAM_FUNC_EX(fci, fcc, 1, 0)
		Z_PARAM_OPTIONAL
		Z_PARAM_LONG(flags)
		ZEND_PARSE_PARAMETERS_END();
		PHP_UV_FS_SETUP_AND_EXECUTE(scandir, path->val, flags);
		break;
	}
	case UV_FS_LSTAT:
	{
		zend_string *path;

		PHP_UV_FS_PARSE_PARAMETERS_EX(1, Z_PARAM_STR(path), 1);
		PHP_UV_FS_SETUP_AND_EXECUTE(lstat, path->val);
		break;
	}
	case UV_FS_FSTAT:
	{
		zval *zstream = NULL;
		unsigned long fd;

		PHP_UV_FS_PARSE_PARAMETERS_EX(1, Z_PARAM_RESOURCE(zstream), 1);
		PHP_UV_FS_SETUP()
		PHP_UV_ZVAL_TO_FD(fd, zstream);
		uv->fs_fd = *zstream;
		Z_ADDREF(uv->fs_fd);
		PHP_UV_FS_ASYNC(loop, fstat, fd);
		break;
	}
	case UV_FS_STAT:
	{
		zend_string *path;

		PHP_UV_FS_PARSE_PARAMETERS_EX(1, Z_PARAM_STR(path), 1);
		PHP_UV_FS_SETUP_AND_EXECUTE(stat, path->val);
		break;
	}
	case UV_FS_UTIME:
	{
		zend_long utime, atime;
		zend_string *path;

		PHP_UV_FS_PARSE_PARAMETERS(3, Z_PARAM_STR(path) Z_PARAM_LONG(utime) Z_PARAM_LONG(atime));
		PHP_UV_FS_SETUP_AND_EXECUTE(utime, path->val, utime, atime);
		break;
	}
	case UV_FS_FUTIME:
	{
		zval *zstream = NULL;
		zend_long utime, atime;
		unsigned long fd;

		PHP_UV_FS_PARSE_PARAMETERS(3, Z_PARAM_RESOURCE(zstream) Z_PARAM_LONG(utime) Z_PARAM_LONG(atime));
		PHP_UV_FS_SETUP()
		PHP_UV_ZVAL_TO_FD(fd, zstream);
		uv->fs_fd = *zstream;
		Z_ADDREF(uv->fs_fd);
		PHP_UV_FS_ASYNC(loop, futime, fd, utime, atime);
		break;
	}
	case UV_FS_READLINK:
	{
		zend_string *path;

		PHP_UV_FS_PARSE_PARAMETERS_EX(1, Z_PARAM_STR(path), 1);
		PHP_UV_FS_SETUP_AND_EXECUTE(readlink, path->val);
		break;
	}
	case UV_FS_READ:
	{
		zval *zstream = NULL;
		unsigned long fd;
		zend_long length;
		zend_long offset;
		uv_buf_t buf;

		PHP_UV_FS_PARSE_PARAMETERS_EX(3, Z_PARAM_RESOURCE(zstream) Z_PARAM_LONG(offset) Z_PARAM_LONG(length), 1);
		if (length <= 0)
		{
			length = 0;
		}
		if (offset < 0)
		{
			offset = 0;
		}
		PHP_UV_FS_SETUP()
		PHP_UV_ZVAL_TO_FD(fd, zstream);
		uv->fs_fd = *zstream;
		Z_ADDREF(uv->fs_fd);

		uv->buffer = (char *)emalloc(length);
		buf = uv_buf_init(uv->buffer, length);

		PHP_UV_FS_ASYNC(loop, read, fd, &buf, 1, offset);
		break;
	}
	case UV_FS_SENDFILE:
	{
		zval *z_instream, *z_outstream = NULL;
		unsigned long in_fd, out_fd;
		zend_long offset, length = 0;

		PHP_UV_FS_PARSE_PARAMETERS(4, Z_PARAM_RESOURCE(z_instream) Z_PARAM_RESOURCE(z_outstream) Z_PARAM_LONG(offset) Z_PARAM_LONG(length));
		PHP_UV_FS_SETUP()
		/* TODO */
		PHP_UV_ZVAL_TO_FD(in_fd, z_instream);
		PHP_UV_ZVAL_TO_FD(out_fd, z_outstream);
		uv->fs_fd = *z_outstream;
		Z_ADDREF(uv->fs_fd);
		uv->fs_fd_alt = *z_instream;
		Z_ADDREF(uv->fs_fd_alt);
		PHP_UV_FS_ASYNC(loop, sendfile, in_fd, out_fd, offset, length);
		break;
	}
	case UV_FS_WRITE:
	{
		zval *zstream = NULL;
		zend_string *buffer;
		zend_long fd, offset = -1;
		uv_buf_t uv_fs_write_buf_t;

		ZEND_PARSE_PARAMETERS_START(3, 5)
		UV_PARAM_OBJ(loop, php_uv_loop_t, uv_loop_ce)
		Z_PARAM_RESOURCE(zstream)
		Z_PARAM_STR(buffer)
		Z_PARAM_OPTIONAL
		Z_PARAM_LONG(offset)
		Z_PARAM_FUNC_EX(fci, fcc, 1, 0)
		ZEND_PARSE_PARAMETERS_END();
		PHP_UV_FS_SETUP();
		PHP_UV_ZVAL_TO_FD(fd, zstream);
		uv->fs_fd = *zstream;
		Z_ADDREF(uv->fs_fd);
		uv->buffer = estrndup(buffer->val, buffer->len);

		/* TODO: is this right?! */
		uv_fs_write_buf_t = uv_buf_init(uv->buffer, buffer->len);
		PHP_UV_FS_ASYNC(loop, write, fd, &uv_fs_write_buf_t, 1, offset);
		break;
	}
	case UV_FS_UNKNOWN:
	case UV_FS_CUSTOM:
	default:
	{
		php_error_docref(NULL, E_ERROR, "type; %d does not support yet.", fs_type);
		break;
	}
	}

#undef PHP_UV_FS_PARSE_PARAMETERS
#undef PHP_UV_FS_SETUP
#undef PHP_UV_FS_SETUP_AND_EXECUTE
}

static php_socket_t php_uv_zval_to_fd(zval *ptr)
{
	php_socket_t fd = -1;
	php_stream *stream;
	php_socket *socket;
	/* TODO: is this correct on windows platform? */
	if (Z_TYPE_P(ptr) == IS_RESOURCE)
	{
		if ((stream = (php_stream *)zend_fetch_resource_ex(ptr, NULL, php_file_le_stream())))
		{
			if (php_stream_cast(stream, PHP_STREAM_AS_FD | PHP_STREAM_CAST_INTERNAL, (void *)&fd, 1) != SUCCESS || fd < 0)
			{
				fd = -1;
			}
		}
		else
		{
			php_error_docref(NULL, E_WARNING, "unhandled resource type detected.");
			fd = -1;
		}
	}
	else if (Z_TYPE_P(ptr) == IS_LONG)
	{
		fd = Z_LVAL_P(ptr);
		if (fd < 0)
		{
			fd = -1;
		}

		{
			/* make sure that a valid resource handle was passed - issue #36 */
			int err = uv_guess_handle((uv_file)fd);
			if (err == UV_UNKNOWN_HANDLE)
			{
				php_error_docref(NULL, E_WARNING, "invalid resource type detected");
				fd = -1;
			}
		}
	}
	else if (socket_ce && Z_TYPE_P(ptr) == IS_OBJECT && Z_OBJCE_P(ptr) == socket_ce && (socket = (php_socket *)((char *)(Z_OBJ_P(ptr)) - XtOffsetOf(php_socket, std))))
	{
		fd = socket->bsd_socket;
	}

	return fd;
}

static void php_uv_fs_cb(uv_fs_t *req)
{
	zval params[3] = {0};
	zval retval = {0};
	php_uv_t *uv = (php_uv_t *)req->data;
	int argc, i = 0;
	TSRMLS_FETCH_FROM_CTX(uv->thread_ctx);

	PHP_UV_DEBUG_PRINT("# php_uv_fs_cb %p\n", uv);

	if (PHP_UV_IS_DTORED(uv))
	{
		uv_fs_req_cleanup(req);

		OBJ_RELEASE(&uv->std);
		return;
	}

	if (!Z_ISUNDEF(uv->fs_fd))
	{
		ZVAL_COPY_VALUE(&params[0], &uv->fs_fd);
		ZVAL_UNDEF(&uv->fs_fd);
	}

	switch (uv->uv.fs.fs_type)
	{
	case UV_FS_SYMLINK:
	case UV_FS_LINK:
	case UV_FS_CHMOD:
	case UV_FS_RENAME:
	case UV_FS_UNLINK:
	case UV_FS_RMDIR:
	case UV_FS_MKDIR:
	case UV_FS_CLOSE:
	case UV_FS_CHOWN:
	case UV_FS_UTIME:
	case UV_FS_FUTIME:
		argc = 1;
		ZVAL_LONG(&params[0], uv->uv.fs.result);
		break;

	case UV_FS_FCHMOD:
	case UV_FS_FCHOWN:
	case UV_FS_FTRUNCATE:
	case UV_FS_FDATASYNC:
	case UV_FS_FSYNC:
		argc = 2;
		ZVAL_LONG(&params[1], uv->uv.fs.result);
		break;

	case UV_FS_OPEN:
		argc = 1;
		if (uv->uv.fs.result < 0)
		{
			ZVAL_LONG(&params[0], uv->uv.fs.result);
		}
		else
		{
			PHP_UV_FD_TO_ZVAL(&params[0], uv->uv.fs.result)
			PHP_UV_DEBUG_PRINT("Creating fs handle %p\n", Z_RES(params[0]));
		}
		break;

	case UV_FS_SCANDIR:
		argc = 1;
		if (uv->uv.fs.result < 0)
		{ /* req->ptr may be NULL here, but uv_fs_scandir_next() knows to handle it */
			ZVAL_LONG(&params[0], uv->uv.fs.result);
		}
		else
		{
			uv_dirent_t dent;

			array_init(&params[0]);
			while (UV_EOF != uv_fs_scandir_next(req, &dent))
			{
				add_next_index_string(&params[0], dent.name);
			}
		}
		break;

	case UV_FS_LSTAT:
	case UV_FS_STAT:
		argc = 1;
		if (req->ptr != NULL)
		{
			params[0] = php_uv_make_stat((const uv_stat_t *)req->ptr);
		}
		else
		{
			ZVAL_LONG(&params[0], uv->uv.fs.result);
		}
		break;
	case UV_FS_FSTAT:
		argc = 2;
		if (req->ptr != NULL)
		{
			params[1] = php_uv_make_stat((const uv_stat_t *)req->ptr);
		}
		else
		{
			ZVAL_LONG(&params[1], uv->uv.fs.result);
		}
		break;

	case UV_FS_READLINK:
		argc = 1;
		if (uv->uv.fs.result == 0)
		{
			ZVAL_STRING(&params[0], req->ptr);
		}
		else
		{
			ZVAL_LONG(&params[0], uv->uv.fs.result);
		}
		break;

	case UV_FS_READ:
		argc = 2;
		if (uv->uv.fs.result >= 0)
		{
			ZVAL_STRINGL(&params[1], uv->buffer, uv->uv.fs.result);
		}
		else
		{
			ZVAL_LONG(&params[1], uv->uv.fs.result);
		}
		efree(uv->buffer);
		break;

	case UV_FS_SENDFILE:
		argc = 2;
		ZVAL_LONG(&params[1], uv->uv.fs.result);
		break;

	case UV_FS_WRITE:
		argc = 2;
		ZVAL_LONG(&params[1], uv->uv.fs.result);
		efree(uv->buffer);
		break;

	case UV_FS_UNKNOWN:
	case UV_FS_CUSTOM:
	default:
		argc = 0;
		php_error_docref(NULL, E_ERROR, "type; %d does not support yet.", uv->uv.fs.fs_type);
		break;
	}

	php_uv_do_callback2(&retval, uv, params, argc, PHP_UV_FS_CB TSRMLS_CC);

	PHP_UV_DEBUG_OBJ_DEL_REFCOUNT(uv_fs_cb, uv);
	for (i = 0; i < argc; i++)
	{
		zval_ptr_dtor(&params[i]);
	}

	zval_ptr_dtor(&retval);

	if (!Z_ISUNDEF(uv->fs_fd_alt))
	{
		zval_ptr_dtor(&uv->fs_fd_alt);
		ZVAL_UNDEF(&uv->fs_fd_alt);
	}

	uv_fs_req_cleanup(req);

	clean_uv_handle(uv);
	OBJ_RELEASE(&uv->std);
}

static zval php_uv_make_stat(const uv_stat_t *s)
{
	zval tmp = {0};
	array_init(&tmp);

	add_assoc_long_ex(&tmp, ZEND_STRL("dev"), s->st_dev);
	add_assoc_long_ex(&tmp, ZEND_STRL("ino"), s->st_ino);
	add_assoc_long_ex(&tmp, ZEND_STRL("mode"), s->st_mode);
	add_assoc_long_ex(&tmp, ZEND_STRL("nlink"), s->st_nlink);
	add_assoc_long_ex(&tmp, ZEND_STRL("uid"), s->st_uid);
	add_assoc_long_ex(&tmp, ZEND_STRL("gid"), s->st_gid);
	add_assoc_long_ex(&tmp, ZEND_STRL("rdev"), s->st_rdev);
	add_assoc_long_ex(&tmp, ZEND_STRL("size"), s->st_size);

#ifndef PHP_WIN32
	add_assoc_long_ex(&tmp, ZEND_STRL("blksize"), s->st_blksize);
	add_assoc_long_ex(&tmp, ZEND_STRL("blocks"), s->st_blocks);
#endif

	add_assoc_long_ex(&tmp, ZEND_STRL("atime"), s->st_atim.tv_sec);
	add_assoc_long_ex(&tmp, ZEND_STRL("mtime"), s->st_mtim.tv_sec);
	add_assoc_long_ex(&tmp, ZEND_STRL("ctime"), s->st_ctim.tv_sec);

	return tmp;
}

/* {{{ proto void uv_fs_open(UVLoop $loop, string $path, long $flag, long $mode, callable(long|resource $file_or_result) $callback)
 */
PHP_FUNCTION(uv_fs_open)
{
	php_uv_fs_common(UV_FS_OPEN, INTERNAL_FUNCTION_PARAM_PASSTHRU);
}
/* }}} */

/* {{{ proto void uv_fs_read(UVLoop $loop, resource $fd, long $offset, long $length, callable(resource $fd, string|long $read) $callback)
 */
PHP_FUNCTION(uv_fs_read)
{
	php_uv_fs_common(UV_FS_READ, INTERNAL_FUNCTION_PARAM_PASSTHRU);
}
/* }}} */

/* {{{ proto void uv_fs_close(UVLoop $loop, resource $fd[, callable(bool $success) $callback])
 */
PHP_FUNCTION(uv_fs_close)
{
	php_uv_fs_common(UV_FS_CLOSE, INTERNAL_FUNCTION_PARAM_PASSTHRU);
}
/* }}} */

/* {{{ proto void uv_fs_write(UVLoop $loop, resource $fd, string $buffer[, long $offset = -1[, callable(resource $fd, long $result) $callback]])
 */
PHP_FUNCTION(uv_fs_write)
{
	php_uv_fs_common(UV_FS_WRITE, INTERNAL_FUNCTION_PARAM_PASSTHRU);
}
/* }}} */

/* {{{ proto void uv_fs_fsync(UVLoop $loop, resource $fd[, callable(resource $fd, long $result) $callback])
 */
PHP_FUNCTION(uv_fs_fsync)
{
	php_uv_fs_common(UV_FS_FSYNC, INTERNAL_FUNCTION_PARAM_PASSTHRU);
}
/* }}} */

/* {{{ proto void uv_fs_fdatasync(UVLoop $loop, resource $fd[, callable(resource $fd, long $result) $callback])
 */
PHP_FUNCTION(uv_fs_fdatasync)
{
	php_uv_fs_common(UV_FS_FDATASYNC, INTERNAL_FUNCTION_PARAM_PASSTHRU);
}
/* }}} */

/* {{{ proto void uv_fs_ftruncate(UVLoop $loop, resource $fd, long $offset[, callable(resource $fd, long $result) $callback])
 */
PHP_FUNCTION(uv_fs_ftruncate)
{
	php_uv_fs_common(UV_FS_FTRUNCATE, INTERNAL_FUNCTION_PARAM_PASSTHRU);
}
/* }}} */

/* {{{ proto void uv_fs_mkdir(UVLoop $loop, string $path, long $mode[, callable(long $result) $callback])
 */
PHP_FUNCTION(uv_fs_mkdir)
{
	php_uv_fs_common(UV_FS_MKDIR, INTERNAL_FUNCTION_PARAM_PASSTHRU);
}
/* }}} */

/* {{{ proto void uv_fs_rmdir(UVLoop $loop, string $path[, callable(long $result) $callback])
 */
PHP_FUNCTION(uv_fs_rmdir)
{
	php_uv_fs_common(UV_FS_RMDIR, INTERNAL_FUNCTION_PARAM_PASSTHRU);
}
/* }}} */

/* {{{ proto void uv_fs_unlink(UVLoop $loop, string $path[, callable(long $result) $callback])
 */
PHP_FUNCTION(uv_fs_unlink)
{
	php_uv_fs_common(UV_FS_UNLINK, INTERNAL_FUNCTION_PARAM_PASSTHRU);
}
/* }}} */

/* {{{ proto void uv_fs_rename(UVLoop $loop, string $from, string $to[, callable(long $result) $callback])
 */
PHP_FUNCTION(uv_fs_rename)
{
	php_uv_fs_common(UV_FS_RENAME, INTERNAL_FUNCTION_PARAM_PASSTHRU);
}
/* }}} */

/* {{{ proto void uv_fs_utime(UVLoop $loop, string $path, long $utime, long $atime[, callable(long $result) $callback])
 */
PHP_FUNCTION(uv_fs_utime)
{
	php_uv_fs_common(UV_FS_UTIME, INTERNAL_FUNCTION_PARAM_PASSTHRU);
}
/* }}} */

/* {{{ proto void uv_fs_futime(UVLoop $loop, zval $fd, long $utime, long $atime[, callable(long $result) $callback])
 */
PHP_FUNCTION(uv_fs_futime)
{
	php_uv_fs_common(UV_FS_FUTIME, INTERNAL_FUNCTION_PARAM_PASSTHRU);
}
/* }}} */

/* {{{ proto void uv_fs_chmod(UVLoop $loop, string $path, long $mode[, callable(long $result) $callback])
 */
PHP_FUNCTION(uv_fs_chmod)
{
	php_uv_fs_common(UV_FS_CHMOD, INTERNAL_FUNCTION_PARAM_PASSTHRU);
}
/* }}} */

/* {{{ proto void uv_fs_fchmod(UVLoop $loop, zval $fd, long $mode[, callable(long $result) $callback])
 */
PHP_FUNCTION(uv_fs_fchmod)
{
	php_uv_fs_common(UV_FS_FCHMOD, INTERNAL_FUNCTION_PARAM_PASSTHRU);
}
/* }}} */

/* {{{ proto void uv_fs_chown(UVLoop $loop, string $path, long $uid, long $gid[, callable(long $result) $callback])
 */
PHP_FUNCTION(uv_fs_chown)
{
	php_uv_fs_common(UV_FS_CHOWN, INTERNAL_FUNCTION_PARAM_PASSTHRU);
}
/* }}} */

/* {{{ proto void uv_fs_fchown(UVLoop $loop, zval $fd, long $uid, $long $gid[, callable(long $result) $callback])
 */
PHP_FUNCTION(uv_fs_fchown)
{
	php_uv_fs_common(UV_FS_FCHOWN, INTERNAL_FUNCTION_PARAM_PASSTHRU);
}
/* }}} */

/* {{{ proto void uv_fs_link(UVLoop $loop, string $from, string $to[, callable(long $result) $callback])
 */
PHP_FUNCTION(uv_fs_link)
{
	php_uv_fs_common(UV_FS_LINK, INTERNAL_FUNCTION_PARAM_PASSTHRU);
}
/* }}} */

/* {{{ proto void uv_fs_symlink(UVLoop $loop, string $from, string $to, long $flags[, callable(long $result) $callback])
 */
PHP_FUNCTION(uv_fs_symlink)
{
	php_uv_fs_common(UV_FS_SYMLINK, INTERNAL_FUNCTION_PARAM_PASSTHRU);
}
/* }}} */

/* {{{ proto void uv_fs_readlink(UVLoop $loop, string $path, callable(string|long $result_or_link_contents) $callback)
 */
PHP_FUNCTION(uv_fs_readlink)
{
	php_uv_fs_common(UV_FS_READLINK, INTERNAL_FUNCTION_PARAM_PASSTHRU);
}
/* }}} */

/* {{{ proto void uv_fs_stat(UVLoop $loop, string $path, callable(long|array $result_or_stat) $callback)
 */
PHP_FUNCTION(uv_fs_stat)
{
	php_uv_fs_common(UV_FS_STAT, INTERNAL_FUNCTION_PARAM_PASSTHRU);
}
/* }}} */

/* {{{ proto void uv_fs_lstat(UVLoop $loop, string $path, callable(long|array $result_or_stat) $callback)
 */
PHP_FUNCTION(uv_fs_lstat)
{
	php_uv_fs_common(UV_FS_LSTAT, INTERNAL_FUNCTION_PARAM_PASSTHRU);
}
/* }}} */

/* {{{ proto void uv_fs_fstat(UVLoop $loop, resource $fd, callable(resource $fd, array $stat) $callback)
 */
PHP_FUNCTION(uv_fs_fstat)
{
	php_uv_fs_common(UV_FS_FSTAT, INTERNAL_FUNCTION_PARAM_PASSTHRU);
}
/* }}} */

/* {{{ proto void uv_fs_readdir(UVLoop $loop, string $path, callable(long|array $result_or_dir_contents) $callback[, long $flags = 0])
 */
PHP_FUNCTION(uv_fs_readdir)
{
	php_error_docref(NULL, E_DEPRECATED, "Use uv_fs_scandir() instead of uv_fs_readdir()");
	php_uv_fs_common(UV_FS_SCANDIR, INTERNAL_FUNCTION_PARAM_PASSTHRU);
}
/* }}} */

/* {{{ proto void uv_fs_scandir(UVLoop $loop, string $path, callable(long|array $result_or_dir_contents) $callback[, long $flags = 0])
 *  */
PHP_FUNCTION(uv_fs_scandir)
{
	php_uv_fs_common(UV_FS_SCANDIR, INTERNAL_FUNCTION_PARAM_PASSTHRU);
}
/* }}} */

/* {{{ proto void uv_fs_sendfile(UVLoop $loop, resource $in_fd, resource $out_fd, long $offset, long $length[, callable(resource $out_fd, long $result) $callback]) */
PHP_FUNCTION(uv_fs_sendfile)
{
	php_uv_fs_common(UV_FS_SENDFILE, INTERNAL_FUNCTION_PARAM_PASSTHRU);
}
/* }}} */
