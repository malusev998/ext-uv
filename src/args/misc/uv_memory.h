#pragma once

#include <php.h>

/* {{{ proto long uv_get_free_memory(void) */
PHP_FUNCTION(uv_get_free_memory);
/* }}} */

/* {{{ proto long uv_get_total_memory(void) */
PHP_FUNCTION(uv_get_total_memory);
/* }}} */

/* {{{ proto long uv_resident_set_memory(void) */
PHP_FUNCTION(uv_resident_set_memory);
/* }}} */
