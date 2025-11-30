add_executable(Lab3CPP lab3.cpp)
target_include_directories(Lab3CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab3CPP LibraryCPP)
set_target_properties(Lab3CPP PROPERTIES CXX_STANDARD 20)
set_target_properties(Lab3CPP PROPERTIES CXX_STANDARD_REQUIRED ON)

add_test(NAME Test1 COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_property(TEST Test1 PROPERTY PASS_REGULAR_EXPRESSION "Start City1 City2 End")
add_test(NAME Test2 COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/test2.txt)
set_property(TEST Test2 PROPERTY PASS_REGULAR_EXPRESSION "City1 City4")

add_test(NAME Test3.3 COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/test3.txt)
set_property(TEST Test3.3 PROPERTY WILL_FAIL TRUE)

add_test(NAME Test4 COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/test4.txt)
set_property(TEST Test4 PROPERTY PASS_REGULAR_EXPRESSION "City1")

add_test(NAME Test5 COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/test5.txt)
set_property(TEST Test5 PROPERTY PASS_REGULAR_EXPRESSION "Start City1 End")

add_test(NAME Test6 COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/test6.txt)
set_property(TEST Test6 PROPERTY WILL_FAIL TRUE)