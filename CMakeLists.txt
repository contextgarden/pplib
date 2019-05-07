cmake_minimum_required(VERSION 3.5)

project(pplib
    LANGUAGES C)
set(VERSION 1.0.5)

set(CMAKE_C_STANDARD 99)

find_package(ZLIB REQUIRED)

enable_testing()

add_subdirectory(src)
