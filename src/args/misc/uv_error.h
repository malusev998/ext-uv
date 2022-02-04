#pragma once

#include <php.h>

/* {{{ proto string uv_err_name(long $error_code) */
PHP_FUNCTION(uv_err_name);
/* }}} */

/* {{{ proto string uv_strerror(long $error_code) */
PHP_FUNCTION(uv_strerror);
/* }}} */
