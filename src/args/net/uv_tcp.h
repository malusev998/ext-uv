#pragma once

#include <php.h>

/* {{{ proto UVTcp uv_tcp_init([UVLoop $loop]) */
PHP_FUNCTION(uv_tcp_init);
/* }}} */

/* {{{ proto void uv_tcp_bind(UVTcp $uv_tcp, UVSockAddr $uv_sockaddr) */
PHP_FUNCTION(uv_tcp_bind);
/* }}} */

/* {{{ proto void uv_tcp_bind6(UVTcp $uv_tcp, UVSockAddr $uv_sockaddr) */
PHP_FUNCTION(uv_tcp_bind6);
/* }}} */

/* {{{ proto int|false uv_tcp_open(UVTcp $handle, long|resource $tcpfd) */
PHP_FUNCTION(uv_tcp_open);
/* }}} */

/* {{{ proto void uv_tcp_nodelay(UVTcp $handle, bool $enable) */
PHP_FUNCTION(uv_tcp_nodelay);
/* }}} */

/* {{{ proto void uv_tcp_connect(UVTcp $handle, UVSockAddr $sock_addr, callable(UVTcp $handle, long $status) $callback) */
PHP_FUNCTION(uv_tcp_connect);
/* }}} */

/* {{{ proto void uv_tcp_connect6(UVTcp $handle, UVSockAddrIPv6 $ipv6_addr, callable(UVTcp $handle, long $status) $callback) */
PHP_FUNCTION(uv_tcp_connect6);
/* }}} */

/* {{{ proto void uv_tcp_simultaneous_accepts(UVTcp $handle, bool $enable) */
PHP_FUNCTION(uv_tcp_simultaneous_accepts);
/* }}} */

/* {{{ proto string uv_tcp_getsockname(UVTcp $uv_sock) */
PHP_FUNCTION(uv_tcp_getsockname);
/* }}} */

/* {{{ proto string uv_tcp_getpeername(UVTcp $uv_sock) */
PHP_FUNCTION(uv_tcp_getpeername);
/* }}} */
