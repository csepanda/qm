cmake_minimum_required(VERSION 3.7)
project(qm)

option(BUILD_TESTS "whether or not to build the test" ON)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_library(qm
        src/model_ipv4address.cpp
        src/parsers.cpp src/model_p2p_connection.cpp src/yaml-parsers/p2p_connection.cpp src/yaml-parsers/ip.cpp src/model_network.cpp include/qm/model/network.hpp src/model_node.cpp include/qm/exceptions.hpp)

link_directories($ENV{DCE_ROOT}/lib)
target_include_directories(qm PUBLIC include $ENV{DCE_ROOT}/include)
target_link_libraries(qm PUBLIC ns3.28-core-debug yaml-cpp)

if (BUILD_TESTS)
    add_subdirectory(tests)
endif()
