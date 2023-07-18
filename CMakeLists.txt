cmake_minimum_required(VERSION 3.11)

set(CMAKE_MODULE_PATH
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules/"
    CACHE INTERNAL "Default module path.")

option(CMAKE_VERBOSE_MAKEFILE "Enable verbose output" ON)
option(CMAKE_EXPORT_COMPILE_COMMANDS "Export compile commands for linters and autocompleters" ON)

project(main LANGUAGES CXX)

option(BUILD_TESTS "Build test suite" OFF)
option(ADDRESS_SANITIZER "Enable address sanitizer" OFF)

set(CMAKE_CXX_STANDARD
    11
    CACHE STRING "The C++ standard to use")

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
add_executable(main main.cpp)
#target_link_libraries(main functions_lib)

if(BUILD_TESTS)
    add_subdirectory("tests")
endif()

### Useful debug stuff

### TODO: DELETE
# print variables
include(CMakePrintHelpers)
cmake_print_variables(CMAKE_CXX_STANDARD)
# function to print vars
function(print)
    message("--")
    cmake_print_variables(${ARGN})
endfunction()
function(print_fatal)
    print(${ARGN})
    message(FATAL_ERROR "--- last print")
endfunction()
### TODO: DELETE
