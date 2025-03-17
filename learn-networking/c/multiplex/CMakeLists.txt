cmake_minimum_required(VERSION 3.29)
project(multiplex C)

set(CMAKE_C_STANDARD 17)

find_package(PkgConfig REQUIRED)
pkg_check_modules(glib2 REQUIRED IMPORTED_TARGET glib-2.0)

add_executable(multiplex src/main.c
        src/utils.c
        src/utils.h
        src/server.c
        src/server.h
        src/client.c
        src/client.h
        src/server2.c)
target_link_libraries(multiplex PRIVATE m PkgConfig::glib2)
