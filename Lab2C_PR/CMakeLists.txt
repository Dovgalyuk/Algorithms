add_executable(Lab2C_PR main.cpp)
target_include_directories(Lab2C_PR PUBLIC ../LibraryCPP)
target_link_libraries(Lab2C_PR LibraryCPP)

if (MSVC)
  target_compile_options(Lab2C_PR PRIVATE /utf-8)
endif()

add_test(NAME Lab2_Forth_Sample1 COMMAND Lab2C_PR ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt)
set_property(TEST Lab2_Forth_Sample1 PROPERTY PASS_REGULAR_EXPRESSION "1(.|\\r|\\n)*3(.|\\r|\\n)*2")

add_test(NAME Lab2_Forth_Sample2 COMMAND Lab2C_PR ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)
set_property(TEST Lab2_Forth_Sample2 PROPERTY PASS_REGULAR_EXPRESSION "1(.|\\r|\\n)*2(.|\\r|\\n)*3(.|\\r|\\n)*6")

add_test(NAME Lab2_Forth_Swap COMMAND Lab2C_PR ${CMAKE_CURRENT_SOURCE_DIR}/input_swap.txt)
set_property(TEST Lab2_Forth_Swap PROPERTY PASS_REGULAR_EXPRESSION "5(.|\\r|\\n)*6")

add_test(NAME Lab2_Forth_Over COMMAND Lab2C_PR ${CMAKE_CURRENT_SOURCE_DIR}/input_over.txt)
set_property(TEST Lab2_Forth_Over PROPERTY PASS_REGULAR_EXPRESSION "1(.|\\r|\\n)*2(.|\\r|\\n)*1")