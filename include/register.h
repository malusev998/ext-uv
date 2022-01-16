#include <php.h>

#ifndef PHP_UV_REGISTER_CLASS_H
#define PHP_UV_REGISTER_CLASS_H

zend_class_entry* php_uv_register_internal_class_ex(const char* name, zend_class_entry* parent);
zend_class_entry* php_uv_register_internal_class(const char* name);

extern zend_class_entry* uv_ce;
extern zend_object_handlers uv_handlers;
#endif
