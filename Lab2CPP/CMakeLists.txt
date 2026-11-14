add_executable(LAB2 lab2.cpp)

target_link_libraries(LAB2 PRIVATE LibraryCPP)
target_include_directories(LAB2 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../LibraryCPP)
if(MINGW)
    target_link_options(LAB2 PRIVATE -static)
endif()

enable_testing()

set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Tests)

foreach(i RANGE 1 15)
    add_test(
            NAME Lab2_Run_${i}
            COMMAND LAB2 ${TEST_DIR}/input_${i} ${CMAKE_CURRENT_BINARY_DIR}/result_${i}
    )
    add_test(
            NAME Lab2_Check_${i}
            COMMAND ${CMAKE_COMMAND} -E compare_files
            ${CMAKE_CURRENT_BINARY_DIR}/result_${i}
            ${TEST_DIR}/expected_${i}
    )
    set_tests_properties(Lab2_Check_${i} PROPERTIES DEPENDS Lab2_Run_${i})
endforeach()

