cmake_minimum_required(VERSION 3.14)
project(buf VERSION 1.0.0 LANGUAGES C)

option(ENABLE_COVERAGE "Enable code coverage" OFF)
if(ENABLE_COVERAGE)
    add_compile_options(--coverage)
    add_link_options(--coverage)
    set(CMAKE_BUILD_TYPE Debug)
endif()

add_library(buf src/buf.c)
add_library(buf::buf ALIAS buf)

target_include_directories(buf PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# -------- Tests --------
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    include(CTest) # Включает функционал add_test
    add_subdirectory(tests)
endif()

# ------- Coverage -------
if(ENABLE_COVERAGE)
    add_custom_target(coverage
        COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
        COMMAND find . -name "buf.c.gcda" | xargs gcov -n
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Running tests and checking coverage..."
    )
endif()

# ---- Installation ----
include(GNUInstallDirs)
install(TARGETS buf EXPORT bufConfig DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(FILES include/buf.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT bufConfig NAMESPACE buf:: DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/buf)
