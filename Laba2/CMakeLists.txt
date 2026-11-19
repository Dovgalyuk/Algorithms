add_executable(Mazerunner main.cpp)

target_include_directories(Mazerunner PUBLIC ../LibraryCPP)
target_link_libraries(Mazerunner LibraryCPP)

add_test(NAME TestHelloWorld1 COMMAND Mazerunner
    ${CMAKE_CURRENT_SOURCE_DIR}/Test/hello1.maze)
set_property(TEST TestHelloWorld1 PROPERTY PASS_REGULAR_EXPRESSION "HELLO WORLD!")

add_test(NAME TestHelloWorld2 COMMAND Mazerunner
    ${CMAKE_CURRENT_SOURCE_DIR}/Test/hello2.maze)
set_property(TEST TestHelloWorld2 PROPERTY PASS_REGULAR_EXPRESSION "Hello, world!")

add_test(NAME TestTruth1 COMMAND Mazerunner
    ${CMAKE_CURRENT_SOURCE_DIR}/Test/truth.maze
    ${CMAKE_CURRENT_SOURCE_DIR}/Test/truth_1.input)
set_property(TEST TestTruth1 PROPERTY PASS_REGULAR_EXPRESSION "1")

add_test(NAME TestTruth1Compact COMMAND Mazerunner
    ${CMAKE_CURRENT_SOURCE_DIR}/Test/truth2.maze
    ${CMAKE_CURRENT_SOURCE_DIR}/Test/truth_1.input)
set_property(TEST TestTruth1Compact PROPERTY PASS_REGULAR_EXPRESSION "1")

add_test(NAME TestDisan COMMAND Mazerunner
    ${CMAKE_CURRENT_SOURCE_DIR}/Test/disan.maze
    ${CMAKE_CURRENT_SOURCE_DIR}/Test/disan.input)
set_property(TEST TestDisan PROPERTY PASS_REGULAR_EXPRESSION "0")

add_test(NAME TestCat COMMAND Mazerunner
    ${CMAKE_CURRENT_SOURCE_DIR}/Test/cat.maze
    ${CMAKE_CURRENT_SOURCE_DIR}/Test/cat.input)
set_property(TEST TestCat PROPERTY PASS_REGULAR_EXPRESSION "A")