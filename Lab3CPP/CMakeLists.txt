add_executable(Lab3CPP main.cpp)
target_include_directories(Lab3CPP PUBLIC ../LibraryCPPClass)
target_link_libraries(Lab3CPP LibraryCPPClass)

add_test(NAME Test1P COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt)
set_tests_properties(Test1P PROPERTIES PASS_REGULAR_EXPRESSION "/ \ / \ / \.*|S| |#| |.|.*\ /  \ /  \ / \.*|x| |#| |#|.*\ /  \ /  \ / \.*|x| |x| |E|.*\ /  \ /  \ /")

add_test(NAME Test2P COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)
set_tests_properties(Test2P PROPERTIES PASS_REGULAR_EXPRESSION "/ \ / \ / \ / \ / \
																	.*|#| |#| |#| |#| |S|
																	.*\ /  \ /  \ /  \ /  \ / \
																	.*|.| |.| |#| |x| |.|
																	.*\ /  \ /  \ /  \ /  \ / \
																	.*|.| |.| |E| |#| |.|
																	.*\ /  \ /  \ /  \ /  \ / \
																	.*|.| |#| |#| |.| |.|
																	.*\ /  \ /  \ /  \ /  \ / \
																	.*|.| |.| |.| |.| |#|
																	.*\ /  \ /  \ /  \ /  \ /")

add_test(NAME Test3P COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/input3.txt)
set_tests_properties(Test3P PROPERTIES PASS_REGULAR_EXPRESSION "No path")
