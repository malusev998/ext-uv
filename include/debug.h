#ifndef PHP_UV_DEBUG_H
#define PHP_UV_DEBUG_H

#if PHP_UV_DEBUG>=1
	#define PHP_UV_DEBUG_PRINT(format, ...) fprintf(stderr, format, ## __VA_ARGS__)
#else
	#define PHP_UV_DEBUG_PRINT(format, ...)
#endif

#if PHP_UV_DEBUG>=1
	#define PHP_UV_DEBUG_OBJ_ADD_REFCOUNT(handler, uv) \
	{ \
		PHP_UV_DEBUG_PRINT("# %s add(%p - %s): %u->%u\n", #handler, uv, ZSTR_VAL(uv->std.ce->name), GC_REFCOUNT(&(uv)->std) - 1, GC_REFCOUNT(&(uv)->std)); \
	}
	#define PHP_UV_DEBUG_OBJ_DEL_REFCOUNT(handler, uv) \
	{ \
		PHP_UV_DEBUG_PRINT("# %s del(%p - %s): %u->%u\n", #handler, uv, ZSTR_VAL(uv->std.ce->name), GC_REFCOUNT(&(uv)->std), GC_REFCOUNT(&(uv)->std) - 1); \
	}
#else
	#define PHP_UV_DEBUG_OBJ_ADD_REFCOUNT(hander, uv)
	#define PHP_UV_DEBUG_OBJ_DEL_REFCOUNT(hander, uv)
#endif

#endif
