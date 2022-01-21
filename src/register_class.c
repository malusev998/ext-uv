#include <php.h>
#include <Zend/zend_interfaces.h>

#include "types.h"
#include "register.h"

zend_class_entry* uv_ce;
zend_object_handlers uv_handlers;

static zend_function_entry php_uv_empty_methods[] = {
	{0},
};

static zend_object* php_uv_create_uv(zend_class_entry* ce) {
	php_uv_t* uv = emalloc(sizeof(php_uv_t));
	zend_object_std_init(&uv->std, ce);
	uv->std.handlers = &uv_handlers;

	for (int i = 0; i < PHP_UV_CB_MAX; i++) {			
		uv->callback[i] = NULL; 
	} 

	ZVAL_UNDEF(&uv->fs_fd); 
	ZVAL_UNDEF(&uv->fs_fd_alt);

	uv->uv.handle.data = uv;

	return &uv->std;
}

zend_class_entry* php_uv_register_internal_class_ex(const char* name, zend_class_entry* parent) {
	zend_class_entry ce = { 0 }, * new;

	ce.name = zend_new_interned_string(zend_string_init(name, strlen(name), 1));
	ce.info.internal.builtin_functions = php_uv_empty_methods;
	new = zend_register_internal_class_ex(&ce, parent);
#if PHP_VERSION_ID < 80100
	new->serialize = zend_class_serialize_deny;
	new->unserialize = zend_class_unserialize_deny;
#endif
	new->ce_flags |= ZEND_ACC_FINAL;
#if PHP_VERSION_ID >= 80100
	new->ce_flags |= ZEND_ACC_NOT_SERIALIZABLE;
#endif
	new->create_object = php_uv_create_uv;

	return new;
}

zend_class_entry* php_uv_register_internal_class(const char* name) {
	return php_uv_register_internal_class_ex(name, NULL);
}
