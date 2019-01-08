set(tests
        src/parsers_ip_from_string.cpp src/parsers_ip_from_yaml.cpp src/parsers_p2p_from_yaml.cpp)

add_subdirectory(lib/Catch2)
add_executable(qm_test test_base.cpp ${tests})
target_include_directories(qm_test PUBLIC ${CMAKE_CURRENT_BINARY_DIR} $ENV{DCE_ROOT}/include)

link_directories($ENV{DCE_ROOT}/lib)


target_link_libraries(qm_test PUBLIC qm Catch2::Catch2 yaml-cpp ns3.28-core-debug ns3.28-network-debug ns3.28-stats-debug)
set_target_properties(qm_test PROPERTIES CXX_STANDARD 11)

enable_testing()
add_test(NAME test COMMAND qm_test)
