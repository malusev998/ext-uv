#pragma once

#include <php.h>

/* {{{ proto string uv_ip4_name(UVSockAddr $address) */
PHP_FUNCTION(uv_ip4_name);
/* }}} */

/* {{{ proto string uv_ip6_name(UVSockAddr $address) */
PHP_FUNCTION(uv_ip6_name);
/* }}} */

/* {{{ proto UVSockAddrIPv4 uv_ip4_addr(string $ipv4_addr, long $port)*/
PHP_FUNCTION(uv_ip4_addr);
/* }}} */

/* {{{ proto UVSockAddrIPv6 uv_ip6_addr(string $ipv6_addr, long $port) */
PHP_FUNCTION(uv_ip6_addr);
/* }}} */

/* {{{ proto void uv_getaddrinfo(UVLoop $loop, callable(array|long $addresses_or_error) $callback, string $node, string $service[, array $hints = []]) */
PHP_FUNCTION(uv_getaddrinfo);
/* }}} */

/* {{{ proto array uv_interface_addresses(void) */
PHP_FUNCTION(uv_interface_addresses);
/* }}} */
