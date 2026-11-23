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
    PASS_REGULAR_EXPRESSION "^8"
)

add_test(NAME Lab3CPPTest2
    COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/test2.txt
)
set_tests_properties(Lab3CPPTest2 PROPERTIES
    PASS_REGULAR_EXPRESSION "^2"
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
