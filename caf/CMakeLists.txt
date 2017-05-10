include_directories(${CAF_INC_DIR})

add_executable(caf_test caf_test.cpp)

target_link_libraries(caf_test ${CAF_LIBS})