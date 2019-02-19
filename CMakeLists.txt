cmake_minimum_required(VERSION 3.13)
project(qm)

option(BUILD_TESTS "whether or not to build the test" ON)

include_directories(include)

add_library(qm
        src/models/ipv4.cpp
        src/models/p2p_connection.cpp src/yaml/p2p_connection.cpp src/yaml/ip.cpp src/models/network.cpp include/qm/model/network.hpp src/models/node.cpp include/qm/exceptions.hpp include/qm/model/identifiable.hpp src/yaml/reference_resolve.cpp src/yaml/reference_parse.cpp src/yaml/node.cpp include/qm/yaml/yaml_reference.hpp include/qm/yaml/dto.h)

set_property(TARGET qm PROPERTY CXX_STANDARD 17)
set_property(TARGET qm PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET qm PROPERTY CXX_EXTENSIONS ON)

link_directories($ENV{DCE_ROOT}/lib)
target_include_directories(qm PUBLIC include $ENV{DCE_ROOT}/include)
target_link_libraries(qm PUBLIC ns3.28-core-debug yaml-cpp)

if (BUILD_TESTS)
    add_subdirectory(tests)
endif()
