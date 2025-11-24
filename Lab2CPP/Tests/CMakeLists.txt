add_test(NAME TestListBasic COMMAND Lab2CPP -list 5)
set_property(TEST TestListBasic PROPERTY PASS_REGULAR_EXPRESSION "5 4 3 2 1")

add_test(NAME TestListCopy COMMAND Lab2CPP -list -c)
set_property(TEST TestListCopy PROPERTY PASS_REGULAR_EXPRESSION "1")

add_test(NAME TestListAssignment COMMAND Lab2CPP -list -a)
set_property(TEST TestListAssignment PROPERTY PASS_REGULAR_EXPRESSION "1")

add_test(NAME TestStackBas COMMAND Lab2CPP -stack ${CMAKE_CURRENT_SOURCE_DIR}/test.txt)
set_property(TEST TestStackBas PROPERTY PASS_REGULAR_EXPRESSION "YES")

add_test(NAME ASBase COMMAND Lab2CPP -inter ${CMAKE_CURRENT_SOURCE_DIR}/testscript1.txt ${CMAKE_CURRENT_SOURCE_DIR}/emptyInput.txt)
set_property(TEST ASBase PROPERTY PASS_REGULAR_EXPRESSION "C\nB\nA")

add_test(NAME ASAdd COMMAND Lab2CPP -inter ${CMAKE_CURRENT_SOURCE_DIR}/testscript2.txt ${CMAKE_CURRENT_SOURCE_DIR}/emptyInput.txt)
set_property(TEST ASAdd PROPERTY PASS_REGULAR_EXPRESSION "A\nB")

add_test(NAME ASRemove COMMAND Lab2CPP -inter ${CMAKE_CURRENT_SOURCE_DIR}/testscript3.txt ${CMAKE_CURRENT_SOURCE_DIR}/emptyInput.txt)
set_property(TEST ASRemove PROPERTY PASS_REGULAR_EXPRESSION "A")

set_tests_properties(ASRemove PROPERTIES
    FAIL_REGULAR_EXPRESSION "B"
)

add_test(NAME ASOutPut COMMAND Lab2CPP -inter ${CMAKE_CURRENT_SOURCE_DIR}/testscript4.txt ${CMAKE_CURRENT_SOURCE_DIR}/emptyInput.txt)
set_property(TEST ASOutPut PROPERTY PASS_REGULAR_EXPRESSION "Console output: Hello World")

add_test(NAME ASVar COMMAND Lab2CPP -inter ${CMAKE_CURRENT_SOURCE_DIR}/testscript5.txt ${CMAKE_CURRENT_SOURCE_DIR}/emptyInput.txt)
set_property(TEST ASVar PROPERTY PASS_REGULAR_EXPRESSION "Console output: B\nA\nB")

add_test(NAME ASVarClear COMMAND Lab2CPP -inter ${CMAKE_CURRENT_SOURCE_DIR}/testscript6.txt ${CMAKE_CURRENT_SOURCE_DIR}/emptyInput.txt)
set_property(TEST ASVarClear PROPERTY PASS_REGULAR_EXPRESSION "Console output: \nA\nB\nC\nE")

add_test(NAME ASInput COMMAND Lab2CPP -inter ${CMAKE_CURRENT_SOURCE_DIR}/testscript7.txt ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt)
set_property(TEST ASInput PROPERTY PASS_REGULAR_EXPRESSION "Console output: 25\n25\nA")

add_test(NAME ASDoubleInput COMMAND Lab2CPP -inter ${CMAKE_CURRENT_SOURCE_DIR}/testscript8.txt ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)
set_property(TEST ASDoubleInput PROPERTY PASS_REGULAR_EXPRESSION "2\nA\n5")
