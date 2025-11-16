add_executable(Lab2CPP lab2.cpp)
target_include_directories(Lab2CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab2CPP LibraryCPP)

add_test(NAME your_first_test COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/TestTXT/text1.txt)
set_property(TEST your_first_test PROPERTY PASS_REGULAR_EXPRESSION "1.*3.*2")

add_test(NAME your_second_test COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/TestTXT/text2.txt)
set_property(TEST your_second_test PROPERTY PASS_REGULAR_EXPRESSION "1.*2.*3.*6")

add_test(NAME test_summ COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/TestTXT/text3.txt)
set_property(TEST test_summ PROPERTY PASS_REGULAR_EXPRESSION "3.*18")

add_test(NAME test_division COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/TestTXT/text4.txt)
set_property(TEST test_division PROPERTY PASS_REGULAR_EXPRESSION "1.*1.*1.*2.*2")

add_test(NAME test_division_by_zero COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/TestTXT/text4-1.txt)
set_property(TEST test_division_by_zero PROPERTY PASS_REGULAR_EXPRESSION "division by zero error.*stack empty")

add_test(NAME test_remainder COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/TestTXT/text5.txt)
set_property(TEST test_remainder PROPERTY PASS_REGULAR_EXPRESSION "1.*0")

add_test(NAME test_dup COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/TestTXT/text6.txt)
set_property(TEST test_dup PROPERTY PASS_REGULAR_EXPRESSION "3.*3.*2")

add_test(NAME test_swap COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/TestTXT/text7.txt)
set_property(TEST test_swap PROPERTY PASS_REGULAR_EXPRESSION "1.*2.*0.*1")

add_test(NAME test_drop COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/TestTXT/text8.txt)
set_property(TEST test_drop PROPERTY PASS_REGULAR_EXPRESSION "1")

add_test(NAME test_over COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/TestTXT/text9.txt)
set_property(TEST test_over PROPERTY PASS_REGULAR_EXPRESSION "9.*5.*5")

add_test(NAME test_rot COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/TestTXT/text10.txt)
set_property(TEST test_rot PROPERTY PASS_REGULAR_EXPRESSION "8.*0.*9.*7.*6.*5.*4.*3.*2.*1")