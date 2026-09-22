# Программа для задачи 1
add_executable(lab1_task1 lab1_task1.cpp)
target_include_directories(lab1_task1 PUBLIC ../LibraryCPP)
target_link_libraries(lab1_task1 LibraryCPP)

# Программа для задачи 2
add_executable(lab1_task2 lab1_task2.cpp)
target_include_directories(lab1_task2 PUBLIC ../LibraryCPP)
target_link_libraries(lab1_task2 LibraryCPP)

# - Тесты для задачи 1 -

# 1 резистор
add_test(NAME TestTask1_Single COMMAND lab1_task1 ${CMAKE_CURRENT_SOURCE_DIR}/input1_1.txt)
set_property(TEST TestTask1_Single PROPERTY PASS_REGULAR_EXPRESSION "^10\\.000000[\\r\\n]*$")

# 2 одинаковых резистора
add_test(NAME TestTask1_Two COMMAND lab1_task1 ${CMAKE_CURRENT_SOURCE_DIR}/input1_2.txt)
set_property(TEST TestTask1_Two PROPERTY PASS_REGULAR_EXPRESSION "^2\\.500000[\\r\\n]*$")

# 4 одинаковых резистора
add_test(NAME TestTask1_Four COMMAND lab1_task1 ${CMAKE_CURRENT_SOURCE_DIR}/input1_3.txt)
set_property(TEST TestTask1_Four PROPERTY PASS_REGULAR_EXPRESSION "^0\\.250000[\\r\\n]*$")

# 3 разных резистора
add_test(NAME TestTask1_Three COMMAND lab1_task1 ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt)
set_property(TEST TestTask1_Three PROPERTY PASS_REGULAR_EXPRESSION "^5\\.454545[\\r\\n]*$")

# - Тесты для задачи 2 -

# все элементы одинаковые
add_test(NAME TestTask2_AllSame COMMAND lab1_task2 ${CMAKE_CURRENT_SOURCE_DIR}/input2_1.txt)
set_property(TEST TestTask2_AllSame PROPERTY PASS_REGULAR_EXPRESSION "^\\(7,5\\) [\\r\\n]*$")

# один элемент
add_test(NAME TestTask2_Single COMMAND lab1_task2 ${CMAKE_CURRENT_SOURCE_DIR}/input2_2.txt)
set_property(TEST TestTask2_Single PROPERTY PASS_REGULAR_EXPRESSION "^\\(42,1\\) [\\r\\n]*$")

# все разные
add_test(NAME TestTask2_AllDiff COMMAND lab1_task2 ${CMAKE_CURRENT_SOURCE_DIR}/input2_3.txt)
set_property(TEST TestTask2_AllDiff PROPERTY PASS_REGULAR_EXPRESSION "^\\(1,1\\) \\(2,1\\) \\(3,1\\) [\\r\\n]*$")

# серия с повторами
add_test(NAME TestTask2_Runs COMMAND lab1_task2 ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)
set_property(TEST TestTask2_Runs PROPERTY PASS_REGULAR_EXPRESSION "^\\(1,2\\) \\(2,1\\) \\(3,1\\) [\\r\\n]*$")
