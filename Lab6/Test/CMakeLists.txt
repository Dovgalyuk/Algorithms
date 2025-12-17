add_test(NAME Test1 COMMAND Lab6 ${CMAKE_CURRENT_SOURCE_DIR}/testData1.txt)

set_tests_properties(Test1 PROPERTIES
	PASS_REGULAR_EXPRESSION "150[ \t\r\n]+5x10\\*10x3"
)

add_test(NAME Test2 COMMAND Lab6 ${CMAKE_CURRENT_SOURCE_DIR}/testData2.txt)

set_tests_properties(Test2 PROPERTIES
	PASS_REGULAR_EXPRESSION "4500[ \t\r\n]+\\(10x30\\*30x5\\)\\*5x60"
)

add_test(NAME Test3 COMMAND Lab6 ${CMAKE_CURRENT_SOURCE_DIR}/testData3.txt)

set_tests_properties(Test3 PROPERTIES
		PASS_REGULAR_EXPRESSION "7500[ \t\r\n]+\\(10x100\\*100x5\\)\\*5x50"
)

add_test(NAME Test4 COMMAND Lab6 ${CMAKE_CURRENT_SOURCE_DIR}/testData4.txt)

set_tests_properties(Test4 PROPERTIES
		PASS_REGULAR_EXPRESSION "158[ \t\r\n]+\\(5x4\\*\\(4x6\\*6x2\\)\\)\\*2x7"
)

add_test(NAME Test5 COMMAND Lab6 ${CMAKE_CURRENT_SOURCE_DIR}/testData5.txt)

set_tests_properties(Test5 PROPERTIES
		PASS_REGULAR_EXPRESSION "15125[ \t\r\n]+\\(30x35\\*\\(35x15\\*15x5\\)\\)\\*\\(\\(5x10\\*10x20\\)\\*20x25\\)"
)


add_test(NAME BenchmarkOutputTest COMMAND Lab6 --benchmark)

set_tests_properties(BenchmarkOutputTest PROPERTIES
		PASS_REGULAR_EXPRESSION
		"n[ \t]+Exhaustive \\(ns\\)[ \t]+DP \\(ns\\)\n[-]+\n.*\nBenchmark completed\\.\nResults saved to .+\\.csv\n"
)
