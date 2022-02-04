#pragma once

#include <php.h>

/* {{{ proto UVUdp uv_udp_init([UVLoop $loop]) */
PHP_FUNCTION(uv_udp_init);
/* }}} */

/* {{{ proto int|false uv_udp_open(UVUdp $handle, long|resource $udpfd) */
PHP_FUNCTION(uv_udp_open);
/* }}} */

/* {{{ proto void uv_udp_bind(UVUdp $resource, UVSockAddr $address[, long $flags = 0]) */
PHP_FUNCTION(uv_udp_bind);
/* }}} */

/* {{{ proto void uv_udp_bind6(UVUdp $resource, UVSockAddr $address[, long $flags = 0]) */
PHP_FUNCTION(uv_udp_bind6);
/* }}} */

/* {{{ proto void uv_udp_recv_start(UVUdp $handle, callable(UVUdp $handle, string|long $read, long $flags) $callback) */
PHP_FUNCTION(uv_udp_recv_start);
/* }}} */

/* {{{ proto void uv_udp_recv_stop(UVUdp $handle) */
PHP_FUNCTION(uv_udp_recv_stop);
/* }}} */

/* {{{ proto long uv_udp_set_membership(UVUdp $handle, string $multicast_addr, string $interface_addr, long $membership) */
PHP_FUNCTION(uv_udp_set_membership);
/* }}} */

/* {{{ proto void uv_udp_set_multicast_loop(UVUdp $handle, bool $enabled) */
PHP_FUNCTION(uv_udp_set_multicast_loop);
/* }}} */

/* {{{ proto void uv_udp_set_multicast_ttl(UVUdp $handle, long $ttl) */
PHP_FUNCTION(uv_udp_set_multicast_ttl);
/* }}} */

/* {{{ proto void uv_udp_set_broadcast(UVUdp $handle, bool $enabled) */
PHP_FUNCTION(uv_udp_set_broadcast);
/* }}} */

/* {{{ proto void uv_udp_send(UVUdp $handle, string $data, UVSockAddr $uv_addr, callable(UVUdp $handle, long $status) $callback) */
PHP_FUNCTION(uv_udp_send);
/* }}} */

/* {{{ proto void uv_udp_send6(resource $handle, string $data, UVSockAddrIPv6 $uv_addr6, callable(UVUdp $handle, long $status) $callback) */
PHP_FUNCTION(uv_udp_send6);

/* {{{ proto string uv_udp_getsockname(UVUdp $uv_sock) */
PHP_FUNCTION(uv_udp_getsockname);
/* }}} */
