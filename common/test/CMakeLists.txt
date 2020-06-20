set(SOURCES
        main.cpp
        ExpectedTest.cpp
        ScopedThreadTest.cpp)

add_executable(common_test ${SOURCES})
target_link_libraries(common_test CONAN_PKG::catch2)