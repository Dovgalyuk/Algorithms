add_executable(Lab1CPP1 task1.cpp)
target_include_directories(Lab1CPP1 PUBLIC ../LibraryCPP)
target_link_libraries(Lab1CPP1 LibraryCPP)

add_test(NAME Test1Lab1CPP COMMAND Lab1CPP1 ${CMAKE_CURRENT_SOURCE_DIR}/task1_test1.txt)
set_property(TEST Test1Lab1CPP PROPERTY PASS_REGULAR_EXPRESSION "16")

add_test(NAME Test2Lab1CPP COMMAND Lab1CPP1 ${CMAKE_CURRENT_SOURCE_DIR}/task1_test2.txt)
set_property(TEST Test2Lab1CPP PROPERTY PASS_REGULAR_EXPRESSION "25")

add_test(NAME Test3Lab1CPP COMMAND Lab1CPP1 ${CMAKE_CURRENT_SOURCE_DIR}/task1_test3.txt)
set_property(TEST Test3Lab1CPP PROPERTY PASS_REGULAR_EXPRESSION "51")

add_executable(Lab1CPP2 task2.cpp)
target_include_directories(Lab1CPP2 PUBLIC ../LibraryCPP)
target_link_libraries(Lab1CPP2 LibraryCPP)

add_test(NAME Test1Lab2CPP COMMAND Lab1CPP2 ${CMAKE_CURRENT_SOURCE_DIR}/task2_test1.txt)
set_property(TEST Test1Lab2CPP PROPERTY PASS_REGULAR_EXPRESSION "15")

add_test(NAME Test2Lab2CPP COMMAND Lab1CPP2 ${CMAKE_CURRENT_SOURCE_DIR}/task2_test2.txt)
set_property(TEST Test2Lab2CPP PROPERTY PASS_REGULAR_EXPRESSION "50")

add_test(NAME Test3Lab2CPP COMMAND Lab1CPP2 ${CMAKE_CURRENT_SOURCE_DIR}/task2_test3.txt)
set_property(TEST Test3Lab2CPP PROPERTY PASS_REGULAR_EXPRESSION "5")