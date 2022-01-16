#include <php.h>
#include <zend_smart_str.h>

#include "parsing.h"

ZEND_COLD zend_string* php_uv_concat_ce_names(zend_class_entry* ce, zend_class_entry* next, ...) {
	va_list va;
	smart_str buf = { 0 };

	va_start(va, next);

	if (!next) {
		return zend_string_copy(ce->name);
	}

	goto start;
	do {
		if (next) {
			smart_str_appends(&buf, ", ");
		}
		else {
			smart_str_appends(&buf, " or ");
		}
	start:
		smart_str_append(&buf, ce->name);
		ce = next;
		next = (zend_class_entry*)va_arg(va, zend_class_entry*);
	} while (next);

	va_end(va);

	smart_str_0(&buf);
	return buf.s;
}

/* gcc complains: sorry, unimplemented: function ‘uv_parse_arg_object’ can never be inlined because it uses variable argument lists */
#ifdef __clang__
zend_always_inline int uv_parse_arg_object(zval* arg, zval** dest, int check_null, zend_class_entry* ce, ...) {
#else
int uv_parse_arg_object(zval * arg, zval * *dest, int check_null, zend_class_entry * ce, ...) {
#endif
	if (EXPECTED(Z_TYPE_P(arg) == IS_OBJECT)) {
		va_list va;
		zend_class_entry* argce = Z_OBJCE_P(arg);
		va_start(va, ce);
		do {
			if (instanceof_function(argce, ce)) {
				*dest = arg;
				return 1;
			}
			ce = (zend_class_entry*)va_arg(va, zend_class_entry*);
		} while (ce);
	}
	else if (check_null && EXPECTED(Z_TYPE_P(arg) == IS_NULL)) {
		*dest = NULL;
		return 1;
	}
	return 0;
}