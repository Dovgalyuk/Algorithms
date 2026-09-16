add_executable(Task4Sum labatask4.cpp)
target_include_directories(Task4Sum PUBLIC ../LibraryCPPTemplate)

add_test(NAME TestTask4Sum1 COMMAND Task4Sum ${CMAKE_CURRENT_SOURCE_DIR}/suminput1.txt)
set_property(TEST TestTask4Sum1 PROPERTY PASS_REGULAR_EXPRESSION "^9")

add_test(NAME TestTask4Sum2 COMMAND Task4Sum ${CMAKE_CURRENT_SOURCE_DIR}/suminput2.txt)
set_property(TEST TestTask4Sum2 PROPERTY PASS_REGULAR_EXPRESSION "^4")

add_test(NAME TestTask4Sum3 COMMAND Task4Sum ${CMAKE_CURRENT_SOURCE_DIR}/suminput3.txt)
set_property(TEST TestTask4Sum3 PROPERTY PASS_REGULAR_EXPRESSION "^15")

add_test(NAME TestTask4Sum4 COMMAND Task4Sum ${CMAKE_CURRENT_SOURCE_DIR}/suminput4.txt)
set_property(TEST TestTask4Sum4 PROPERTY PASS_REGULAR_EXPRESSION "^0")

add_test(NAME TestTask4Sum5 COMMAND Task4Sum ${CMAKE_CURRENT_SOURCE_DIR}/suminput5.txt)
set_property(TEST TestTask4Sum5 PROPERTY PASS_REGULAR_EXPRESSION "^3")

add_executable(Task5Compress labatask5.cpp)
target_include_directories(Task5Compress PUBLIC ../LibraryCPPTemplate)

add_test(NAME TestTask5Compress1 COMMAND Task5Compress ${CMAKE_CURRENT_SOURCE_DIR}/compressinput1.txt)
set_property(TEST TestTask5Compress1 PROPERTY PASS_REGULAR_EXPRESSION "^1 9 8 2 0 0 0")

add_test(NAME TestTask5Compress2 COMMAND Task5Compress ${CMAKE_CURRENT_SOURCE_DIR}/compressinput2.txt)
set_property(TEST TestTask5Compress2 PROPERTY PASS_REGULAR_EXPRESSION "^5 7 9 0 0 0")

add_test(NAME TestTask5Compress3 COMMAND Task5Compress ${CMAKE_CURRENT_SOURCE_DIR}/compressinput3.txt)
set_property(TEST TestTask5Compress3 PROPERTY PASS_REGULAR_EXPRESSION "^1 2 3 4 5")

add_test(NAME TestTask5Compress4 COMMAND Task5Compress ${CMAKE_CURRENT_SOURCE_DIR}/compressinput4.txt)
set_property(TEST TestTask5Compress4 PROPERTY PASS_REGULAR_EXPRESSION "^0 0 0 0")

add_test(NAME TestTask5Compress5 COMMAND Task5Compress ${CMAKE_CURRENT_SOURCE_DIR}/compressinput5.txt)
set_property(TEST TestTask5Compress5 PROPERTY PASS_REGULAR_EXPRESSION "^-5 6 8 0 0 0 0")
