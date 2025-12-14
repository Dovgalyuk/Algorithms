add_executable(Lab3CPP main.cpp)
target_include_directories(Lab3CPP PUBLIC ../LibraryCPPClass)
target_link_libraries(Lab3CPP LibraryCPPClass)

add_test(NAME Test1P COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt)
set_tests_properties(Test1P PROPERTIES PASS_REGULAR_EXPRESSION "/ \ / \ / \.*|S| |#| |.|.*\ /  \ /  \ / \.*|x| |#| |#|.*\ /  \ /  \ / \.*|x| |x| |E|.*\ /  \ /  \ /")

add_test(NAME Test2P COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)
set_tests_properties(Test2P PROPERTIES PASS_REGULAR_EXPRESSION "/ \ / \ / \ / \ / \.*|#| |#| |#| |#| |S|.*\ /  \ /  \ /  \ /  \ / \.*|.| |.| |#| |x| |.|
																	.*\ /  \ /  \ /  \ /  \ / \.*|.| |.| |E| |#| |.|.*\ /  \ /  \ /  \ /  \ / \.*|.| |#| |#| |.| |.|
																	.*\ /  \ /  \ /  \ /  \ / \.*|.| |.| |.| |.| |#|.*\ /  \ /  \ /  \ /  \ /")

add_test(NAME Test3P COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/input3.txt)
set_tests_properties(Test3P PROPERTIES PASS_REGULAR_EXPRESSION "No path")

add_test(NAME Test4P COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/input4.txt)
set_tests_properties(Test4P PROPERTIES PASS_REGULAR_EXPRESSION "Start \\(S\\) or End \\(E\\) not found")

add_test(NAME Test5P COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/input5.txt)
set_tests_properties(Test5P PROPERTIES PASS_REGULAR_EXPRESSION " / \ / \ / \ / \ / \ / \.*|#| |#| |#| |x| |x| |#|.*\ /  \ /  \ /  \ /  \ /  \ / \.*|S| |x| |x| |#| |x| |#|
    .*\ /  \ /  \ /  \ /  \ /  \ / \.*|.| |#| |.| |#| |x| |.|.*\ /  \ /  \ /  \ /  \ /  \ / \.*|#| |#| |#| |#| |x| |.|.*\ /  \ /  \ /  \ /  \ /  \ / \.*|.| |.| |#| |x| |.| |#|
     .*\ /  \ /  \ /  \ /  \ /  \ / \.*|E| |x| |x| |#| |.| |#|.*\ /  \ /  \ /  \ /  \ /  \ /")

add_test(NAME Test6P COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/input6.txt)
set_tests_properties(Test6P PROPERTIES PASS_REGULAR_EXPRESSION "All lines must have equal length")