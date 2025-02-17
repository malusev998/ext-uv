#pragma once

#include <php.h>

ZEND_BEGIN_ARG_INFO_EX(arginfo_void, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_run, 0, 0, 0)
ZEND_ARG_INFO(0, loop)
ZEND_ARG_INFO(0, run_mode)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_stop, 0, 0, 0)
ZEND_ARG_INFO(0, loop)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_loop_delete, 0, 0, 1)
ZEND_ARG_INFO(0, loop)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_now, 0, 0, 0)
ZEND_ARG_INFO(0, loop)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_tcp_connect, 0, 0, 2)
ZEND_ARG_INFO(0, resource)
ZEND_ARG_INFO(0, sock_addr)
ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_tcp_connect6, 0, 0, 2)
ZEND_ARG_INFO(0, resource)
ZEND_ARG_INFO(0, ipv6_addr)
ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_tcp_init, 0, 0, 0)
ZEND_ARG_INFO(0, loop)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_listen, 0, 0, 3)
ZEND_ARG_INFO(0, resource)
ZEND_ARG_INFO(0, backlog)
ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_accept, 0, 0, 2)
ZEND_ARG_INFO(0, server)
ZEND_ARG_INFO(0, client)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_read_start, 0, 0, 2)
ZEND_ARG_INFO(0, server)
ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_read_stop, 0, 0, 1)
ZEND_ARG_INFO(0, server)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_write, 0, 0, 3)
ZEND_ARG_INFO(0, client)
ZEND_ARG_INFO(0, data)
ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_write2, 0, 0, 4)
ZEND_ARG_INFO(0, client)
ZEND_ARG_INFO(0, data)
ZEND_ARG_INFO(0, send)
ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_strerror, 0, 0, 1)
ZEND_ARG_INFO(0, error)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_err_name, 0, 0, 1)
ZEND_ARG_INFO(0, error)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_timer_init, 0, 0, 0)
ZEND_ARG_INFO(0, loop)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_idle_stop, 0, 0, 1)
ZEND_ARG_INFO(0, idle)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_timer_start, 0, 0, 3)
ZEND_ARG_INFO(0, timer)
ZEND_ARG_INFO(0, timeout)
ZEND_ARG_INFO(0, repeat)
ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_timer_stop, 0, 0, 1)
ZEND_ARG_INFO(0, timer)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_timer_again, 0, 0, 1)
ZEND_ARG_INFO(0, timer)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_timer_set_repeat, 0, 0, 2)
ZEND_ARG_INFO(0, timer)
ZEND_ARG_INFO(0, timeout)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_timer_get_repeat, 0, 0, 1)
ZEND_ARG_INFO(0, timer)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_idle_start, 0, 0, 2)
ZEND_ARG_INFO(0, timer)
ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_tcp_open, 0, 0, 2)
ZEND_ARG_INFO(0, resource)
ZEND_ARG_INFO(0, tcpfd)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_tcp_bind, 0, 0, 2)
ZEND_ARG_INFO(0, resource)
ZEND_ARG_INFO(0, address)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_tcp_bind6, 0, 0, 2)
ZEND_ARG_INFO(0, resource)
ZEND_ARG_INFO(0, address)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_shutdown, 0, 0, 2)
ZEND_ARG_INFO(0, stream)
ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_close, 0, 0, 1)
ZEND_ARG_INFO(0, stream)
ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_idle_init, 0, 0, 0)
ZEND_ARG_INFO(0, loop)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_update_time, 0, 0, 0)
ZEND_ARG_INFO(0, loop)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_is_active, 0, 0, 1)
ZEND_ARG_INFO(0, handle)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_is_closing, 0, 0, 1)
ZEND_ARG_INFO(0, handle)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_is_readable, 0, 0, 1)
ZEND_ARG_INFO(0, handle)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_is_writable, 0, 0, 1)
ZEND_ARG_INFO(0, handle)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_walk, 0, 0, 2)
ZEND_ARG_INFO(0, loop)
ZEND_ARG_INFO(0, callback)
ZEND_ARG_INFO(0, opaque)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_guess_handle, 0, 0, 1)
ZEND_ARG_INFO(0, fd)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_ref, 0, 0, 1)
ZEND_ARG_INFO(0, loop)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_unref, 0, 0, 1)
ZEND_ARG_INFO(0, loop)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_tcp_nodelay, 0, 0, 2)
ZEND_ARG_INFO(0, tcp)
ZEND_ARG_INFO(0, enabled)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_ip4_addr, 0, 0, 2)
ZEND_ARG_INFO(0, address)
ZEND_ARG_INFO(0, port)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_ip6_addr, 0, 0, 2)
ZEND_ARG_INFO(0, address)
ZEND_ARG_INFO(0, port)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_udp_init, 0, 0, 0)
ZEND_ARG_INFO(0, loop)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_udp_open, 0, 0, 2)
ZEND_ARG_INFO(0, resource)
ZEND_ARG_INFO(0, udpfd)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_udp_bind, 0, 0, 2)
ZEND_ARG_INFO(0, resource)
ZEND_ARG_INFO(0, address)
ZEND_ARG_INFO(0, flags)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_udp_bind6, 0, 0, 2)
ZEND_ARG_INFO(0, resource)
ZEND_ARG_INFO(0, address)
ZEND_ARG_INFO(0, flags)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_udp_recv_start, 0, 0, 2)
ZEND_ARG_INFO(0, server)
ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_udp_recv_stop, 0, 0, 1)
ZEND_ARG_INFO(0, server)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_udp_set_multicast_loop, 0, 0, 2)
ZEND_ARG_INFO(0, server)
ZEND_ARG_INFO(0, enabled)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_udp_set_multicast_ttl, 0, 0, 2)
ZEND_ARG_INFO(0, server)
ZEND_ARG_INFO(0, ttl)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_udp_set_broadcast, 0, 0, 2)
ZEND_ARG_INFO(0, server)
ZEND_ARG_INFO(0, enabled)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_udp_send, 0, 0, 3)
ZEND_ARG_INFO(0, server)
ZEND_ARG_INFO(0, buffer)
ZEND_ARG_INFO(0, address)
ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_udp_send6, 0, 0, 3)
ZEND_ARG_INFO(0, server)
ZEND_ARG_INFO(0, buffer)
ZEND_ARG_INFO(0, address)
ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_pipe_open, 0, 0, 2)
ZEND_ARG_INFO(0, file)
ZEND_ARG_INFO(0, pipe)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_pipe_init, 0, 0, 0)
ZEND_ARG_INFO(0, file)
ZEND_ARG_INFO(0, ipc)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_pipe_bind, 0, 0, 2)
ZEND_ARG_INFO(0, handle)
ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_pipe_connect, 0, 0, 3)
ZEND_ARG_INFO(0, handle)
ZEND_ARG_INFO(0, name)
ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_pipe_pending_count, 0, 0, 1)
ZEND_ARG_INFO(0, handle)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_pipe_pending_type, 0, 0, 1)
ZEND_ARG_INFO(0, handle)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_pipe_pending_instances, 0, 0, 2)
ZEND_ARG_INFO(0, handle)
ZEND_ARG_INFO(0, count)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_getaddrinfo, 0, 0, 4)
ZEND_ARG_INFO(0, loop)
ZEND_ARG_INFO(0, callback)
ZEND_ARG_INFO(0, node)
ZEND_ARG_INFO(0, service)
ZEND_ARG_INFO(0, hints)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_spawn, 0, 0, 7)
ZEND_ARG_INFO(0, loop)
ZEND_ARG_INFO(0, command)
ZEND_ARG_INFO(0, args)
ZEND_ARG_INFO(0, stdio)
ZEND_ARG_INFO(0, cwd)
ZEND_ARG_INFO(0, env)
ZEND_ARG_INFO(0, callback)
ZEND_ARG_INFO(0, flags)
ZEND_ARG_INFO(0, options)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_kill, 0, 0, 2)
ZEND_ARG_INFO(0, pid)
ZEND_ARG_INFO(0, signal)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_process_kill, 0, 0, 2)
ZEND_ARG_INFO(0, process)
ZEND_ARG_INFO(0, signal)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_process_get_pid, 0, 0, 1)
ZEND_ARG_INFO(0, process)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_chdir, 0, 0, 1)
ZEND_ARG_INFO(0, dir)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_tty_get_winsize, 0, 0, 3)
ZEND_ARG_INFO(0, tty)
ZEND_ARG_INFO(1, width)
ZEND_ARG_INFO(1, height)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_tty_init, 0, 0, 3)
ZEND_ARG_INFO(0, loop)
ZEND_ARG_INFO(0, fd)
ZEND_ARG_INFO(0, readable)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_fs_event_init, 0, 0, 3)
ZEND_ARG_INFO(0, loop)
ZEND_ARG_INFO(0, path)
ZEND_ARG_INFO(0, callback)
ZEND_ARG_INFO(0, flags)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_fs_sendfile, 0, 0, 5)
ZEND_ARG_INFO(0, loop)
ZEND_ARG_INFO(0, in)
ZEND_ARG_INFO(0, out)
ZEND_ARG_INFO(0, offset)
ZEND_ARG_INFO(0, length)
ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_fs_readdir, 0, 0, 3)
ZEND_ARG_INFO(0, loop)
ZEND_ARG_INFO(0, path)
ZEND_ARG_INFO(0, flags)
ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_fs_scandir, 0, 0, 3)
ZEND_ARG_INFO(0, loop)
ZEND_ARG_INFO(0, path)
ZEND_ARG_INFO(0, flags)
ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_fs_fstat, 0, 0, 2)
ZEND_ARG_INFO(0, loop)
ZEND_ARG_INFO(0, fd)
ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_fs_lstat, 0, 0, 2)
ZEND_ARG_INFO(0, loop)
ZEND_ARG_INFO(0, path)
ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_fs_stat, 0, 0, 2)
ZEND_ARG_INFO(0, loop)
ZEND_ARG_INFO(0, path)
ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_fs_readlink, 0, 0, 2)
ZEND_ARG_INFO(0, loop)
ZEND_ARG_INFO(0, path)
ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_fs_symlink, 0, 0, 4)
ZEND_ARG_INFO(0, loop)
ZEND_ARG_INFO(0, from)
ZEND_ARG_INFO(0, to)
ZEND_ARG_INFO(0, callback)
ZEND_ARG_INFO(0, flags)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_fs_link, 0, 0, 3)
ZEND_ARG_INFO(0, loop)
ZEND_ARG_INFO(0, from)
ZEND_ARG_INFO(0, to)
ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_fs_fchown, 0, 0, 4)
ZEND_ARG_INFO(0, loop)
ZEND_ARG_INFO(0, fd)
ZEND_ARG_INFO(0, uid)
ZEND_ARG_INFO(0, gid)
ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_fs_chown, 0, 0, 4)
ZEND_ARG_INFO(0, loop)
ZEND_ARG_INFO(0, path)
ZEND_ARG_INFO(0, uid)
ZEND_ARG_INFO(0, gid)
ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_fs_fchmod, 0, 0, 3)
ZEND_ARG_INFO(0, loop)
ZEND_ARG_INFO(0, fd)
ZEND_ARG_INFO(0, mode)
ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_fs_chmod, 0, 0, 3)
ZEND_ARG_INFO(0, loop)
ZEND_ARG_INFO(0, path)
ZEND_ARG_INFO(0, mode)
ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_fs_futime, 0, 0, 4)
ZEND_ARG_INFO(0, loop)
ZEND_ARG_INFO(0, fd)
ZEND_ARG_INFO(0, utime)
ZEND_ARG_INFO(0, atime)
ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_fs_utime, 0, 0, 4)
ZEND_ARG_INFO(0, loop)
ZEND_ARG_INFO(0, path)
ZEND_ARG_INFO(0, utime)
ZEND_ARG_INFO(0, atime)
ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_fs_open, 0, 0, 4)
ZEND_ARG_INFO(0, loop)
ZEND_ARG_INFO(0, path)
ZEND_ARG_INFO(0, flag)
ZEND_ARG_INFO(0, mode)
ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_fs_read, 0, 0, 2)
ZEND_ARG_INFO(0, loop)
ZEND_ARG_INFO(0, fd)
ZEND_ARG_INFO(0, offset)
ZEND_ARG_INFO(0, size)
ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_fs_close, 0, 0, 2)
ZEND_ARG_INFO(0, loop)
ZEND_ARG_INFO(0, fd)
ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_fs_write, 0, 0, 4)
ZEND_ARG_INFO(0, loop)
ZEND_ARG_INFO(0, fd)
ZEND_ARG_INFO(0, buffer)
ZEND_ARG_INFO(0, offset)
ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_fs_fsync, 0, 0, 2)
ZEND_ARG_INFO(0, loop)
ZEND_ARG_INFO(0, fd)
ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_fs_fdatasync, 0, 0, 2)
ZEND_ARG_INFO(0, loop)
ZEND_ARG_INFO(0, fd)
ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_fs_ftruncate, 0, 0, 3)
ZEND_ARG_INFO(0, loop)
ZEND_ARG_INFO(0, fd)
ZEND_ARG_INFO(0, offset)
ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_fs_mkdir, 0, 0, 3)
ZEND_ARG_INFO(0, loop)
ZEND_ARG_INFO(0, path)
ZEND_ARG_INFO(0, mode)
ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_fs_rmdir, 0, 0, 2)
ZEND_ARG_INFO(0, loop)
ZEND_ARG_INFO(0, path)
ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_fs_unlink, 0, 0, 2)
ZEND_ARG_INFO(0, loop)
ZEND_ARG_INFO(0, path)
ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_fs_rename, 0, 0, 3)
ZEND_ARG_INFO(0, loop)
ZEND_ARG_INFO(0, from)
ZEND_ARG_INFO(0, to)
ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_rwlock_rdlock, 0, 0, 1)
ZEND_ARG_INFO(0, handle)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_rwlock_tryrdlock, 0, 0, 1)
ZEND_ARG_INFO(0, handle)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_rwlock_rdunlock, 0, 0, 1)
ZEND_ARG_INFO(0, handle)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_rwlock_wrlock, 0, 0, 1)
ZEND_ARG_INFO(0, handle)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_rwlock_trywrlock, 0, 0, 1)
ZEND_ARG_INFO(0, handle)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_rwlock_wrunlock, 0, 0, 1)
ZEND_ARG_INFO(0, handle)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_mutex_lock, 0, 0, 1)
ZEND_ARG_INFO(0, handle)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_mutex_trylock, 0, 0, 1)
ZEND_ARG_INFO(0, handle)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_mutex_unlock, 0, 0, 1)
ZEND_ARG_INFO(0, handle)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_sem_init, 0, 0, 1)
ZEND_ARG_INFO(0, val)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_sem_post, 0, 0, 1)
ZEND_ARG_INFO(0, resource)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_sem_wait, 0, 0, 1)
ZEND_ARG_INFO(0, resource)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_sem_trywait, 0, 0, 1)
ZEND_ARG_INFO(0, resource)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_prepare_init, 0, 0, 0)
ZEND_ARG_INFO(0, loop)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_prepare_start, 0, 0, 2)
ZEND_ARG_INFO(0, handle)
ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_prepare_stop, 0, 0, 1)
ZEND_ARG_INFO(0, handle)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_check_init, 0, 0, 0)
ZEND_ARG_INFO(0, loop)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_check_start, 0, 0, 2)
ZEND_ARG_INFO(0, handle)
ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_check_stop, 0, 0, 1)
ZEND_ARG_INFO(0, handle)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_async_send, 0, 0, 1)
ZEND_ARG_INFO(0, handle)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_async_init, 0, 0, 2)
ZEND_ARG_INFO(0, loop)
ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_tcp_getsockname, 0, 0, 1)
ZEND_ARG_INFO(0, handle)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_tcp_getpeername, 0, 0, 1)
ZEND_ARG_INFO(0, handle)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_udp_getsockname, 0, 0, 1)
ZEND_ARG_INFO(0, handle)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_tcp_simultaneous_accepts, 0, 0, 2)
ZEND_ARG_INFO(0, handle)
ZEND_ARG_INFO(0, enable)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_udp_set_membership, 0, 0, 4)
ZEND_ARG_INFO(0, client)
ZEND_ARG_INFO(0, multicast_addr)
ZEND_ARG_INFO(0, interface_addr)
ZEND_ARG_INFO(0, membership)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_ip6_name, 0, 0, 1)
ZEND_ARG_INFO(0, handle)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_ip4_name, 0, 0, 1)
ZEND_ARG_INFO(0, handle)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_fs_poll_init, 0, 0, 0)
ZEND_ARG_INFO(0, loop)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_fs_poll_start, 0, 0, 4)
ZEND_ARG_INFO(0, handle)
ZEND_ARG_INFO(0, callback)
ZEND_ARG_INFO(0, path)
ZEND_ARG_INFO(0, interval)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_fs_poll_stop, 0, 0, 1)
ZEND_ARG_INFO(0, loop)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_poll_init, 0, 0, 2)
ZEND_ARG_INFO(0, loop)
ZEND_ARG_INFO(0, fd)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_poll_start, 0, 0, 3)
ZEND_ARG_INFO(0, handle)
ZEND_ARG_INFO(0, events)
ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_poll_stop, 0, 0, 1)
ZEND_ARG_INFO(0, handle)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_signal_init, 0, 0, 0)
ZEND_ARG_INFO(0, loop)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_signal_start, 0, 0, 3)
ZEND_ARG_INFO(0, sig_handle)
ZEND_ARG_INFO(0, sig_callback)
ZEND_ARG_INFO(0, sig_num)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_uv_signal_stop, 0, 0, 1)
ZEND_ARG_INFO(0, sig_handle)
ZEND_END_ARG_INFO()
