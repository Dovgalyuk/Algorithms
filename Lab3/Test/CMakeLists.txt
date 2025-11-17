#add_test(NAME Lab3Test1
#		COMMAND ${CMAKE_COMMAND}
#		-DPROGRAM=$<TARGET_FILE:Lab3>
#		-DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/test1.txt
#		-DOUTPUT=${CMAKE_CURRENT_BINARY_DIR}/output1.txt
#		-DEXPECTED=${CMAKE_CURRENT_SOURCE_DIR}/test1-expected.txt
#		-P ${CMAKE_CURRENT_SOURCE_DIR}/run_test.cmake
#)

set(LAB3_TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/)
set(LAB3_BUILD_TEST_DIR ${CMAKE_CURRENT_BINARY_DIR}/)

set(TEST_NUMBERS 1 2 3 4 5 6)

foreach(N ${TEST_NUMBERS})
	set(INPUT_FILE    ${LAB3_TEST_DIR}/test${N}.txt)
	set(EXPECTED_FILE ${LAB3_TEST_DIR}/test${N}-expected.txt)
	set(OUTPUT_FILE   ${LAB3_BUILD_TEST_DIR}/output${N}.txt)

	add_test(NAME Lab3Test${N}
			COMMAND ${CMAKE_COMMAND}
			-DPROGRAM=$<TARGET_FILE:Lab3>
			-DINPUT=${INPUT_FILE}
			-DOUTPUT=${OUTPUT_FILE}
			-DEXPECTED=${EXPECTED_FILE}
			-P ${LAB3_TEST_DIR}/run_test.cmake
	)

	set_tests_properties(Lab3Test${N} PROPERTIES
			WORKING_DIRECTORY $<TARGET_FILE_DIR:Lab3>
	)
endforeach()

#add_test(NAME Lab3Test1 COMMAND Lab3 ${CMAKE_CURRENT_SOURCE_DIR}/test1.txt ${CMAKE_CURRENT_BINARY_DIR}/output.txt &&
#		${CMAKE_COMMAND} -E compare_files ${CMAKE_CURRENT_SOURCE_DIR}/test1-expected.txt ${CMAKE_CURRENT_BINARY_DIR}/output1.txt)

#add_test(NAME Lab3Test2 COMMAND Lab3 ${CMAKE_CURRENT_SOURCE_DIR}/test2.txt ${CMAKE_CURRENT_BINARY_DIR}/output.txt &&
#		${CMAKE_COMMAND} -E compare_files ${CMAKE_CURRENT_SOURCE_DIR}/test2-expected.txt ${CMAKE_CURRENT_BINARY_DIR}/output.txt)
#
#add_test(NAME Lab3Test3 COMMAND Lab3 ${CMAKE_CURRENT_SOURCE_DIR}/test3.txt ${CMAKE_CURRENT_BINARY_DIR}/output.txt &&
#		${CMAKE_COMMAND} -E compare_files ${CMAKE_CURRENT_SOURCE_DIR}/test3-expected.txt ${CMAKE_CURRENT_BINARY_DIR}/output.txt)
#
#add_test(NAME Lab3Test4 COMMAND Lab3 ${CMAKE_CURRENT_SOURCE_DIR}/test4.txt ${CMAKE_CURRENT_BINARY_DIR}/output.txt &&
#		${CMAKE_COMMAND} -E compare_files ${CMAKE_CURRENT_SOURCE_DIR}/test4-expected.txt ${CMAKE_CURRENT_BINARY_DIR}/output.txt)
#
#add_test(NAME Lab3Test5 COMMAND Lab3 ${CMAKE_CURRENT_SOURCE_DIR}/test5.txt ${CMAKE_CURRENT_BINARY_DIR}/output.txt &&
#		${CMAKE_COMMAND} -E compare_files ${CMAKE_CURRENT_SOURCE_DIR}/test5-expected.txt ${CMAKE_CURRENT_BINARY_DIR}/output.txt)
#
#add_test(NAME Lab3Test6 COMMAND Lab3 ${CMAKE_CURRENT_SOURCE_DIR}/test6.txt ${CMAKE_CURRENT_BINARY_DIR}/output.txt &&
#		${CMAKE_COMMAND} -E compare_files ${CMAKE_CURRENT_SOURCE_DIR}/test6-expected.txt ${CMAKE_CURRENT_BINARY_DIR}/output.txt)
