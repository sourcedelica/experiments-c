set(SOURCES
        Envelope.cpp
        PingPong.cpp
        Registration.cpp
        ThreadResource.h ScopedThread.h)

set(PROTOS
        Envelope.proto
        PingPong.proto
        Registration.proto)

# CAF
include_directories(${CAF_INC_DIR})

# Protobuf
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTOS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_library(common ${SOURCES} ${PROTO_SRCS} ${PROTO_HDRS})

add_subdirectory(test)