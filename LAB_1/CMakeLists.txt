foreach(task task1 task2)
    add_executable(${task} ../LibraryCPP/LAB_1/${task}.cpp)
    target_include_directories(${task} PRIVATE ${PROJECT_SOURCE_DIR}/LibraryCPPClass)
    target_link_libraries(${task} PRIVATE LibraryCPPClass)
endforeach()

target_compile_definitions(task1 PRIVATE DEFAULT_INPUT_FILE="${PROJECT_SOURCE_DIR}/LibraryCPP/LAB_1/input1.txt")
target_compile_definitions(task2 PRIVATE DEFAULT_INPUT_FILE="${PROJECT_SOURCE_DIR}/LibraryCPP/LAB_1/input2.txt")

function(add_program_test name target input expected)
    add_test(NAME ${name} COMMAND ${target} ${CMAKE_CURRENT_SOURCE_DIR}/${input})
    set_tests_properties(${name} PROPERTIES PASS_REGULAR_EXPRESSION "${expected}")
endfunction()

add_program_test(RainfallOriginal task1 ../LibraryCPP/LAB_1/input1.txt
    "First decade: 4[.]5[\r\n]+Second decade: 4[.]5[\r\n]+Third decade: 4[.]5")
add_program_test(RainfallDifferent task1 Tests/Rainfall.txt
    "First decade: 5[.]5[\r\n]+Second decade: 15[.]5[\r\n]+Third decade: 25[.]5")
add_program_test(ShiftRight task2 ../LibraryCPP/LAB_1/input2.txt "Result: 0 0 1 2 3")
add_program_test(ShiftLeft task2 Tests/ShiftArr.txt "Result: 3 4 5 0 0")

