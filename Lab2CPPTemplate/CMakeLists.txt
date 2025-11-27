add_executable(Beatnik beatnik.cpp)

target_include_directories(Beatnik PUBLIC ../LibraryCPPTemplate)
target_link_libraries(Beatnik LibraryCPPTemplate)

add_test(NAME TestBeatnik COMMAND Beatnik ${CMAKE_CURRENT_SOURCE_DIR}/script.txt ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)

set_property(TEST TestBeatnik PROPERTY PASS_REGULAR_EXPRESSION "H")

add_test(NAME TestBeatnik2 COMMAND Beatnik ${CMAKE_CURRENT_SOURCE_DIR}/script2.txt ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)

set_property(TEST TestBeatnik2 PROPERTY PASS_REGULAR_EXPRESSION "Z")

add_test(NAME TestBeatnik3 COMMAND Beatnik ${CMAKE_CURRENT_SOURCE_DIR}/script3.txt ${CMAKE_CURRENT_SOURCE_DIR}/input3.txt)

set_property(TEST TestBeatnik3 PROPERTY PASS_REGULAR_EXPRESSION "F")

add_test(NAME TestBeatnik4 COMMAND Beatnik ${CMAKE_CURRENT_SOURCE_DIR}/script4.txt ${CMAKE_CURRENT_SOURCE_DIR}/input4.txt)

set_property(TEST TestBeatnik4 PROPERTY PASS_REGULAR_EXPRESSION "P")