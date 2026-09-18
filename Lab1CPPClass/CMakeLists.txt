add_executable(Lab1_1 lab1_1.cpp)
target_include_directories(Lab1_1 PUBLIC ../LibraryCPPClass)
target_link_libraries(Lab1_1 LibraryCPPClass)

add_executable(Lab1_2 lab1_2.cpp)
target_include_directories(Lab1_2 PUBLIC ../LibraryCPPClass)
target_link_libraries(Lab1_2 LibraryCPPClass)

add_test(NAME TestLab1_1_Work COMMAND Lab1_1 ${CMAKE_CURRENT_SOURCE_DIR}/text1_1.txt)
set_property(TEST TestLab1_1_Work PROPERTY PASS_REGULAR_EXPRESSION "Min: 2.*Min_two: 3")

add_test(NAME TestLab1_2_Identical COMMAND Lab1_1 ${CMAKE_CURRENT_SOURCE_DIR}/text1_2.txt)
set_property(TEST TestLab1_2_Identical PROPERTY PASS_REGULAR_EXPRESSION "Min: 3.*Min_two: 3")

add_test(NAME TestLab2_1_Work COMMAND Lab1_2 ${CMAKE_CURRENT_SOURCE_DIR}/text2_1.txt)
set_property(TEST TestLab2_1_Work PROPERTY PASS_REGULAR_EXPRESSION "Числа которые встречаются один раз: 8 99 7")

add_test(NAME TestLab2_1_Bignum COMMAND Lab1_2 ${CMAKE_CURRENT_SOURCE_DIR}/text2_2.txt)
set_property(TEST TestLab2_1_Bignum PROPERTY PASS_REGULAR_EXPRESSION "Числа которые встречаются один раз: 500")