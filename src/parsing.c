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
