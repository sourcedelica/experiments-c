set(SOURCES
        main.cpp
        EnvelopeTest.cpp
        PingPongTest.cpp
        RegistrationTest.cpp
        ScopedThreadTest.cpp
        ../Envelope.cpp
        ../IdGenerator.h)

include_directories(${CATCH_INC_DIR})

add_executable(common_test ${SOURCES})
target_link_libraries(common_test common ${PROTOBUF_LIBS})