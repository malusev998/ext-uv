#pragma once

#include <php.h>

#include "uv_error.h"
#include "uv_memory.h"
#include "uv_cpu.h"

/* {{{ proto long uv_guess_handle(resource $uv) */
PHP_FUNCTION(uv_guess_handle);
/* }}} */

/* {{{ proto long uv_hrtime(void) */
PHP_FUNCTION(uv_hrtime);
/* }}} */
