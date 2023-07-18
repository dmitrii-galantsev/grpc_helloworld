cmake_minimum_required(VERSION 3.15)

set(CMAKE_MODULE_PATH
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules/"
    CACHE INTERNAL "Default module path.")

option(CMAKE_VERBOSE_MAKEFILE "Enable verbose output" ON)
option(CMAKE_EXPORT_COMPILE_COMMANDS "Export compile commands for linters and autocompleters" ON)
add_compile_definitions(SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_TRACE)

project(main LANGUAGES CXX)

option(BUILD_TESTS "Build test suite" OFF)
option(ADDRESS_SANITIZER "Enable address sanitizer" OFF)

#set(CMAKE_CXX_STANDARD
#    14
#    CACHE STRING "The C++ standard to use")

## Add address sanitizer
if(${ADDRESS_SANITIZER})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -shared-libasan")
    message(STATUS "ADDRESS_SANITIZE: CMAKE_CXX_FLAGS=: ${CMAKE_CXX_FLAGS}")
    message(STATUS "ADDRESS_SANITIZE: CMAKE_EXE_LINKER_FLAGS=: ${CMAKE_EXE_LINKER_FLAGS}")
endif()

# Include CMAKE_INSTALL_* variables
# this must go after project()
include(GNUInstallDirs)

add_subdirectory(grpc)
