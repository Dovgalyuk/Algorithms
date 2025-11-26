add_executable(TestList list.cpp)
target_include_directories(TestList PUBLIC ../../LibraryCPPClass)
target_link_libraries(TestList LibraryCPPClass)
add_test(TestList TestList)

add_executable(TestStack stack.cpp)
target_include_directories(TestStack PUBLIC ../../LibraryCPPClass)
target_link_libraries(TestStack LibraryCPPClass)
add_test(TestStack TestStack)

add_test(NAME ASBase COMMAND Lab2CPP -inter ${CMAKE_CURRENT_SOURCE_DIR}/testscript1.txt ${CMAKE_CURRENT_SOURCE_DIR}/emptyInput.txt)
set_property(TEST ASBase PROPERTY PASS_REGULAR_EXPRESSION "Console output: \nC\nB\nA")

add_test(NAME ASAdd COMMAND Lab2CPP -inter ${CMAKE_CURRENT_SOURCE_DIR}/testscript2.txt ${CMAKE_CURRENT_SOURCE_DIR}/emptyInput.txt)
set_property(TEST ASAdd PROPERTY PASS_REGULAR_EXPRESSION "Console output: \nA\nB")

add_test(NAME ASRemove COMMAND Lab2CPP -inter ${CMAKE_CURRENT_SOURCE_DIR}/testscript3.txt ${CMAKE_CURRENT_SOURCE_DIR}/emptyInput.txt)
set_property(TEST ASRemove PROPERTY PASS_REGULAR_EXPRESSION "Console output: \nA")

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
set_property(TEST ASDoubleInput PROPERTY PASS_REGULAR_EXPRESSION "Console output: \n2\nA\n5")

add_test(NAME ASConcat COMMAND Lab2CPP -inter ${CMAKE_CURRENT_SOURCE_DIR}/testscript9.txt ${CMAKE_CURRENT_SOURCE_DIR}/emptyInput.txt)
set_property(TEST ASConcat PROPERTY PASS_REGULAR_EXPRESSION "Console output: \nCBA")

add_test(NAME ASIFTrue COMMAND Lab2CPP -inter ${CMAKE_CURRENT_SOURCE_DIR}/testscript10.txt ${CMAKE_CURRENT_SOURCE_DIR}/input3.txt)
set_property(TEST ASIFTrue PROPERTY PASS_REGULAR_EXPRESSION "Console output: 1E\n1E")

add_test(NAME ASIFFalse COMMAND Lab2CPP -inter ${CMAKE_CURRENT_SOURCE_DIR}/testscript10.txt ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt)
set_property(TEST ASIFFalse PROPERTY PASS_REGULAR_EXPRESSION "Console output: \n25")

add_test(NAME ASIFHalted COMMAND Lab2CPP -inter ${CMAKE_CURRENT_SOURCE_DIR}/testscript11.txt ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt)
set_property(TEST ASIFHalted PROPERTY PASS_REGULAR_EXPRESSION "Console output: Program Halted\n25")

add_test(NAME ASClearOutput COMMAND Lab2CPP -inter ${CMAKE_CURRENT_SOURCE_DIR}/testscript12.txt ${CMAKE_CURRENT_SOURCE_DIR}/emptyInput.txt)
set_property(TEST ASClearOutput PROPERTY PASS_REGULAR_EXPRESSION "Console output: \nA\nB")

add_test(NAME ASFreeze COMMAND Lab2CPP -inter ${CMAKE_CURRENT_SOURCE_DIR}/testscript13.txt ${CMAKE_CURRENT_SOURCE_DIR}/emptyInput.txt)
set_property(TEST ASFreeze PROPERTY TIMEOUT 3)

add_test(NAME ASRandom COMMAND Lab2CPP -inter ${CMAKE_CURRENT_SOURCE_DIR}/testscript14.txt ${CMAKE_CURRENT_SOURCE_DIR}/emptyInput.txt)
set_property(TEST ASRandom PROPERTY PASS_REGULAR_EXPRESSION "[1-9]")

add_test(NAME ASVariable COMMAND Lab2CPP -inter ${CMAKE_CURRENT_SOURCE_DIR}/testscript15.txt ${CMAKE_CURRENT_SOURCE_DIR}/emptyInput.txt)
set_property(TEST ASVariable PROPERTY PASS_REGULAR_EXPRESSION "Console output: 1\n1")

add_test(NAME ASSpecified COMMAND Lab2CPP -inter ${CMAKE_CURRENT_SOURCE_DIR}/testscript16.txt ${CMAKE_CURRENT_SOURCE_DIR}/emptyInput.txt)
set_property(TEST ASSpecified PROPERTY PASS_REGULAR_EXPRESSION "Console output: E\nE")

add_test(NAME ASSetsValue COMMAND Lab2CPP -inter ${CMAKE_CURRENT_SOURCE_DIR}/testscript17.txt ${CMAKE_CURRENT_SOURCE_DIR}/emptyInput.txt)
set_property(TEST ASSetsValue PROPERTY PASS_REGULAR_EXPRESSION "Console output: E4\nE\n4")

add_test(NAME ASReplaceValue COMMAND Lab2CPP -inter ${CMAKE_CURRENT_SOURCE_DIR}/testscript18.txt ${CMAKE_CURRENT_SOURCE_DIR}/emptyInput.txt)
set_property(TEST ASReplaceValue PROPERTY PASS_REGULAR_EXPRESSION "Console output: E\nE\n4")