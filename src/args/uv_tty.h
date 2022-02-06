#pragma once

#include <php.h>

/* {{{ proto UVTty uv_tty_init(UVLoop $loop, resource $fd, long $readable) */
PHP_FUNCTION(uv_tty_init);
/* }}} */

/* {{{ proto long uv_tty_get_winsize(UVTty $tty, long &$width, long &$height) */
PHP_FUNCTION(uv_tty_get_winsize);
/* }}} */

/* {{{ proto long uv_tty_set_mode(UVTty $tty, long $mode) */
PHP_FUNCTION(uv_tty_set_mode);
/* }}} */

/* {{{ proto void uv_tty_reset_mode(void) */
PHP_FUNCTION(uv_tty_reset_mode);
/* }}} */
