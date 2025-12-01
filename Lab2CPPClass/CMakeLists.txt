add_executable(Beatnik beatnik.cpp)

target_include_directories(Beatnik PUBLIC ../LibraryCPPClass)
target_link_libraries(Beatnik LibraryCPPClass)

add_test(NAME TestBeatnik1 COMMAND Beatnik ${CMAKE_CURRENT_SOURCE_DIR}/script.txt ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_property(TEST TestBeatnik1 PROPERTY PASS_REGULAR_EXPRESSION "H")

add_test(NAME TestBeatnik2 COMMAND Beatnik ${CMAKE_CURRENT_SOURCE_DIR}/script1.txt ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt)
set_property(TEST TestBeatnik2 PROPERTY PASS_REGULAR_EXPRESSION "X")

add_test(NAME TestBeatnik3 COMMAND Beatnik ${CMAKE_CURRENT_SOURCE_DIR}/script2.txt ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)
set_property(TEST TestBeatnik3 PROPERTY PASS_REGULAR_EXPRESSION "B")
