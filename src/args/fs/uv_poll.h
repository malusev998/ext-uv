#pragma once

#include <php.h>

/* {{{ proto UVPoll uv_poll_init(UVLoop $loop, resource $fd) */
PHP_FUNCTION(uv_poll_init);
/* }}} */

/* {{{ proto void uv_poll_start(UVPoll $handle, long $events, callable(UVPoll $handle, long $status, long $events, resource $fd) $callback) */
PHP_FUNCTION(uv_poll_start);
/* }}} */

/* {{{ proto void uv_poll_stop(UVPoll $poll) */
PHP_FUNCTION(uv_poll_stop);
/* }}} */

