add_executable(Lab3 lab3.cpp)
target_include_directories(Lab3 PRIVATE ../LibraryCPPTemplate)

string(ASCII 13 CR)
string(ASCII 10 LF)

function(add_lab3_test name input expected)
    add_test(
        NAME ${name}
        COMMAND Lab3 ${CMAKE_CURRENT_SOURCE_DIR}/${input}
    )
    set_tests_properties(${name} PROPERTIES
        PASS_REGULAR_EXPRESSION "^${expected}[${CR}${LF}]*$"
    )
endfunction()

add_lab3_test(TestLab3_Example input_example.txt 4)
add_lab3_test(TestLab3_Layers  input_layers.txt  2)
add_lab3_test(TestLab3_Walls   input_walls.txt   7)
add_lab3_test(TestLab3_Nearest input_nearest.txt 1)