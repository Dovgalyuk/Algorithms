add_executable(Beatnik main.cpp beatnik.cpp)
target_link_libraries(Beatnik PRIVATE LibraryCPP)

enable_testing()

add_test(NAME Beatnik_HelloAunts COMMAND Beatnik ${CMAKE_CURRENT_SOURCE_DIR}/tests/hello_aunts.bt ${CMAKE_CURRENT_SOURCE_DIR}/tests/hello_aunts.in)
set_property(TEST Beatnik_HelloAunts PROPERTY PASS_REGULAR_EXPRESSION "H")

add_test(NAME Beatnik_HelloAunts_B COMMAND Beatnik ${CMAKE_CURRENT_SOURCE_DIR}/tests/hello_aunts.bt ${CMAKE_CURRENT_SOURCE_DIR}/tests/hello_aunts_b.in)
set_property(TEST Beatnik_HelloAunts_B PROPERTY PASS_REGULAR_EXPRESSION "I")

add_test(NAME Beatnik_pustoiScript COMMAND Beatnik ${CMAKE_CURRENT_SOURCE_DIR}/tests/pustoi.bt ${CMAKE_CURRENT_SOURCE_DIR}/tests/hello_aunts.in)

add_test(NAME Beatnik_prost COMMAND Beatnik ${CMAKE_CURRENT_SOURCE_DIR}/tests/prost.bt ${CMAKE_CURRENT_SOURCE_DIR}/tests/hello_aunts.in)

add_test(NAME Beatnik_Space COMMAND Beatnik ${CMAKE_CURRENT_SOURCE_DIR}/tests/output_space.bt ${CMAKE_CURRENT_SOURCE_DIR}/tests/hello_aunts.in)
set_property(TEST Beatnik_Space PROPERTY PASS_REGULAR_EXPRESSION " ")

add_test(NAME Beatnik_DoubleSpace COMMAND Beatnik ${CMAKE_CURRENT_SOURCE_DIR}/tests/duplicate.bt ${CMAKE_CURRENT_SOURCE_DIR}/tests/hello_aunts.in)
set_property(TEST Beatnik_DoubleSpace PROPERTY PASS_REGULAR_EXPRESSION "  ")

add_test(NAME Beatnik_PopDiscard COMMAND Beatnik ${CMAKE_CURRENT_SOURCE_DIR}/tests/pop_discard.bt ${CMAKE_CURRENT_SOURCE_DIR}/tests/hello_aunts.in)

add_test(NAME Beatnik_Stop COMMAND Beatnik ${CMAKE_CURRENT_SOURCE_DIR}/tests/stop.bt ${CMAKE_CURRENT_SOURCE_DIR}/tests/hello_aunts.in)

add_test(NAME Beatnik_OutputA COMMAND Beatnik ${CMAKE_CURRENT_SOURCE_DIR}/tests/output_a.bt ${CMAKE_CURRENT_SOURCE_DIR}/tests/hello_aunts.in)
set_property(TEST Beatnik_OutputA PROPERTY PASS_REGULAR_EXPRESSION "A")

add_test(NAME Beatnik_MultiOutput COMMAND Beatnik ${CMAKE_CURRENT_SOURCE_DIR}/tests/multi_output.bt ${CMAKE_CURRENT_SOURCE_DIR}/tests/hello_aunts.in)
set_property(TEST Beatnik_MultiOutput PROPERTY PASS_REGULAR_EXPRESSION " !")

add_custom_target(test_all COMMAND ${CMAKE_CTEST_COMMAND} -C $<CONFIG> --ouput-on-failure
DEPENDS Beatnik
)






