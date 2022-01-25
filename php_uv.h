#ifndef PHP_UV_H

#define PHP_UV_H

#define PHP_UV_EXTNAME "uv"
#define PHP_UV_VERSION "0.3.0"

#include <config.h>

#ifndef PHP_UV_DTRACE
	#define PHP_UV_DTRACE 0
#endif

#if PHP_UV_DTRACE >= 1
	#include <dtrace.h>
	#include <sys/sdt.h>
	#include "phpuv_dtrace.h"
	#define PHP_UV_PROBE(PROBE) PHPUV_TRACE_##PROBE();
#else
	#define PHP_UV_PROBE(PROBE)
#endif

#include "php.h"
#include "uv.h"

#include "php_network.h"
#include "php_streams.h"

typedef struct {
	int bsd_socket;
	int type;
	int error;
	int blocking;
	zval zstream;
	zend_object std;
} php_socket;

#include <Zend/zend.h>
#include <Zend/zend_compile.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_extensions.h>
#include <Zend/zend_globals.h>
#include <Zend/zend_hash.h>
#include <Zend/zend_list.h>
#include <Zend/zend_object_handlers.h>
#include <Zend/zend_variables.h>
#include <Zend/zend_vm.h>

#if PHP_VERSION_ID >= 80000
#define TSRMLS_C
#define TSRMLS_CC
#define TSRMLS_D
#define TSRMLS_DC
#define TSRMLS_FETCH_FROM_CTX(ctx)
#define TSRMLS_SET_CTX(ctx)
#endif

/* Define the entry point symbol
 * Zend will use when loading this module
 */
extern zend_module_entry uv_module_entry;
#define phpext_uv_ptr &uv_module_entry

extern zend_class_entry *uv_class_entry;

#include "types.h"

/* File/directory stat mode constants*/

#ifndef S_IFDIR
	#define S_IFDIR 0040000
#endif
#ifndef S_IFREG
	#define S_IFREG 0100000
#endif

// TODO: Remove global loop
ZEND_BEGIN_MODULE_GLOBALS(uv)
	php_uv_loop_t *default_loop;
ZEND_END_MODULE_GLOBALS(uv)


#define UV_G(v) (uv_globals.v)

#endif /* PHP_UV_H */
