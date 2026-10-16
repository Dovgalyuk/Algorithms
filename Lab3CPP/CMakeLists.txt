add_executable(LAB3 lab3.cpp)

target_link_libraries(LAB3 PRIVATE LibraryCPP)
target_include_directories(LAB3 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../LibraryCPP)
if(MINGW)
    target_link_options(LAB3 PRIVATE -static)
endif()

enable_testing()

set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Tests)

foreach(i RANGE 2 15)
    add_test(NAME LAB3_run_${i}
            COMMAND LAB3
            ${CMAKE_CURRENT_SOURCE_DIR}/Tests/input_${i}
            ${CMAKE_CURRENT_BINARY_DIR}/output_${i})


    add_test(NAME LAB3_check_${i}
            COMMAND ${CMAKE_COMMAND} -E compare_files
            ${CMAKE_CURRENT_BINARY_DIR}/output_${i}
            ${CMAKE_CURRENT_SOURCE_DIR}/Tests/expected_${i})

    set_tests_properties(LAB3_run_${i}   PROPERTIES FIXTURES_SETUP    out_${i})
    set_tests_properties(LAB3_check_${i} PROPERTIES FIXTURES_REQUIRED out_${i})
endforeach()

