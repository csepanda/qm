cmake_minimum_required(VERSION 3.7)
project(qm)

option(BUILD_TESTS "whether or not to build the test" ON)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_library(qm
        include/qm/model.hpp
        src/model_ipv4address.cpp
        src/parsers_ipv4address_yaml.cpp
        src/parsers.cpp)

target_include_directories(qm PUBLIC include)

if (BUILD_TESTS)
    add_subdirectory(tests)
endif()
