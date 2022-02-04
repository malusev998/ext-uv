#pragma once

#include <php.h>

extern zend_object_handlers uv_default_handlers;
extern zend_class_entry *uv_ce;
extern zend_object_handlers uv_handlers;
extern zend_class_entry *uv_stream_ce;
extern zend_class_entry *uv_tcp_ce;
extern zend_class_entry *uv_udp_ce;
extern zend_class_entry *uv_pipe_ce;
extern zend_class_entry *uv_idle_ce;
extern zend_class_entry *uv_timer_ce;
extern zend_class_entry *uv_async_ce;
extern zend_class_entry *uv_addrinfo_ce;
extern zend_class_entry *uv_process_ce;
extern zend_class_entry *uv_prepare_ce;
extern zend_class_entry *uv_check_ce;
extern zend_class_entry *uv_work_ce;
extern zend_class_entry *uv_fs_ce;
extern zend_class_entry *uv_fs_event_ce;
extern zend_class_entry *uv_tty_ce;
extern zend_class_entry *uv_fs_poll_ce;
extern zend_class_entry *uv_poll_ce;
extern zend_class_entry *uv_signal_ce;
extern zend_class_entry *uv_loop_ce;
extern zend_object_handlers uv_loop_handlers;
extern zend_class_entry *uv_sockaddr_ce;
extern zend_class_entry *uv_sockaddr_ipv4_ce;
extern zend_class_entry *uv_sockaddr_ipv6_ce;
extern zend_class_entry *uv_lock_ce;
extern zend_object_handlers uv_lock_handlers;
extern zend_class_entry *uv_stdio_ce;
extern zend_object_handlers uv_stdio_handlers;
