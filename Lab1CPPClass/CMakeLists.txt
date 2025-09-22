add_executable(Lab1CPPClass lab1.cpp)
target_include_directories(Lab1CPPClass PUBLIC ../LibraryCPPClass)
target_link_libraries(Lab1CPPClass LibraryCPPClass)

add_test(NAME TestLab1CPPClass 
         COMMAND Lab1CPPClass ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)

set_tests_properties(TestLab1CPPClass PROPERTIES
    PASS_REGULAR_EXPRESSION "Положительных: 4.*Отрицательных: 3.*Нулевых: 3.*Элементы, встречающиеся ровно два раза:.*-1.*1"
)