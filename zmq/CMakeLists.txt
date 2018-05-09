set(SOURCES
        echoserver.cpp
        stream.cpp)

# From vcpkg
# To integrate with our CMakeLists.txt
# cd <top of tree>/cmake-build-debug
# cmake .. -DCMAKE_TOOLCHAIN_FILE=/Users/eric/IdeaProjects/vcpkg/scripts/buildsystems/vcpkg.cmake
#find_package(zeromq REQUIRED)

add_executable(echoserver echoserver.cpp)
target_link_libraries(echoserver CONAN_PKG::cppzmq)
#target_link_libraries(echoserver PRIVATE libzmq libzmq-static)  # From vcpkg

add_executable(stream stream.cpp)
target_link_libraries(stream CONAN_PKG::cppzmq)
#target_link_libraries(stream PRIVATE libzmq libzmq-static)  # From vcpkg
