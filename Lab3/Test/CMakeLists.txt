add_test(NAME Lab3Test1 COMMAND Lab3 ${CMAKE_CURRENT_SOURCE_DIR}/test1.txt ${CMAKE_CURRENT_BINARY_DIR}/output.txt &&
		${CMAKE_COMMAND} -E compare_files ${CMAKE_CURRENT_SOURCE_DIR}/test1-expected.txt ${CMAKE_CURRENT_BINARY_DIR}/output.txt)

add_test(NAME Lab3Test2 COMMAND Lab3 ${CMAKE_CURRENT_SOURCE_DIR}/test2.txt ${CMAKE_CURRENT_BINARY_DIR}/output.txt &&
		${CMAKE_COMMAND} -E compare_files ${CMAKE_CURRENT_SOURCE_DIR}/test2-expected.txt ${CMAKE_CURRENT_BINARY_DIR}/output.txt)

add_test(NAME Lab3Test3 COMMAND Lab3 ${CMAKE_CURRENT_SOURCE_DIR}/test3.txt ${CMAKE_CURRENT_BINARY_DIR}/output.txt &&
		${CMAKE_COMMAND} -E compare_files ${CMAKE_CURRENT_SOURCE_DIR}/test3-expected.txt ${CMAKE_CURRENT_BINARY_DIR}/output.txt)

add_test(NAME Lab3Test4 COMMAND Lab3 ${CMAKE_CURRENT_SOURCE_DIR}/test4.txt ${CMAKE_CURRENT_BINARY_DIR}/output.txt &&
		${CMAKE_COMMAND} -E compare_files ${CMAKE_CURRENT_SOURCE_DIR}/test4-expected.txt ${CMAKE_CURRENT_BINARY_DIR}/output.txt)

add_test(NAME Lab3Test5 COMMAND Lab3 ${CMAKE_CURRENT_SOURCE_DIR}/test5.txt ${CMAKE_CURRENT_BINARY_DIR}/output.txt &&
		${CMAKE_COMMAND} -E compare_files ${CMAKE_CURRENT_SOURCE_DIR}/test5-expected.txt ${CMAKE_CURRENT_BINARY_DIR}/output.txt)

add_test(NAME Lab3Test6 COMMAND Lab3 ${CMAKE_CURRENT_SOURCE_DIR}/test6.txt ${CMAKE_CURRENT_BINARY_DIR}/output.txt &&
		${CMAKE_COMMAND} -E compare_files ${CMAKE_CURRENT_SOURCE_DIR}/test6-expected.txt ${CMAKE_CURRENT_BINARY_DIR}/output.txt)
