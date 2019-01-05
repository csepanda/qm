set(tests
    src/basic_test.cpp
)

add_subdirectory(lib/Catch2)
add_executable(qm_test test_base.cpp ${tests})
target_include_directories(qm_test PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(qm_test PUBLIC qm Catch2::Catch2)
set_target_properties(qm_test PROPERTIES CXX_STANDARD 11)

enable_testing()
add_test(NAME test COMMAND qm_test)
