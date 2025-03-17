cmake_minimum_required(VERSION 3.29)
project(simple C)

set(CMAKE_C_STANDARD 11)

add_executable(simple
        src/server.c
        src/client.c
        src/client.h
        src/server.h
        src/utils.c
        src/utils.h
        src/main.c)
