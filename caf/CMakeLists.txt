add_executable(caf_test caf_test.cpp)
target_link_libraries(caf_test PRIVATE CONAN_PKG::caf)

protobuf_generate_cpp(ProtoSources ProtoHeaders pingpong.proto)

add_executable(protobuf_broker protobuf_broker.cpp ${ProtoSources})
target_link_libraries(protobuf_broker PRIVATE CONAN_PKG::caf CONAN_PKG::protobuf)
target_include_directories(protobuf_broker PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

add_executable(simple_broker simple_broker.cpp)
target_link_libraries(simple_broker PRIVATE CONAN_PKG::caf)

add_executable(simple_http_broker simple_http_broker.cpp)
target_link_libraries(simple_http_broker PRIVATE CONAN_PKG::caf)

# Uncomment to temporarily add CAF source to project for debugging (make sure it's the same version!)
#add_subdirectory(/Users/eric/IdeaProjects/actor-framework caf-source)