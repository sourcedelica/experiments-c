get_filename_component(hw_proto "./helloworld.proto" ABSOLUTE)
get_filename_component(hw_proto_path "${hw_proto}" PATH)

# Generated sources
protobuf_generate_cpp(hw_proto_srcs hw_proto_hdrs "${hw_proto}")
set(hw_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/helloworld.grpc.pb.cc")
set(hw_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/helloworld.grpc.pb.h")
add_custom_command(
      OUTPUT "${hw_grpc_srcs}" "${hw_grpc_hdrs}"
      COMMAND ${PROTOBUF_PROTOC_EXECUTABLE}
      ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}" -I ${hw_proto_path}
        --plugin=protoc-gen-grpc="${GRPC_BIN_DIR}/grpc_cpp_plugin"
        "${hw_proto}"
      DEPENDS "${hw_proto}")

# Generated include directory
include_directories("${CMAKE_CURRENT_BINARY_DIR}")

# Targets greeter_[async_](client|server)
foreach(_target
  greeter_client greeter_server greeter_async_client greeter_async_server greeter_combined)
  add_executable(${_target} "${_target}.cc"
    ${hw_proto_srcs}
    ${hw_grpc_srcs})
  target_link_libraries(${_target} PRIVATE
    ${PROTOBUF_LIBS}
    ${GRPC_LIBS}
    ${ZLIB_LIBS})
endforeach()
