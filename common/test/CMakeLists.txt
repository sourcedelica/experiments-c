set(SOURCES
        main.cpp
        ScopedThreadTest.cpp)

include_directories(${CATCH_INC_DIR})

add_executable(common_test ${SOURCES})
target_link_libraries(common_test common ${PROTOBUF_LIBS})