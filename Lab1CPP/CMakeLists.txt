#task1
add_executable(Lab1CPP1 task1.cpp)
target_include_directories(Lab1CPP1 PUBLIC ../LibraryCPP)
target_link_libraries(Lab1CPP1 LibraryCPP)

add_test(NAME Test1Lab1CPP COMMAND Lab1CPP1 ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt)
set_property(TEST Test1Lab1CPP PROPERTY PASS_REGULAR_EXPRESSION "2")

add_test(NAME Test11Lab1CPP COMMAND Lab1CPP1 ${CMAKE_CURRENT_SOURCE_DIR}/input11.txt)
set_property(TEST Test11Lab1CPP PROPERTY PASS_REGULAR_EXPRESSION "6")

add_test(NAME Test12Lab1CPP COMMAND Lab1CPP1 ${CMAKE_CURRENT_SOURCE_DIR}/input12.txt)
set_property(TEST Test12Lab1CPP PROPERTY PASS_REGULAR_EXPRESSION "10")

#task2
add_executable(Lab1CPP2 task2.cpp)
target_include_directories(Lab1CPP2 PUBLIC ../LibraryCPP)
target_link_libraries(Lab1CPP2 LibraryCPP)

add_test(NAME Test2Lab2CPP COMMAND Lab1CPP2 ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)
set_property(TEST Test2Lab2CPP PROPERTY PASS_REGULAR_EXPRESSION "5 7 ")

add_test(NAME Test21Lab2CPP COMMAND Lab1CPP2 ${CMAKE_CURRENT_SOURCE_DIR}/input21.txt)
set_property(TEST Test21Lab2CPP PROPERTY PASS_REGULAR_EXPRESSION "5 7 10 ")

add_test(NAME Test22Lab2CPP COMMAND Lab1CPP2 ${CMAKE_CURRENT_SOURCE_DIR}/input22.txt)
set_property(TEST Test22Lab2CPP PROPERTY PASS_REGULAR_EXPRESSION "3 700 1000 ")