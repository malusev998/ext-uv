#pragma once

#include <php.h>

/* {{{ proto array uv_cpu_info(void) */
PHP_FUNCTION(uv_cpu_info);
/* }}} */

/* {{{ proto array uv_loadavg(void) */
PHP_FUNCTION(uv_loadavg);
/* }}} */

/* {{{ proto double uv_uptime(void) */
PHP_FUNCTION(uv_uptime);
/* }}} */
