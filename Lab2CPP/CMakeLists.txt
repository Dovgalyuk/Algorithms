add_executable(Calculon calculon.cpp)
target_include_directories(Calculon PUBLIC ../LibraryCPP)
target_link_libraries(Calculon LibraryCPP)

add_test(NAME TestHello COMMAND Calculon ${CMAKE_CURRENT_SOURCE_DIR}/hello.txt ${CMAKE_CURRENT_SOURCE_DIR}/empty.txt)
set_property(TEST TestHello PROPERTY PASS_REGULAR_EXPRESSION "72 101 108 111 44 32 119 114 108 100 33 10")

add_test(NAME TestArithmetic COMMAND Calculon ${CMAKE_CURRENT_SOURCE_DIR}/arith.txt ${CMAKE_CURRENT_SOURCE_DIR}/empty.txt)
set_property(TEST TestArithmetic PROPERTY PASS_REGULAR_EXPRESSION "14")

add_test(NAME TestGet COMMAND Calculon ${CMAKE_CURRENT_SOURCE_DIR}/get.txt ${CMAKE_CURRENT_SOURCE_DIR}/get_data.txt)
set_property(TEST TestGet PROPERTY PASS_REGULAR_EXPRESSION "15")

add_test(NAME TestCondEqual COMMAND Calculon ${CMAKE_CURRENT_SOURCE_DIR}/cond_equal.txt ${CMAKE_CURRENT_SOURCE_DIR}/empty.txt)
set_property(TEST TestCondEqual PROPERTY PASS_REGULAR_EXPRESSION "100")

add_test(NAME TestCondNotEqual COMMAND Calculon ${CMAKE_CURRENT_SOURCE_DIR}/cond_not_equal.txt ${CMAKE_CURRENT_SOURCE_DIR}/empty.txt)
set_property(TEST TestCondNotEqual PROPERTY PASS_REGULAR_EXPRESSION "7")

add_test(NAME TestRepeat COMMAND Calculon ${CMAKE_CURRENT_SOURCE_DIR}/loop.txt ${CMAKE_CURRENT_SOURCE_DIR}/empty.txt)
set_property(TEST TestRepeat PROPERTY PASS_REGULAR_EXPRESSION "1 12")