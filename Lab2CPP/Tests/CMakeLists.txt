add_test(NAME TestListBasic COMMAND Lab2CPP -list 5)
set_property(TEST TestListBasic PROPERTY PASS_REGULAR_EXPRESSION "1 2 3 4 5 ")


add_test(NAME TestStackBas COMMAND Lab2CPP -stack ${CMAKE_CURRENT_SOURCE_DIR}/test.txt)
set_property(TEST TestStackBas PROPERTY PASS_REGULAR_EXPRESSION "YES")

add_test(NAME AnnoyingScriptBase COMMAND Lab2CPP -inter ${CMAKE_CURRENT_SOURCE_DIR}/testscript1.txt ${CMAKE_CURRENT_SOURCE_DIR}/emptyInput.txt)
set_property(TEST AnnoyingScriptBase PROPERTY PASS_REGULAR_EXPRESSION "C B A")