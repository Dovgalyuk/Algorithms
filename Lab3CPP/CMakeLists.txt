add_library(Lab3Containers STATIC
    ${CMAKE_SOURCE_DIR}/LibraryCPP/vector.cpp
    ${CMAKE_SOURCE_DIR}/LibraryCPP/queue.cpp
)

target_include_directories(Lab3Containers PUBLIC
    ${CMAKE_SOURCE_DIR}/LibraryCPP
)

add_executable(Lab3CPP main.cpp)

target_link_libraries(Lab3CPP PRIVATE Lab3Containers)

add_test(NAME Lab3CPPTest1
    COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/test1.txt
)
set_tests_properties(Lab3CPPTest1 PROPERTIES
    PASS_REGULAR_EXPRESSION "^1"
)

add_test(NAME Lab3CPPTest2
    COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/test2.txt
)
set_tests_properties(Lab3CPPTest2 PROPERTIES
    PASS_REGULAR_EXPRESSION "^0"
)

add_test(NAME Lab3CPPTest3
    COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/test3.txt
)
set_tests_properties(Lab3CPPTest3 PROPERTIES
    PASS_REGULAR_EXPRESSION "^0"
)

add_test(NAME Lab3CPPTest4
    COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/test4.txt
)
set_tests_properties(Lab3CPPTest4 PROPERTIES
    PASS_REGULAR_EXPRESSION "Invalid maze"
)

add_test(NAME Lab3CPPTest5
    COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/test5.txt
)
set_tests_properties(Lab3CPPTest5 PROPERTIES
    PASS_REGULAR_EXPRESSION "^4"
)

add_test(NAME Lab3CPPTest6
    COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/test6.txt
)
set_tests_properties(Lab3CPPTest6 PROPERTIES
    PASS_REGULAR_EXPRESSION "^7"
)

add_test(NAME Lab3CPPTest7
    COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/test7.txt
)
set_tests_properties(Lab3CPPTest7 PROPERTIES
    PASS_REGULAR_EXPRESSION "^6"
)

add_test(NAME Lab3CPPTest8
    COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/test8.txt
)
set_tests_properties(Lab3CPPTest8 PROPERTIES
    PASS_REGULAR_EXPRESSION "^2"
)
