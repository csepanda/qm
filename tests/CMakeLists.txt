cmake_minimum_required(VERSION 3.13)

set(tests
        src/parsers/ip_from_string.cpp src/parsers/ip_from_yaml.cpp src/parsers/p2p_from_yaml.cpp src/parsers/resolve_context.cpp src/parsers/ipconfig_yaml.cpp src/yaml/parsers/Node.cpp src/parsers/network_from_yaml.cpp src/yaml/parsers/Process.cpp src/parsers/simulationConfiguration_from_yaml.cpp src/yaml/parsers/NS3Types.cpp src/services/utils/FileModeBuilder.cpp src/yaml/parsers/File.cpp src/algorithm/matrix/MatrixTests.cpp src/algorithm/matrix/Normalization.cpp src/algorithm/graph/MarkovClusteringVerification.cpp)

add_subdirectory(lib/Catch2)
add_executable(qm_test test_base.cpp ${tests})
target_include_directories(qm_test PUBLIC ${CMAKE_CURRENT_BINARY_DIR} $ENV{DCE_ROOT}/include)
set_property(TARGET qm_test PROPERTY CXX_STANDARD 17)
set_property(TARGET qm_test PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET qm_test PROPERTY CXX_EXTENSIONS ON)

link_directories($ENV{DCE_ROOT}/lib)


target_link_libraries(qm_test PUBLIC qm Catch2::Catch2 yaml-cpp ns3.28-core-debug ns3.28-network-debug ns3.28-stats-debug)

enable_testing()
add_test(NAME test COMMAND qm_test)
