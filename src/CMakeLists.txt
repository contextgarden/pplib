add_library(pplib_utils STATIC
    util/utilcrypt.c
    util/utiliof.c
    util/utillog.c
    util/utilmd5.c
    util/utilmem.c
    util/utilnumber.c
    util/utilsha.c
)

target_include_directories(pplib_utils PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include/util>
    $<INSTALL_INTERFACE:pplib/include>
    $<INSTALL_INTERFACE:pplib/include/util>
)

target_link_libraries(pplib_utils
    PUBLIC
        m
        ZLIB::ZLIB
)

add_library(pplib_filters STATIC
    util/utilbasexx.c
    util/utilflate.c
    util/utilfpred.c
    util/utillzw.c
)

target_include_directories(pplib_filters PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include/util>
    $<INSTALL_INTERFACE:pplib/include>
    $<INSTALL_INTERFACE:pplib/include/util>
)

target_link_libraries(pplib_filters
    PUBLIC
        m
        ZLIB::ZLIB
)

add_library(pplib
    pparray.c
    ppcrypt.c
    ppdict.c
    ppheap.c
    ppload.c
    ppstream.c
    ppxref.c
)

target_include_directories(pplib PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include/util>
    $<INSTALL_INTERFACE:pplib/include>
    $<INSTALL_INTERFACE:pplib/include/util>
)

target_link_libraries(pplib
    PRIVATE
        pplib_filters
        pplib_utils
)

target_include_directories(pplib
    PRIVATE
        util
)

add_library(pplib::pplib ALIAS pplib)

include(GNUInstallDirs)

install(TARGETS pplib pplib_filters pplib_utils
    EXPORT pplib
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/include
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pplib
)

install(EXPORT pplib
    NAMESPACE pplib::
    FILE pplib.cmake
    DESTINATION lib/cmake/pplib
)

list(APPEND tests pptest1 pptest2 pptest3)

foreach(_test IN LISTS tests)
    add_executable(${_test} ${_test}.c)
    target_link_libraries(${_test} PRIVATE pplib)

    add_test(
        NAME pplib.${_test}
        COMMAND $<TARGET_FILE:${_test}>
    )
endforeach()
