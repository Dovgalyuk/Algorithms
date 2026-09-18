add_test(
	NAME Task1Test1
	COMMAND TASK1 ${CMAKE_CURRENT_SOURCE_DIR}/task1_test1.txt
)

set_tests_properties(
	Task1Test1
	PROPERTIES
	PASS_REGULAR_EXPRESSION "Quantity 2: 4\nQuantity 3: 4\nQuantity 4: 3\nQuantity 5: 4"
)

add_test(
	NAME Task1Test2
	COMMAND TASK1 ${CMAKE_CURRENT_SOURCE_DIR}/task1_test2.txt
)

set_tests_properties(
	Task1Test2
	PROPERTIES
	PASS_REGULAR_EXPRESSION "Quantity 2: 4\nQuantity 3: 3\nQuantity 4: 5\nQuantity 5: 4"
)

add_test(
	NAME Task1
	COMMAND TASK1 ${CMAKE_CURRENT_SOURCE_DIR}/task1.txt
)

set_tests_properties(
	Task1
	PROPERTIES
	PASS_REGULAR_EXPRESSION "Quantity 2: 4\nQuantity 3: 5\nQuantity 4: 7\nQuantity 5: 4"
)

add_test(
	NAME Task2Test1
	COMMAND TASK2 ${CMAKE_CURRENT_SOURCE_DIR}/task2_test1.txt
)

set_tests_properties(
	Task2Test1
	PROPERTIES
	PASS_REGULAR_EXPRESSION "The maximum sum of 5 adjacent elements: 366"
)

add_test(
	NAME Task2Test2
	COMMAND TASK2 ${CMAKE_CURRENT_SOURCE_DIR}/task2_test2.txt
)

set_tests_properties(
	Task2Test2
	PROPERTIES
	PASS_REGULAR_EXPRESSION "The maximum sum of 5 adjacent elements: 369"
)

add_test(
	NAME Task2
	COMMAND TASK2 ${CMAKE_CURRENT_SOURCE_DIR}/task2.txt
)

set_tests_properties(
	Task2
	PROPERTIES
	PASS_REGULAR_EXPRESSION "The maximum sum of 5 adjacent elements: 325"
)