cmake_minimum_required(VERSION 3.7)
project(qm)

option(BUILD_TESTS "whether or not to build the test" ON)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(src)

add_library(qm
        src/model.hpp
        src/model_ipv4address.cpp
        src/model_ipv4address_yaml.cpp
        src/parsers.cpp)

if (BUILD_TESTS)
    add_subdirectory(tests)
endif()
