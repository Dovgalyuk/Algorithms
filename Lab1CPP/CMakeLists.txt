add_executable(Lab1_Task1 lab1_task1.cpp)
add_executable(Lab1_Task2 lab1_task2.cpp)

foreach(TARGET Lab1_Task1 Lab1_Task2)
    target_link_libraries(${TARGET} LibraryCPP)
    target_include_directories(${TARGET} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../LibraryCPP)
endforeach()

enable_testing()

set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Test)

foreach(i RANGE 1 8)
    add_test(
            NAME Lab1_Task1_Run_${i}
            COMMAND Lab1_Task1 ${TEST_DIR}/input_${i} ${CMAKE_CURRENT_BINARY_DIR}/result_${i}
    )
    add_test(
            NAME Lab1_Task1_Check_${i}
            COMMAND ${CMAKE_COMMAND} -E compare_files
            ${CMAKE_CURRENT_BINARY_DIR}/result_${i}
            ${TEST_DIR}/expected_${i}
    )
    set_tests_properties(Lab1_Task1_Check_${i} PROPERTIES DEPENDS Lab1_Task1_Run_${i})
endforeach()


foreach(i RANGE 9 15)
    add_test(
            NAME Lab1_Task2_Run_${i}
            COMMAND Lab1_Task2 ${TEST_DIR}/input_${i} ${CMAKE_CURRENT_BINARY_DIR}/result_${i}
    )
    add_test(
            NAME Lab1_Task2_Check_${i}
            COMMAND ${CMAKE_COMMAND} -E compare_files --ignore-eol
            ${CMAKE_CURRENT_BINARY_DIR}/result_${i}
            ${TEST_DIR}/expected_${i}
    )
    set_tests_properties(Lab1_Task2_Check_${i} PROPERTIES DEPENDS Lab1_Task2_Run_${i})
endforeach()