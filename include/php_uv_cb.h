#pragma once

#include <php.h>

#include "php_uv.h"

void php_uv_cb_init(php_uv_cb_t **result, php_uv_t *uv, zend_fcall_info *fci, zend_fcall_info_cache *fcc, enum php_uv_callback_type type);
int php_uv_do_callback2(zval *retval_ptr, php_uv_t *uv, zval *params, int param_count, enum php_uv_callback_type type TSRMLS_DC);
