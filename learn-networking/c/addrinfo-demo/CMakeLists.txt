cmake_minimum_required(VERSION 3.29)

set(CMAKE_C_STANDARD 17)

# Ideally move this to a toolchain file
set(CMAKE_C_FLAGS "-Wall")

# Ideally move this to a CMakePresets.json file
set(CMAKE_EXPORT_COMPILE_COMMANDS YES)

project(netlearn VERSION 0.1 LANGUAGES C)

# find_package(PkgConfig REQUIRED)
# pkg_check_modules(glib2 REQUIRED IMPORTED_TARGET glib-2.0)

add_executable(netlearn main.c
        netutils.h
        netutils.c
        stringutils.h
        stringutils.c
)
# target_link_libraries(netlearn PRIVATE m PkgConfig::glib2)