
set(GRPC_ROOT "/opt/grpc" CACHE PATH "GRPC installation directory.")

# find package (preferred!)
find_package(protobuf
    HINTS ${GRPC_ROOT}
    CONFIG REQUIRED)
find_package(gRPC ${GRPC_DESIRED_VERSION}
    HINTS ${GRPC_ROOT}
    CONFIG REQUIRED)
find_program(GRPC_PLUGIN
    NAMES grpc_cpp_plugin
    HINTS ${GRPC_ROOT}
    REQUIRED)
set(GRPC_LIB_DIR "${GRPC_ROOT}/lib")

#set(ENV{LD_LIBRARY_PATH} ${GRPC_LIB_DIR}:${GRPC_LIB_DIR}64:$ENV{LD_LIBRARY_PATH})
#message("LD_LIBRARY_PATH = $ENV{LD_LIBRARY_PATH}")

file(GLOB PROTOB_DEF_SRC_FILES "*.proto")
set(PROTOB_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(PROTOB_OUT_DIR "${CMAKE_CURRENT_BINARY_DIR}")
find_program(PROTOB_CMD
    NAMES protoc
    HINTS ${GRPC_ROOT}
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

# find package (preferred!)
#find_package(protobuf
#    HINTS ${GRPC_ROOT}
#    CONFIG REQUIRED)
#find_package(gRPC ${GRPC_DESIRED_VERSION}
#    HINTS ${GRPC_ROOT}
#    CONFIG REQUIRED)

