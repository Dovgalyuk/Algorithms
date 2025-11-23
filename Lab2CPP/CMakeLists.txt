add_executable(Lab2CPP lab2.cpp)
target_include_directories(Lab2CPP PUBLIC ../LibraryCPPClass)
target_link_libraries(Lab2CPP LibraryCPPClass)

add_test(NAME TestListBasic COMMAND Lab2CPP -list 5)

set_property(TEST TestListBasic PROPERTY PASS_REGULAR_EXPRESSION "1 2 3 4 5 ")


add_test(NAME TestStackBas COMMAND Lab2CPP -stack ${CMAKE_CURRENT_SOURCE_DIR}/test.txt)

set_property(TEST TestStackBas PROPERTY PASS_REGULAR_EXPRESSION "YES")