add_executable(BeatnikCPP main.cpp)
target_include_directories(BeatnikCPP PRIVATE ../LibraryCPP)
target_link_libraries(BeatnikCPP PRIVATE LibraryCPP)

add_test(NAME TestBeatnikExample
    COMMAND BeatnikCPP ${CMAKE_CURRENT_SOURCE_DIR}/example.beatnik ${CMAKE_CURRENT_SOURCE_DIR}/example.in)
set_tests_properties(TestBeatnikExample PROPERTIES PASS_REGULAR_EXPRESSION "H")

add_test(NAME TestBeatnikArithmetic
    COMMAND BeatnikCPP ${CMAKE_CURRENT_SOURCE_DIR}/arithmetic.beatnik ${CMAKE_CURRENT_SOURCE_DIR}/empty.in)
set_tests_properties(TestBeatnikArithmetic PROPERTIES PASS_REGULAR_EXPRESSION "C")

add_test(NAME TestBeatnikInputOutput
    COMMAND BeatnikCPP ${CMAKE_CURRENT_SOURCE_DIR}/echo.beatnik ${CMAKE_CURRENT_SOURCE_DIR}/echo.in)
set_tests_properties(TestBeatnikInputOutput PROPERTIES PASS_REGULAR_EXPRESSION "Z")
