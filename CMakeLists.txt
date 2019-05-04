cmake_minimum_required(VERSION 3.5)

project(pplib
    VERSION 1.0.5
    LANGUAGES C)

set(CMAKE_C_STANDARD 99)

if(MSVC)
    add_compile_options(/W4 /WX)
else(MSVC)
    add_compile_options(
        -Wall -Wextra
        -Wunused -Wimplicit -Wreturn-type -Wdeclaration-after-statement -Wno-unknown-pragmas -Wmissing-prototypes -Wmissing-declarations -Wparentheses -Wswitch -Wtrigraphs -Wcast-qual -Wcast-align -Wwrite-strings -Wold-style-definition -Wpointer-arith
    )
endif(MSVC)

add_library(pplib_utils STATIC
    util/utilarm.h
    util/utilplat.h
    util/utilcryptdef.h
    util/utildecl.h
    #
    util/utilcrypt.c
    util/utilcrypt.h
    util/utiliof.c
    util/utiliof.h
    util/utillog.c
    util/utillog.h
    util/utilmd5.c
    util/utilmd5.h
    util/utilmem.c
    util/utilmem.h
    util/utilnumber.c
    util/utilnumber.h
    util/utilsha.c
    util/utilsha.h
)

add_library(pplib_filters STATIC
    util/utilbasexx.c
    util/utilbasexx.h
    util/utilflate.c
    util/utilflate.h
    util/utilfpred.c
    util/utilfpred.h
    util/utillzw.c
    util/utillzw.h
)

add_library(pplib
    ppapi.h
    ppconf.h
    pplib.h
    #
    pparray.c
    pparray.h
    ppcrypt.c
    ppcrypt.h
    ppdict.c
    ppdict.h
    ppfilter.h
    ppheap.c
    ppheap.h
    ppload.c
    ppload.h
    ppstream.c
    ppstream.h
    ppxref.c
    ppxref.h
)

target_link_libraries(pplib
    PRIVATE
        pplib_filters
        pplib_utils
)

target_include_directories(pplib
    PRIVATE
        util
#       zlib::zlib
)
set_target_properties(pplib
    PROPERTIES
        PUBLIC_HEADER "ppapi.h;ppconf.h;pplib.h"
)

add_library(pplib::pplib ALIAS pplib)

install(TARGETS pplib
    EXPORT pplib
    DESTINATION lib
)

# enable_testing()
#
# list(APPEND tests pptest1 pptest2 pptest3)
#
# foreach(_test IN LISTS tests)
#     add_executable(${_test} ${_test}.c)
#     target_link_libraries(${_test} PRIVATE pplib)
#
#     add_test(
#         NAME ${_test}
#         COMMAND $<TARGET_FILE:${_test}>
#     )
# endforeach()
