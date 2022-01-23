#include <php.h>
#include <php_network.h>
#include <php_streams.h>

#include <uv.h>

#include "../fs.h"
#include "types.h"

static php_socket_t php_uv_zval_to_valid_poll_fd(zval *ptr) {
  php_socket_t fd = -1;
  php_stream *stream;
  php_socket *socket;
  /* TODO: is this correct on windows platform? */
  if (Z_TYPE_P(ptr) == IS_RESOURCE) {
    if ((stream = (php_stream *)zend_fetch_resource_ex(ptr, NULL,
                                                       php_file_le_stream()))) {
      /* make sure only valid resource streams are passed - plainfiles and most
       * php streams are invalid */
      if (stream->wrapper &&
          !strcmp((char *)stream->wrapper->wops->label, "PHP") &&
          (!stream->orig_path ||
           (strncmp(stream->orig_path, "php://std", sizeof("php://std") - 1) &&
            strncmp(stream->orig_path, "php://fd", sizeof("php://fd") - 1)))) {
        php_error_docref(
            NULL, E_WARNING,
            "invalid resource passed, this resource is not supported");
        return -1;
      }

      /* Some streams (specifically STDIO and encrypted streams) can be cast to
       * FDs */
      if (php_stream_cast(
              stream, PHP_STREAM_AS_FD_FOR_SELECT | PHP_STREAM_CAST_INTERNAL,
              (void *)&fd, 1) == SUCCESS &&
          fd >= 0) {
        if (stream->wrapper &&
            !strcmp((char *)stream->wrapper->wops->label, "plainfile")) {
          struct stat stat;
          fstat(fd, &stat);
          if (!S_ISFIFO(stat.st_mode)) {
            php_error_docref(
                NULL, E_WARNING,
                "invalid resource passed, this plain files are not supported");
            return -1;
          }
        }
        return fd;
      }

      fd = -1;
    } else {
      php_error_docref(NULL, E_WARNING, "unhandled resource type detected.");
      fd = -1;
    }
  } else if (socket_ce && Z_TYPE_P(ptr) == IS_OBJECT &&
             Z_OBJCE_P(ptr) == socket_ce &&
             (socket = (php_socket *)((char *)(Z_OBJ_P(ptr)) -
                                      XtOffsetOf(php_socket, std)))) {
    fd = socket->bsd_socket;
  }

  return fd;
}

static php_socket_t php_uv_zval_to_fd(zval *ptr) {
  php_socket_t fd = -1;
  php_stream *stream;
  php_socket *socket;
  /* TODO: is this correct on windows platform? */
  if (Z_TYPE_P(ptr) == IS_RESOURCE) {
    if ((stream = (php_stream *)zend_fetch_resource_ex(ptr, NULL,
                                                       php_file_le_stream()))) {
      if (php_stream_cast(stream, PHP_STREAM_AS_FD | PHP_STREAM_CAST_INTERNAL,
                          (void *)&fd, 1) != SUCCESS ||
          fd < 0) {
        fd = -1;
      }
    } else {
      php_error_docref(NULL, E_WARNING, "unhandled resource type detected.");
      fd = -1;
    }
  } else if (Z_TYPE_P(ptr) == IS_LONG) {
    fd = Z_LVAL_P(ptr);
    if (fd < 0) {
      fd = -1;
    }

    {
      /* make sure that a valid resource handle was passed - issue #36 */
      int err = uv_guess_handle((uv_file)fd);
      if (err == UV_UNKNOWN_HANDLE) {
        php_error_docref(NULL, E_WARNING, "invalid resource type detected");
        fd = -1;
      }
    }
  } else if (socket_ce && Z_TYPE_P(ptr) == IS_OBJECT &&
             Z_OBJCE_P(ptr) == socket_ce &&
             (socket = (php_socket *)((char *)(Z_OBJ_P(ptr)) -
                                      XtOffsetOf(php_socket, std)))) {
    fd = socket->bsd_socket;
  }

  return fd;
}
