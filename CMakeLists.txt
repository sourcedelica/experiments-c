cmake_minimum_required(VERSION 3.5)
project(experiments)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

# Run "conan install .." in the "build" directory to create this file
if(EXISTS ${CMAKE_SOURCE_DIR}/conanbuildinfo.cmake)
    include(conanbuildinfo.cmake)
    conan_basic_setup()
#    conan_basic_setup(TARGETS)    # TODO
endif()

#################################################################################################
# Third party libraries

# Boost
#set(BOOST_LIBRARYDIR ${BOOST_ROOT}/bin.v2/libs CACHE PATH "Boost library directory")   # Cygwin
set (Boost_USE_STATIC_LIBS ON)
set (Boost_USE_MULTITHREAD ON)
find_package(Boost COMPONENTS REQUIRED chrono filesystem thread)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
endif ()

# CAF
set(CAF_DIR ${CONAN_CAF_ROOT} CACHE PATH "CAF install directory")
set(CAF_INC_DIR ${CAF_DIR}/include)
set(CAF_LIB_DIR ${CAF_DIR}/lib)
# CMake really wants absolute paths for static libraries.
# If you have a relative path like ../../third-party/caf-0.15.1/lib,
# prefix it with ${CMAKE_CURRENT_SOURCE_DIR} to make it absolute.
# For example:
# ${CMAKE_CURRENT_SOURCE_DIR}/../../third-party/caf-0.15.1/lib
set(CAF_LIBS
        ${CAF_LIB_DIR}/libcaf_io_static.a
        ${CAF_LIB_DIR}/libcaf_core_static.a)

# Uncomment to temporarily add CAF source to project for debugging (make sure it's the same version!)
#add_subdirectory(/Users/eric/IdeaProjects/actor-framework caf-source)

# Catch
set(CATCH_INC_DIR ${CONAN_INCLUDE_DIRS_CATCH} CACHE PATH "Catch include directory")      # Conan

# Foonathan
include_directories(${CONAN_INCLUDE_DIRS_DEBUG_ASSERT})
include_directories(${CONAN_INCLUDE_DIRS_TYPE_SAFE})

# gRPC
#set(GRPC_INC_DIR ${CONAN_INCLUDE_DIRS_GRPC} CACHE PATH "gRPC include directory")         # Conan
#set(GRPC_LIB_DIR ${CONAN_LIB_DIRS_GRPC} CACHE PATH "gRPC libs directory")                # Conan
#set(GRPC_BIN_DIR ${CONAN_BIN_DIRS_GRPC} CACHE PATH "gRPC bin directory")                 # Conan
#set(GRPC_LIBS ${GRPC_LIB_DIR}/libgrpc++_unsecure.a ${GRPC_LIB_DIR}/libgrpc.a)

# libuv
#set(LIBUV_INC_DIR ${CONAN_INCLUDE_DIRS_LIBUV} CACHE PATH "libuv include directory")      # Conan
#set(LIBUV_LIB_DIR ${CONAN_LIB_DIRS_LIBUV} CACHE PATH "libuv lib dir")                    # Conan
#set(LIBUV_LIBS ${LIBUV_LIB_DIR}/libuv.a)

# Protobuf
#set(Protobuf_LIBRARY ${CONAN_PROTOBUF_ROOT})                                             # Conan
#find_package(Protobuf)
#set(PROTOBUF_INC_DIR ${PROTOBUF_INCLUDE_DIRS} CACHE PATH "Protobuf include directory")
#set(PROTOBUF_LIBS ${PROTOBUF_LIBRARIES}/lib/libprotobuf.a CACHE PATH "Protobuf libs")

# Range-v3
include_directories(${CONAN_INCLUDE_DIRS_RANGE-V3})

# Spdlog
include_directories(${CONAN_INCLUDE_DIRS_SPDLOG})

# zlib
set(ZLIB_LIBS ${CONAN_LIB_DIRS_ZLIB}/libz.a CACHE PATH "Zlib library")                   # Conan

# ZMQ
#set(ZMQ_INC_DIR ${CONAN_INCLUDE_DIRS_CPPZMQ} CACHE PATH "ZMQ include directory")         # Conan
#set(ZMQ_LIBS ${CONAN_LIB_DIRS_LIBZMQ}/libzmq-static.a CACHE PATH "ZMQ libraries")        # Conan

##################################################################################################

# Add top directory to include path
include_directories(${CMAKE_SOURCE_DIR})

# Switch on DEBUG code
add_definitions(-DDEBUG)

add_executable(catch_example catch_example.cpp catch_main.cpp CatchTests.cpp)
add_executable(cu_ordering_test CUTrace.h cu_ordering_test.cpp cu_ordering_test2.cpp)
add_executable(experiments main.cpp)
add_executable(fmt fmt.cpp)
add_executable(grandchild_override grandchild_override.cpp)
add_executable(numeric_range numeric_range.cpp)
add_executable(ranges ranges.cpp)
add_executable(reference_slicing reference_slicing.cpp)
add_executable(stop_problem stop_problem.cpp)
add_executable(template_via_pointer template_via_pointer.cpp)
add_executable(tuple_iterator_main tuple_iterator_main.cpp tuple_iterator.h)
add_executable(type_index type_index.cpp)
add_executable(type_safe type_safe.cpp)
add_executable(variant_server variant_server.cpp make_overload.h)

add_subdirectory(caf)
add_subdirectory(common)
add_subdirectory(gaffer)
#add_subdirectory(grpc)
#add_subdirectory(zmq)
