#pragma once

#include <php.h>

// TODO: Add functions: uv_fs_event_start, uv_fs_event_stop, uv_fs_event_getpath

/* {{{ proto UVFsEvent uv_fs_event_init(UVLoop $loop, string $path, callable(UVFsEvent $handle, string|null $filename, long $events, long $status) $callback[, long $flags = 0]) */
PHP_FUNCTION(uv_fs_event_init);
/* }}} */
