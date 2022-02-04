#pragma once

#include <php.h>

#include "uv_tcp.h"
#include "uv_udp.h"
#include "uv_ip.h"

/* {{{ proto void uv_accept<T = UVTcp|UVPipe>(T $server, T $client)*/
PHP_FUNCTION(uv_accept);
/* }}} */

/* {{{ proto void uv_listen<T = UVTcp|UVPipe>(T $handle, long $backlog, callable(T $handle, long $status) $callback) */
PHP_FUNCTION(uv_listen);
/* }}} */
