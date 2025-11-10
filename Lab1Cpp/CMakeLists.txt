cmake_minimum_required(VERSION 3.10)
project(Lab1Cpp)

enable_testing()

#Ѕыла ошибка компил€ции

if(MSVC)
    add_compile_options(/EHsc)
endif()


add_executable(Lab1Cpp main.cpp ../LibraryCPP/array.cpp)
target_include_directories(Lab1Cpp PUBLIC ../LibraryCPP)


add_test(NAME TestLab1_Simples COMMAND $<TARGET_FILE:Lab1Cpp> 1)
set_tests_properties(TestLab1_Simples PROPERTIES
    PASS_REGULAR_EXPRESSION "Simple: 2 3 5 7 11"
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_test(NAME TestLab1_Shift COMMAND $<TARGET_FILE:Lab1Cpp> 2)
set_tests_properties(TestLab1_Shift PROPERTIES
    PASS_REGULAR_EXPRESSION "shift: 0 0 10 20 30 40"
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)