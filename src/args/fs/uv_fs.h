#pragma once

#include <php.h>

#include "uv_fs_common.h"
#include "uv_fs_poll.h"
#include "uv_fs_event.h"
#include "uv_pipe.h"
#include "uv_stream.h"
#include "uv_poll.h"

/* {{{ proto UVStdio uv_stdio_new([UV|resource|long|null $fd[, long $flags = 0]]) */
PHP_FUNCTION(uv_stdio_new);
/* }}} */

/* {{{ proto void uv_fs_sendfile(UVLoop $loop, resource $in_fd, resource $out_fd, long $offset, long $length[, callable(resource $out_fd, long $result) $callback]) */
PHP_FUNCTION(uv_fs_sendfile);
/* }}} */

/* {{{ proto bool uv_chdir(string $directory) */
PHP_FUNCTION(uv_chdir);
/* }}} */

/* {{{ proto string uv_exepath(void) */
PHP_FUNCTION(uv_exepath);
/* }}} */

/* {{{ proto string uv_cwd(void) */
PHP_FUNCTION(uv_cwd);
/* }}} */
