set(PROTOB_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(PROTOB_OUT_DIR "${CMAKE_CURRENT_BINARY_DIR}")
find_program(PROTOB_CMD
    NAMES protoc
    REQUIRED)
find_program(GRPC_PLUGIN
    NAMES grpc_cpp_plugin
    REQUIRED)

add_custom_command(
    OUTPUT ${PROTOB_OUT_DIR}/helloworld.pb.cc ${PROTOB_OUT_DIR}/helloworld.pb.h
    WORKING_DIRECTORY ${PROTOB_SRC_DIR}
    COMMAND
        ${PROTOB_CMD}
        --proto_path=${PROTOB_SRC_DIR}
        --cpp_out=${PROTOB_OUT_DIR}
        helloworld.proto)

add_custom_command(
    OUTPUT ${PROTOB_OUT_DIR}/helloworld.grpc.pb.cc ${PROTOB_OUT_DIR}/helloworld.grpc.pb.h
    WORKING_DIRECTORY ${PROTOB_SRC_DIR}
    COMMAND
        ${PROTOB_CMD}
        --proto_path=${PROTOB_SRC_DIR}
        --grpc_out=${PROTOB_OUT_DIR}
        --plugin=protoc-gen-grpc=${GRPC_PLUGIN}
        helloworld.proto)

set(PROTO_SOURCES
    ${PROTOB_OUT_DIR}/helloworld.grpc.pb.h
    ${PROTOB_OUT_DIR}/helloworld.grpc.pb.cc
    ${PROTOB_OUT_DIR}/helloworld.pb.h
    ${PROTOB_OUT_DIR}/helloworld.pb.cc)

# find package
find_package(protobuf
    CONFIG REQUIRED)
find_package(gRPC ${GRPC_DESIRED_VERSION}
    CONFIG REQUIRED)

cmake_policy(SET CMP0135 OLD)

if(NOT DEFINED PROTOB_OUT_DIR)
    message(FATAL_ERROR "PROTOB_OUT_DIR is not set!")
endif()

# logging and formatting
include("${PROJECT_SOURCE_DIR}/cmake_modules/spdlog.cmake")

# server
add_executable(server server.cpp ${PROTO_SOURCES})
target_link_libraries(server
    PUBLIC gRPC::grpc++
    PRIVATE spdlog)
target_include_directories(server PUBLIC ${PROTOB_OUT_DIR})

# client
add_executable(client client.cpp ${PROTO_SOURCES})
target_link_libraries(client
    PUBLIC gRPC::grpc++
    PRIVATE spdlog)
target_include_directories(client PUBLIC ${PROTOB_OUT_DIR})
