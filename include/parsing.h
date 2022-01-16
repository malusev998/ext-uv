#ifndef PHP_UV_PARSING_H
#define PHP_UV_PARSING_H

ZEND_COLD zend_string* php_uv_concat_ce_names(zend_class_entry* ce, zend_class_entry* next, ...);
int uv_parse_arg_object(zval* arg, zval** dest, int check_null, zend_class_entry* ce, ...);

#define uv_zend_wrong_parameter_class_error(throw, ...) zend_wrong_parameter_class_error(__VA_ARGS__)
#define UV_PARAM_PROLOGUE Z_PARAM_PROLOGUE(0, 0)
#define zend_internal_type_error(strict_types, ...) zend_type_error(__VA_ARGS__)

#define UV_PARAM_OBJ_EX(dest, type, check_null, ce, ...) \
	{ \
		zval *zv; \
		UV_PARAM_PROLOGUE \
		if (UNEXPECTED(!uv_parse_arg_object(_arg, &zv, check_null, ce, ##__VA_ARGS__, NULL))) { \
			if (!(_flags & ZEND_PARSE_PARAMS_QUIET)) { \
				zend_string *names = php_uv_concat_ce_names(ce, ##__VA_ARGS__, NULL); \
				uv_zend_wrong_parameter_class_error(_flags & ZEND_PARSE_PARAMS_THROW, _i, ZSTR_VAL(names), _arg); \
				zend_string_release(names); \
			} \
			_error_code = ZPP_ERROR_FAILURE; \
			break; \
		} \
		if (GC_FLAGS(Z_OBJ_P(zv)) & IS_OBJ_DESTRUCTOR_CALLED) { \
			if (!(_flags & ZEND_PARSE_PARAMS_QUIET)) { \
				php_error_docref(NULL, E_WARNING, "passed %s handle is already closed", ZSTR_VAL(Z_OBJCE_P(_arg)->name)); \
			} \
			_error_code = ZPP_ERROR_FAILURE; \
			break; \
		} \
		dest = zv == NULL ? NULL : (type *) Z_OBJ_P(zv); \
	}

#define UV_PARAM_OBJ(dest, type, ...) UV_PARAM_OBJ_EX(dest, type, 0, ##__VA_ARGS__, NULL)
#define UV_PARAM_OBJ_NULL(dest, type, ...) UV_PARAM_OBJ_EX(dest, type, 1, ##__VA_ARGS__, NULL)


#endif
