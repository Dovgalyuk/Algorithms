
add_executable(Lab1C_task4 task4.cpp)
target_include_directories(Lab1C_task4 PUBLIC ../LibraryCPP)
target_link_libraries(Lab1C_task4 LibraryCPP)

add_test(NAME Test1_task4 COMMAND Lab1C_task4 ${CMAKE_CURRENT_SOURCE_DIR}/input41.txt)
set_property(TEST Test1_task4 PROPERTY PASS_REGULAR_EXPRESSION "^3")

add_test(NAME Test2_task4 COMMAND Lab1C_task4 ${CMAKE_CURRENT_SOURCE_DIR}/input42.txt)
set_property(TEST Test2_task4 PROPERTY PASS_REGULAR_EXPRESSION "^4")

add_test(NAME Test3_task4 COMMAND Lab1C_task4 ${CMAKE_CURRENT_SOURCE_DIR}/input43.txt)
set_property(TEST Test3_task4 PROPERTY PASS_REGULAR_EXPRESSION "^9")

add_test(NAME Test4_task4 COMMAND Lab1C_task4 ${CMAKE_CURRENT_SOURCE_DIR}/input44.txt)
set_property(TEST Test4_task4 PROPERTY PASS_REGULAR_EXPRESSION "^0")

add_test(NAME Test5_task4 COMMAND Lab1C_task4 ${CMAKE_CURRENT_SOURCE_DIR}/input45.txt)
set_property(TEST Test5_task4 PROPERTY PASS_REGULAR_EXPRESSION "^3")

add_test(NAME Test6_task4 COMMAND Lab1C_task4 ${CMAKE_CURRENT_SOURCE_DIR}/input46.txt)
set_property(TEST Test6_task4 PROPERTY PASS_REGULAR_EXPRESSION "^0")

add_test(NAME Test7_task4 COMMAND Lab1C_task4 ${CMAKE_CURRENT_SOURCE_DIR}/input47.txt)
set_property(TEST Test7_task4 PROPERTY PASS_REGULAR_EXPRESSION "^0")


add_executable(Lab1C_task5 task5.cpp)
target_include_directories(Lab1C_task5 PUBLIC ../LibraryCPP)
target_link_libraries(Lab1C_task5 LibraryCPP)

add_test(NAME Test1_task5 COMMAND Lab1C_task5 ${CMAKE_CURRENT_SOURCE_DIR}/input51.txt)
set_property(TEST Test1_task5 PROPERTY PASS_REGULAR_EXPRESSION "^12 56 -89 0 0 0")

add_test(NAME Test2_task5 COMMAND Lab1C_task5 ${CMAKE_CURRENT_SOURCE_DIR}/input52.txt)
set_property(TEST Test2_task5 PROPERTY PASS_REGULAR_EXPRESSION "^-10 -3 7 -1 100 0 0 0")

add_test(NAME Test3_task5 COMMAND Lab1C_task5 ${CMAKE_CURRENT_SOURCE_DIR}/input53.txt)
set_property(TEST Test3_task5 PROPERTY PASS_REGULAR_EXPRESSION "^0 0 0 0 0")

add_test(NAME Test4_task5 COMMAND Lab1C_task5 ${CMAKE_CURRENT_SOURCE_DIR}/input54.txt)
set_property(TEST Test4_task5 PROPERTY PASS_REGULAR_EXPRESSION "^1 2 3 4")

add_test(NAME Test5_task5 COMMAND Lab1C_task5 ${CMAKE_CURRENT_SOURCE_DIR}/input55.txt)
set_property(TEST Test5_task5 PROPERTY PASS_REGULAR_EXPRESSION "^-4 0 5 0 0 0")

add_test(NAME Test6_task5 COMMAND Lab1C_task5 ${CMAKE_CURRENT_SOURCE_DIR}/input56.txt)
set_property(TEST Test6_task5 PROPERTY PASS_REGULAR_EXPRESSION "^0 0 0 0")

add_test(NAME Test7_task5 COMMAND Lab1C_task5 ${CMAKE_CURRENT_SOURCE_DIR}/input57.txt)
set_property(TEST Test7_task5 PROPERTY PASS_REGULAR_EXPRESSION "^-200 -150 -25 0 0 0 0")