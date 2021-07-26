cmake_minimum_required(VERSION 3.5)
project(experiments)

set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/cmake")

include(conan)
conan_cmake_run(CONANFILE conanfile.txt
        BASIC_SETUP CMAKE_TARGETS
        BUILD missing
        CONAN_COMMAND /Users/eric/.pyenv/versions/3.9.6/bin/conan)

## Run "conan install .." in the "build" directory to create this file
#if(EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
#    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
#    conan_basic_setup(TARGETS)
#endif()

add_executable(assign_derived_classes assign_derived_classes.cpp)

include(CTest)
# TODO - after https://github.com/catchorg/Catch2/issues/1590 is fixed remove tw-Catch.cmake and CatchAddTests.cmake
#  and replace the below with include(Catch).  It will use the code from the Conan catch2 package
include(tw-Catch)
add_executable(catch_example catch_example.cpp catch_main.cpp CatchTests.cpp)
add_executable(catch_other catch_other.cpp)
target_link_libraries(catch_example CONAN_PKG::catch2)
target_link_libraries(catch_other CONAN_PKG::catch2)
catch_discover_tests(catch_example)
catch_discover_tests(catch_other)

add_executable(condition_variable_ping_pong condition_variable_ping_pong.cpp)
target_compile_options(condition_variable_ping_pong PRIVATE -fsanitize=thread)
target_link_libraries(condition_variable_ping_pong PRIVATE -fsanitize=thread)

add_executable(condition_variables condition_variables.cpp)
add_executable(cu_ordering_test CUTrace.h cu_ordering_test.cpp cu_ordering_test2.cpp)
add_executable(experiments main.cpp)

add_executable(fmt fmt.cpp)
target_link_libraries(fmt CONAN_PKG::spdlog)

add_executable(FileWordCount FileWordCount.cpp)
add_executable(func_perf func_perf.cpp func_perf_funcs.cpp)
add_executable(is_detected is_detected.cpp)
add_executable(grandchild_override grandchild_override.cpp)
add_executable(myGuard myGuard.cpp)
add_executable(numeric_range numeric_range.cpp)
add_executable(pretty_sfinae pretty_sfinae.cpp)
add_executable(overloaded overloaded.cpp)

add_executable(pimpl_100 pimpl_100_widget.cpp pimpl_100.cpp)
add_executable(pimpl_101 pimpl_101.cpp pimpl_101_widget.cpp pimpl_101_h.h pimpl_101_impl.h)

add_executable(ranges ranges.cpp)
target_link_libraries(ranges CONAN_PKG::range-v3)
#target_link_libraries(ranges PRIVATE meta range-v3)

add_executable(reference_slicing reference_slicing.cpp)
add_executable(rvalue_refs_in_apis rvalue_refs_in_apis.cpp)
add_executable(self_registering_factory_lambda self_registering_factory_lambda.cpp)
add_executable(stop_problem stop_problem.cpp)
add_executable(strong_optionals strong_optionals.cpp)
add_executable(template_via_pointer template_via_pointer.cpp)

add_executable(to_string_detected to_string_detected.cpp match_hana.h)
target_link_libraries(to_string_detected CONAN_PKG::boost)

add_executable(tuple_iterator_main tuple_iterator_main.cpp tuple_iterator.h)

add_executable(type_index type_index.cpp)
target_link_libraries(type_index CONAN_PKG::boost)

add_executable(type_safe type_safe.cpp)
target_link_libraries(type_safe CONAN_PKG::type_safe CONAN_PKG::debug_assert)

add_executable(universal_reference_wrapper universal_reference_wrapper.cpp)
add_executable(using_namespace using_namespace.cpp)
add_executable(variadic_fmin variadic_fmin.cpp)

add_executable(variant_server variant_server.cpp match.h)
target_link_libraries(variant_server CONAN_PKG::boost)


add_subdirectory(caf)
add_subdirectory(common)
#add_subdirectory(gaffer)
add_subdirectory(grpc)
add_subdirectory(zmq)
