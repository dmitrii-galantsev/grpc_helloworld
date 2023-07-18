
# find package (preferred!)
find_package(protobuf
    CONFIG REQUIRED)
find_package(gRPC ${GRPC_DESIRED_VERSION}
    CONFIG REQUIRED)
find_program(GRPC_PLUGIN
    NAMES grpc_cpp_plugin
    REQUIRED)

cmake_policy(SET CMP0135 OLD)

# logging and formatting
include("${PROJECT_SOURCE_DIR}/cmake_modules/spdlog.cmake")
include("${PROJECT_SOURCE_DIR}/cmake_modules/fmt.cmake")

file(GLOB PROTOB_DEF_SRC_FILES "*.proto")
set(PROTOB_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(PROTOB_OUT_DIR "${CMAKE_CURRENT_BINARY_DIR}")
find_program(PROTOB_CMD
    NAMES protoc
    REQUIRED)

foreach(file ${PROTOB_DEF_SRC_FILES})
    execute_process(COMMAND
        ${PROTOB_CMD} --proto_path=${PROTOB_SRC_DIR}
            --cpp_out=${PROTOB_OUT_DIR} ${file}
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        RESULT_VARIABLE PROTOB_RESULT
        OUTPUT_VARIABLE PROTOB_OUT_VAR
        COMMAND_ERROR_IS_FATAL ANY)
    message("protoc command returned: ${PROTOB_RESULT}")

    message("GRPC_PLUGIN=${GRPC_PLUGIN})")
    message("protoc cmd:")
    message("  $ ${PROTOB_CMD} --proto_path=${PROTOB_SRC_DIR}")
    message("    --grpc_out=${PROTOB_OUT_DIR}")
    message("....--plugin=protoc-gen-grpc=\"${GRPC_PLUGIN}\" ${file}")

    execute_process(COMMAND
        ${PROTOB_CMD} --proto_path=${PROTOB_SRC_DIR}
            --grpc_out=${PROTOB_OUT_DIR}
            --plugin=protoc-gen-grpc=${GRPC_PLUGIN} ${file}
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        RESULT_VARIABLE PROTOB_RESULT
        OUTPUT_VARIABLE PROTOB_OUT_VAR)
    message("protoc command returned: ${PROTOB_RESULT}")
endforeach()

set(PROTO_SOURCES
    helloworld.grpc.pb.h
    helloworld.grpc.pb.cc
    helloworld.pb.h
    helloworld.pb.cc)

# server
add_executable(server server.cpp ${PROTO_SOURCES})
target_link_libraries(server
    PUBLIC gRPC::grpc++
    PRIVATE spdlog)
target_include_directories(server PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

# client
add_executable(client client.cpp ${PROTO_SOURCES})
target_link_libraries(client
    PUBLIC gRPC::grpc++
    PRIVATE spdlog)
target_include_directories(client PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
