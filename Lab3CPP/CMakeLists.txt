add_executable(Lab3CPP lab3.cpp)
target_include_directories(Lab3CPP PUBLIC ../LibraryCPPClass)
target_link_libraries(Lab3CPP LibraryCPPClass)

add_test(NAME your_first_test COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/test/test1.txt)
set_property(TEST your_first_test PROPERTY PASS_REGULAR_EXPRESSION "3")

add_test(NAME simple_work_program COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/test/test2.txt)
set_property(TEST simple_work_program PROPERTY PASS_REGULAR_EXPRESSION "1")

add_test(NAME checking_walls_and_fields COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/test/test3.txt)
set_property(TEST checking_walls_and_fields PROPERTY PASS_REGULAR_EXPRESSION "0")

add_test(NAME аlmost_free_field COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/test/test4.txt)
set_property(TEST аlmost_free_field PROPERTY PASS_REGULAR_EXPRESSION "4")

add_test(NAME diagonal_movement COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/test/test5.txt)
set_property(TEST diagonal_movement PROPERTY PASS_REGULAR_EXPRESSION "1")

add_test(NAME hard_movment_test COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/test/test6.txt)
set_property(TEST hard_movment_test PROPERTY PASS_REGULAR_EXPRESSION "2")