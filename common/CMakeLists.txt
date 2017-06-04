set(SOURCES
        ScopedThread.h
        ThreadResource.h)

# Protobuf
#protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTOS})
#include_directories(${CMAKE_CURRENT_BINARY_DIR})

#add_library(common ${SOURCES} ${PROTO_SRCS} ${PROTO_HDRS})
#target_link_libraries(common CONAN_PKG::caf CONAN_PKG::Protobuf)

add_subdirectory(test)