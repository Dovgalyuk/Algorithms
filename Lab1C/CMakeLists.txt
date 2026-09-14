add_executable(Task1CPP task1.cpp)
target_include_directories(Task1CPP PUBLIC ../LibraryCPP)
target_link_libraries(Task1CPP LibraryCPP)

add_test(NAME Task1_Test1 COMMAND $<TARGET_FILE:Task1CPP> ${CMAKE_CURRENT_SOURCE_DIR}/input_task1_1.txt)
set_property(TEST Task1_Test1 PROPERTY PASS_REGULAR_EXPRESSION "1 3 4 5")

add_test(NAME Task1_Test2 COMMAND $<TARGET_FILE:Task1CPP> ${CMAKE_CURRENT_SOURCE_DIR}/input_task1_2.txt)
set_property(TEST Task1_Test2 PROPERTY PASS_REGULAR_EXPRESSION "^[\r\n]*$")

add_executable(Task2CPP task2.cpp)
target_include_directories(Task2CPP PUBLIC ../LibraryCPP)
target_link_libraries(Task2CPP LibraryCPP)

add_test(NAME Task2_Test1 COMMAND $<TARGET_FILE:Task2CPP> ${CMAKE_CURRENT_SOURCE_DIR}/input_task2_1.txt)
set_property(TEST Task2_Test1 PROPERTY PASS_REGULAR_EXPRESSION "2")

add_test(NAME Task2_Test2 COMMAND $<TARGET_FILE:Task2CPP> ${CMAKE_CURRENT_SOURCE_DIR}/input_task2_2.txt)
set_property(TEST Task2_Test2 PROPERTY PASS_REGULAR_EXPRESSION "Нет различных четных чисел")