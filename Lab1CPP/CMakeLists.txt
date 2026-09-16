 add_executable(Lab1CPP_Task1 lab1.cpp)
 target_include_directories(Lab1CPP_Task1 PUBLIC ../LibraryCPP)
 target_link_libraries(Lab1CPP_Task1 LibraryCPP)

 add_executable(Lab1CPP_Task2 lab2.cpp)
 target_include_directories(Lab1CPP_Task2 PUBLIC ../LibraryCPP)
 target_link_libraries(Lab1CPP_Task2 LibraryCPP)

 add_test(NAME TestLab1_Positive COMMAND Lab1CPP_Task1 ${CMAKE_CURRENT_SOURCE_DIR}/tests/lab1_positive.txt)
 set_property(TEST TestLab1_Positive PROPERTY PASS_REGULAR_EXPRESSION "10")

 add_test(NAME TestLab1_SingleDigits COMMAND Lab1CPP_Task1 ${CMAKE_CURRENT_SOURCE_DIR}/tests/lab1_single_digits.txt)
 set_property(TEST TestLab1_SingleDigits PROPERTY PASS_REGULAR_EXPRESSION "12")

 add_test(NAME TestLab1_Negative COMMAND Lab1CPP_Task1 ${CMAKE_CURRENT_SOURCE_DIR}/tests/lab1_negative.txt)
 set_property(TEST TestLab1_Negative PROPERTY PASS_REGULAR_EXPRESSION "6")

 add_test(NAME TestLab1_EmptyArray COMMAND Lab1CPP_Task1 ${CMAKE_CURRENT_SOURCE_DIR}/tests/lab1_empty_array.txt)
 set_property(TEST TestLab1_EmptyArray PROPERTY PASS_REGULAR_EXPRESSION "0")

 add_test(NAME TestLab2_Positive COMMAND Lab1CPP_Task2 ${CMAKE_CURRENT_SOURCE_DIR}/tests/lab2_positive.txt)
 set_property(TEST TestLab2_Positive PROPERTY PASS_REGULAR_EXPRESSION "1 2")

 add_test(NAME TestLab2_NoDuplicates COMMAND Lab1CPP_Task2 ${CMAKE_CURRENT_SOURCE_DIR}/tests/lab2_noduplicates.txt)

 add_test(NAME TestLab2_BoundaryLimits COMMAND Lab1CPP_Task2 ${CMAKE_CURRENT_SOURCE_DIR}/tests/lab2_boundary_limits.txt)
 set_property(TEST TestLab2_BoundaryLimits PROPERTY PASS_REGULAR_EXPRESSION "0 1000")

 add_test(NAME TestLab2_OutOfBounds COMMAND Lab1CPP_Task2 ${CMAKE_CURRENT_SOURCE_DIR}/tests/lab2_out_of_bounds.txt)
 set_property(TEST TestLab2_OutOfBounds PROPERTY WILL_FAIL TRUE)

 add_test(NAME TestLab2_InvalidSize COMMAND Lab1CPP_Task2 ${CMAKE_CURRENT_SOURCE_DIR}/tests/lab2_out_of_bounds.txt)
 set_property(TEST TestLab2_InvalidSize PROPERTY WILL_FAIL TRUE)