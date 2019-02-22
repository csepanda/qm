cmake_minimum_required(VERSION 3.13)
project(qm)

option(BUILD_TESTS "whether or not to build the test" ON)

include_directories(include)

add_library(qm
        src/models/ipv4.cpp
        src/models/p2p_connection.cpp src/yaml/p2p_connection.cpp src/yaml/ip.cpp src/models/network.cpp include/qm/model/network.hpp src/models/node.cpp include/qm/exceptions.hpp include/qm/model/identifiable.hpp src/yaml/reference_resolve.cpp src/yaml/reference_parse.cpp src/yaml/node.cpp include/qm/yaml/yaml_reference.hpp include/qm/yaml/dto.h include/qm/yaml/network.hpp src/yaml/network.cpp include/qm/services/Simulation.hpp src/services/Simulation.cpp include/qm/services/IpConfigurator.hpp src/services/dce/LinuxStackIpConfigurator.cpp include/qm/services/TimeSequence.h src/services/TimeSequence.cpp include/qm/services/dce/CommandBuilder.hpp src/services/dce/CommandBuilder.cpp include/qm/services/dce/LinuxStackIPConfigurator.hpp src/services/Ns3StackIpConfigurator.cpp include/qm/model/SimulationConfiguration.hpp src/models/SimulationConfiguration.cpp)

set_property(TARGET qm PROPERTY CXX_STANDARD 17)
set_property(TARGET qm PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET qm PROPERTY CXX_EXTENSIONS ON)


link_directories($ENV{DCE_ROOT}/lib)
execute_process(COMMAND sh -c "cd $ENV{DCE_ROOT}/lib; ls *ns3.28* | grep -v 'test-debug' | sed 's/^lib//; s/.so$//' | xargs echo -n" OUTPUT_VARIABLE NS_LIBS)
target_include_directories(qm PUBLIC include $ENV{DCE_ROOT}/include)

string(REPLACE " " ";" NS_LIBS_LIST ${NS_LIBS})
target_link_libraries(qm PUBLIC ${NS_LIBS_LIST} yaml-cpp)

if (BUILD_TESTS)
    add_subdirectory(tests)
endif()
