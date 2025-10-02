# Основная программа
add_executable(Lab1Cpp lab1.cpp)

if(TARGET LibraryCPP)
    target_link_libraries(Lab1Cpp LibraryCPP)
    target_include_directories(Lab1Cpp PRIVATE ../LibraryCPP)
endif()

configure_file(input.txt input.txt COPYONLY)

enable_testing()

# Тест для вашей программы
add_test(NAME Lab1Cpp_Test COMMAND Lab1Cpp ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_tests_properties(Lab1Cpp_Test PROPERTIES 
    PASS_REGULAR_EXPRESSION "Original array: 1 -2 3 -4 5 1 -2 7 -4 9"
)
