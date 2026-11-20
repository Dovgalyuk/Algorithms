add_executable(Labirint main.cpp labirint.cpp)
target_link_libraries(Labirint PRIVATE LibraryCPP)

enable_testing()

macro(add_labirint_test TEST_NOMER)
	add_test(NAME Labirint_${TEST_NOMER}
		COMMAND ${CMAKE_COMMAND}
		-DLabirint=$<TARGET_FILE:Labirint>
		-DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/tests/input_${TEST_NOMER}.txt
		-DOUTPUT=${CMAKE_CURRENT_BINARY_DIR}/vivod_${TEST_NOMER}.txt
		-DEXPECTED=${CMAKE_CURRENT_SOURCE_DIR}//tests/otvet_${TEST_NOMER}.txt
		-P ${CMAKE_CURRENT_SOURCE_DIR}/run_labirint_test.cmake
	)
endmacro()

add_labirint_test(1)
add_labirint_test(2)
add_labirint_test(3)
add_labirint_test(4)
add_labirint_test(5)
add_labirint_test(6)
add_labirint_test(7)
add_labirint_test(8)
add_labirint_test(9)
add_labirint_test(10)



add_custom_target(test_labirint COMMAND ${CMAKE_CTEST_COMMAND} -C $<CONFIG> --output-on-failure -R Labirint DEPENDS Labirint)