#pragma once

#include <php.h>

/* {{{ proto void uv_queue_work(UVLoop $loop, callable() $callback, callable() $after_callback) */
PHP_FUNCTION(uv_queue_work);
/* }}} */
