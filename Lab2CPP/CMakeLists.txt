add_executable(Mazerunner mazerunner.cpp)

target_include_directories(Mazerunner PUBLIC ../LibraryCPPTemplate)

add_test(NAME TestMazerunnerByInput1 COMMAND Mazerunner ${CMAKE_CURRENT_SOURCE_DIR}/MazerunnerTestData/script1.txt ${CMAKE_CURRENT_SOURCE_DIR}/MazerunnerTestData/input1.txt)
set_property(TEST TestMazerunnerByInput1 PROPERTY PASS_REGULAR_EXPRESSION "Hello, world!")

add_test(NAME TestMazerunnerByInput2 COMMAND Mazerunner ${CMAKE_CURRENT_SOURCE_DIR}/MazerunnerTestData/script2.txt ${CMAKE_CURRENT_SOURCE_DIR}/MazerunnerTestData/input2.txt)
set_property(TEST TestMazerunnerByInput2 PROPERTY PASS_REGULAR_EXPRESSION "Mazerunner works")

add_test(NAME TestMazerunnerByInput3 COMMAND Mazerunner ${CMAKE_CURRENT_SOURCE_DIR}/MazerunnerTestData/script3.txt ${CMAKE_CURRENT_SOURCE_DIR}/MazerunnerTestData/input3.txt)
set_property(TEST TestMazerunnerByInput3 PROPERTY PASS_REGULAR_EXPRESSION "1")

add_test(NAME TestMazerunnerByInput4 COMMAND Mazerunner ${CMAKE_CURRENT_SOURCE_DIR}/MazerunnerTestData/script4.txt ${CMAKE_CURRENT_SOURCE_DIR}/MazerunnerTestData/input4.txt)
set_property(TEST TestMazerunnerByInput4 PROPERTY PASS_REGULAR_EXPRESSION "65")

add_test(NAME TestMazerunnerByInput5 COMMAND Mazerunner ${CMAKE_CURRENT_SOURCE_DIR}/MazerunnerTestData/script5.txt ${CMAKE_CURRENT_SOURCE_DIR}/MazerunnerTestData/input5.txt)
set_property(TEST TestMazerunnerByInput5 PROPERTY PASS_REGULAR_EXPRESSION "starved")

add_test(NAME TestMazerunnerByInput6 COMMAND Mazerunner ${CMAKE_CURRENT_SOURCE_DIR}/MazerunnerTestData/script6.txt ${CMAKE_CURRENT_SOURCE_DIR}/MazerunnerTestData/input6.txt)
set_property(TEST TestMazerunnerByInput6 PROPERTY PASS_REGULAR_EXPRESSION "overate")
