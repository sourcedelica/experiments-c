set(SOURCES
        echoserver.cpp
        stream.cpp)

add_executable(echoserver echoserver.cpp)
target_link_libraries(echoserver CONAN_PKG::cppzmq)

add_executable(stream stream.cpp)
target_link_libraries(stream CONAN_PKG::cppzmq)