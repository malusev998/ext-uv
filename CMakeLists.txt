cmake_minimum_required(VERSION 3.8)

project(uv
          VERSION 0.3.0
          LANGUAGES C)

message(STATUS "Begin cmaking of PHP extension ...")

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING
            "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif ()

set(CMAKE_C_STANDARD 11)

set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -ggdb -O0 -Wall -std=c17 -fvisibility=hidden")

set(LIBUV_VERSION 1.34)

execute_process (
        COMMAND php-config --include-dir
        OUTPUT_VARIABLE PHP_SOURCE
)

string(REGEX REPLACE "\n$" "" PHP_SOURCE "${PHP_SOURCE}")

message("Using source directory: ${PHP_SOURCE}")

get_filename_component(LIBUV_INCLUDE "/usr/include" ABSOLUTE)

include_directories(
        "${PHP_SOURCE}"
        "${PHP_SOURCE}/main"
        "${PHP_SOURCE}/Zend"
        "${PHP_SOURCE}/TSRM"
        "${PHP_SOURCE}/ext"
        "${PHP_SOURCE}/sapi"
        "${LIBUV_UINCLUDE}/uv"
        "${LIBUV_INCLUDE}")

include_directories("${PROJECT_SOURCE_DIR}/include")

set(SOURCE_FILES
    php_uv.c
    uv.c
    php_uv.h)

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/config.h")
	add_definitions(-DHAVE_CONFIG_H)
	set(SOURCE_FILES "${SOURCE_FILES};config.h")
endif()

add_custom_target(configure
        COMMAND phpize && ./configure
        DEPENDS ${SOURCE_FILES}
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})

add_library(uv SHARED
        ${SOURCE_FILES}  
        "include/parsing.h" 
        "include/register.h" 
        "src/register_class.c" 
        "src/parsing.c" 
        "src/locks/semaphore.c" 
        "src/locks/mutex.c" 
        "src/locks/rwlock.c"
        "src/locks/php_lock.h" 
        "src/locks/php_lock.c"
        "src/locks/locks.c" 
        "include/init.h" "src/fs.h" "src/fs/fd.c")
add_library(___ EXCLUDE_FROM_ALL ${SOURCE_FILES} "src/fs.h" "src/fs/fd.c")

message(STATUS "End cmaking of PHP extension")