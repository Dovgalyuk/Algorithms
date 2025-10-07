add_executable(TestArrayCPP array.cpp)
target_include_directories(TestArrayCPP PUBLIC ..)
target_link_libraries(TestArrayCPP CustomLibrary)

add_test(NAME FirstTest COMMAND CustomLibraryApp ${CMAKE_CURRENT_SOURCE_DIR}/firstTestData.txt)

set_tests_properties(FirstTest PROPERTIES 
	PASS_REGULAR_EXPRESSION "7[ \t\r\n]+\\(0, 0, 0, 10, 9, 8, 7, 6, 5, 4\\)"
)

add_test(NAME SecondTest COMMAND CustomLibraryApp ${CMAKE_CURRENT_SOURCE_DIR}/secondTestData.txt)

set_tests_properties(SecondTest PROPERTIES 
	PASS_REGULAR_EXPRESSION "49[ \t\r\n]+\\(23, 22, 15, 19, 0, 0, 0, 0, 0, 0, 0\\)"
)

add_test(TestArrayCPP TestArrayCPP)