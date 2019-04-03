cmake_minimum_required(VERSION 3.13)
project(qm)

option(BUILD_TESTS "whether or not to build the test" ON)

include_directories(include)

add_library(qm
        src/models/ipv4.cpp
        src/models/Connection.cpp src/yaml/parsers/Connection.cpp src/models/Network.cpp
        include/qm/models/Network.hpp src/models/Node.cpp include/qm/exceptions.hpp
        include/qm/models/identifiable.hpp src/yaml/reference_resolve.cpp src/yaml/parsers/YamlReference.cpp
        src/yaml/parsers/Node.cpp include/qm/yaml/dto/Index.hpp include/qm/yaml/parsers/Network.hpp src/yaml/parsers/Network.cpp
        include/qm/services/Simulation.hpp src/services/Simulation.cpp include/qm/services/IpConfigurator.hpp
        src/services/dce/LinuxStackIpConfigurator.cpp include/qm/services/TimeSequence.h
        src/services/TimeSequence.cpp include/qm/services/dce/CommandBuilder.hpp src/services/dce/CommandBuilder.cpp
        include/qm/services/dce/LinuxStackIPConfigurator.hpp src/services/Ns3StackIpConfigurator.cpp
        include/qm/models/SimulationConfiguration.hpp src/models/SimulationConfiguration.cpp
        include/qm/models/Process.hpp src/models/Process.cpp src/yaml/dto/Process.cpp include/qm/yaml/dto/Process.hpp
        include/qm/yaml/dto/SimulationConfiguration.hpp src/yaml/dto/SimulationConfiguration.cpp
        include/qm/yaml/parsers/SimulationConfiguration.hpp src/yaml/parsers/SimulationConfiguration.cpp
        include/qm/services/SimulationProducer.hpp
        src/services/SimulationProducer.cpp include/qm/services/NetworkConfigurator.hpp
        src/services/NetworkConfigurator.cpp include/qm/services/ApplicationInstaller.hpp
        include/qm/yaml/parsers/NS3Types.hpp src/yaml/parsers/NS3Types.cpp src/services/ApplicationInstaller.cpp
        include/qm/yaml/dto/Connection.hpp
        src/yaml/dto/Connection.cpp include/qm/yaml/dto/Network.hpp src/yaml/dto/Network.cpp
        include/qm/yaml/dto/Node.hpp src/yaml/dto/Node.cpp
        include/qm/yaml/parsers/Process.hpp src/yaml/parsers/Process.cpp include/qm/yaml/dto/IpNetwork.hpp
        src/yaml/dto/IpNetwork.cpp include/qm/yaml/parsers/IpNetwork.hpp
        src/yaml/parsers/IpNetwork.cpp include/qm/yaml/parsers/YamlReference.hpp include/qm/yaml/parsers/IpAddress.hpp
        include/qm/yaml/dto/IpAddress.hpp
        src/yaml/parsers/IpAddress.cpp include/qm/parsers/IpUtils.hpp src/parsers/IpUtils.cpp
        include/qm/services/NodeFilesystem.hpp src/services/NodeFilesystem.cpp
        include/qm/services/utils/FileModeBuilder.hpp src/services/utils/FileModeBuilder.cpp
        include/qm/services/utils/NodeFileSystemHelper.hpp src/services/utils/NodeFileSystemHelper.cpp
        include/qm/models/File.hpp src/models/File.cpp include/qm/yaml/dto/File.hpp src/yaml/dto/File.cpp
        include/qm/yaml/parsers/File.hpp src/yaml/parsers/File.cpp include/qm/services/FilesInstaller.hpp
        src/services/FilesInstaller.cpp include/qm/services/utils/FileTypes.hpp
        src/services/utils/FileTypes.cpp include/qm/services/INs3NodeCreator.hpp
        src/services/SimpleNs3NodeCreator.cpp
        include/qm/services/mpi/MpiNS3NodeCreator.hpp src/services/mpi/MpiNS3NodeCreator.cpp
        include/qm/services/mpi/ISystemIdMarkerStrategy.hpp include/qm/services/SimpleNs3NodeCreator.hpp
        include/qm/services/mpi/MclSystemIdMarkerStrategy.hpp src/services/mpi/MclSystemIdMarkerStrategy.cpp include/qm/services/mpi/ManualSystemIdMarkerStrategy.hpp src/services/mpi/ManualSystemIdMarkerStrategy.cpp
        src/services/mpi/MpiApplicationInstaller.cpp
        include/qm/algorithm/graph/Vertex.hpp include/qm/algorithm/graph/Edge.hpp
        include/qm/algorithm/graph/Vertex.tpp include/qm/algorithm/graph/Edge.tpp
        include/qm/algorithm/matrix/Matrix.hpp src/algorithm/matrix/Matrix.cpp
        include/qm/algorithm/matrix/Normalization.hpp src/algorithm/matrix/Normalization.cpp
        include/qm/algorithm/graph/MarkovClustering.hpp
        include/qm/algorithm/graph/Graph.hpp include/qm/algorithm/graph/Graph.tpp
        include/qm/algorithm/graph/Cluster.hpp include/qm/algorithm/graph/Cluster.tpp
        include/qm/algorithm/graph/MarkovClustering.tpp)

set_property(TARGET qm PROPERTY CXX_STANDARD 17)
set_property(TARGET qm PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET qm PROPERTY CXX_EXTENSIONS ON)


link_directories($ENV{DCE_ROOT}/lib)
execute_process(COMMAND sh -c "cd $ENV{DCE_ROOT}/lib; ls *ns3.28* *ns3-dce* *ns3-netlink* | grep -v 'test-debug' | sed 's/^lib//; s/.so$//' | xargs echo -n" OUTPUT_VARIABLE NS_LIBS)
target_include_directories(qm PUBLIC include $ENV{DCE_ROOT}/include)

string(REPLACE " " ";" NS_LIBS_LIST ${NS_LIBS})
target_link_libraries(qm PUBLIC ${NS_LIBS_LIST} yaml-cpp)

message(${NS_LIBS})

if (BUILD_TESTS)
    add_subdirectory(tests)
endif ()

add_executable(qm-runner src/test.cpp)

set_property(TARGET qm-runner PROPERTY CXX_STANDARD 17)
set_property(TARGET qm-runner PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET qm-runner PROPERTY CXX_EXTENSIONS ON)
target_link_libraries(qm-runner qm yaml-cpp)
target_link_libraries(qm PUBLIC ${NS_LIBS_LIST})
