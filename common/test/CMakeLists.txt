set(SOURCES
        main.cpp
        ScopedThreadTest.cpp)

add_executable(common_test ${SOURCES})
target_link_libraries(common_test common CONAN_PKG::catch)