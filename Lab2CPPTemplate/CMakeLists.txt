add_executable(Beatnik beatnik.cpp)

target_include_directories(Beatnik PUBLIC ../LibraryCPPTemplate)
target_link_libraries(Beatnik LibraryCPPTemplate)

add_test(NAME TestBeatnik COMMAND Beatnik ${CMAKE_CURRENT_SOURCE_DIR}/script.txt ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_property(TEST TestBeatnik PROPERTY PASS_REGULAR_EXPRESSION "H")

add_test(NAME MyTestBeatnik1 COMMAND Beatnik ${CMAKE_CURRENT_SOURCE_DIR}/myscript1.txt ${CMAKE_CURRENT_SOURCE_DIR}/myinput1.txt)
set_property(TEST MyTestBeatnik1 PROPERTY PASS_REGULAR_EXPRESSION "e")

add_test(NAME MyTestBeatnik2 COMMAND Beatnik ${CMAKE_CURRENT_SOURCE_DIR}/myscript2.txt ${CMAKE_CURRENT_SOURCE_DIR}/myinput2.txt)
set_property(TEST MyTestBeatnik2 PROPERTY PASS_REGULAR_EXPRESSION "a")
