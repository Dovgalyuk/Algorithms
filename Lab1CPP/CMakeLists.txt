add_executable(Lab1Task1 task1.cpp)
target_include_directories(Lab1Task1 PUBLIC ../LibraryCPP)
target_link_libraries(Lab1Task1 LibraryCPP)

add_executable(Lab1Task2 task2.cpp)
target_include_directories(Lab1Task2 PUBLIC ../LibraryCPP)
target_link_libraries(Lab1Task2 LibraryCPP)

function(add_lab1_test program name)
    set(output ${CMAKE_CURRENT_BINARY_DIR}/${name}_output.txt)
    add_test(NAME ${name} COMMAND ${program} ${CMAKE_CURRENT_SOURCE_DIR}/tests/${name}_input.txt ${output})
    add_test(NAME ${name}_ok COMMAND ${CMAKE_COMMAND} -E compare_files --ignore-eol ${output} ${CMAKE_CURRENT_SOURCE_DIR}/tests/${name}_valid.txt)
    set_tests_properties(${name}_ok PROPERTIES DEPENDS ${name})
endfunction()

add_lab1_test(Lab1Task1 Task1_1)
add_lab1_test(Lab1Task1 Task1_2)
add_lab1_test(Lab1Task1 Task1_3)

add_lab1_test(Lab1Task2 Task2_1)
add_lab1_test(Lab1Task2 Task2_2)
add_lab1_test(Lab1Task2 Task2_3)
add_lab1_test(Lab1Task2 Task2_4)
