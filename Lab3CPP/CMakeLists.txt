add_executable(Lab3CPP main.cpp)
target_include_directories(Lab3CPP PRIVATE ../LibraryCPP)
target_link_libraries(Lab3CPP LibraryCPP)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input.txt ${CMAKE_CURRENT_BINARY_DIR}/input.txt COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input1.txt ${CMAKE_CURRENT_BINARY_DIR}/input1.txt COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input2.txt ${CMAKE_CURRENT_BINARY_DIR}/input2.txt COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input3.txt ${CMAKE_CURRENT_BINARY_DIR}/input3.txt COPYONLY)

enable_testing()

add_test(NAME TestLab3 COMMAND $<TARGET_FILE:Lab3CPP> ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_property(TEST TestLab3 PROPERTY PASS_REGULAR_EXPRESSION
    "^6\nPath: \\([0-9]+,[0-9]+\\)( -> \\([0-9]+,[0-9]+\\))*\nMaze with path:\n / \\\\ / \\\\ / \\\\ / \\\\ / \\\\ / \\\\\n\\| S \\| \\. \\| # \\| \\. \\| \\. \\| \\. \\| \n \\\\ / \\\\ / \\\\ / \\\\ / \\\\ / \\\\ / \\\\\n  \\| \\. \\| # \\| \\. \\| E \\| \\. \\| \\. \\| \n   \\\\ / \\\\ / \\\\ / \\\\ / \\\\ / \\\\ / \\\\\n    \\| \\. \\| \\. \\| # \\| \\. \\| \\. \\| \\. \\| \n    \\\\ / \\\\ / \\\\ / \\\\ / \\\\ / \\\\ / \\\\\n     \\| \\. \\| # \\| \\. \\| \\. \\| # \\| \\. \\| \n     \\\\ / \\\\ / \\\\ / \\\\ / \\\\ / \\\\ / \\\\\n      \\| \\. \\| \\. \\| \\. \\| # \\| \\. \\| \\. \\| \n      \\\\ / \\\\ / \\\\ / \\\\ / \\\\ / \\\\ / \\\\\n       \\| # \\| \\. \\| E \\| \\. \\| \\. \\| \\. \\| \n       \\\\ / \\\\ / \\\\ / \\\\ / \\\\ / \\\\ / \\\\\n$")

add_test(NAME TestLab3_1 COMMAND $<TARGET_FILE:Lab3CPP> ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt)
set_property(TEST TestLab3_1 PROPERTY PASS_REGULAR_EXPRESSION
    "^2\nPath: \\([0-9]+,[0-9]+\\)( -> \\([0-9]+,[0-9]+\\))*\nMaze with path:\n / \\\\ / \\\\ / \\\\\n\\| S \\| \\. \\| E \\| \n \\\\ / \\\\ / \\\\ / \\\\\n  \\| x \\| x \\| x \\| \n   \\\\ / \\\\ / \\\\ / \\\\\n$")

add_test(NAME TestLab3_2 COMMAND $<TARGET_FILE:Lab3CPP> ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)
set_property(TEST TestLab3_2 PROPERTY PASS_REGULAR_EXPRESSION
    "^5\nPath: \\([0-9]+,[0-9]+\\)( -> \\([0-9]+,[0-9]+\\))*\nMaze with path:\n / \\\\ / \\\\ / \\\\ / \\\\\n\\| S \\| \\. \\| \\. \\| \\. \\| \n \\\\ / \\\\ / \\\\ / \\\\ / \\\\\n  \\| # \\| \\. \\| \\. \\| \\. \\| \n   \\\\ / \\\\ / \\\\ / \\\\ / \\\\\n    \\| # \\| # \\| \\. \\| \\. \\| \n    \\\\ / \\\\ / \\\\ / \\\\ / \\\\\n     \\| x \\| x \\| x \\| E \\| \n     \\\\ / \\\\ / \\\\ / \\\\ / \\\\\n$")

add_test(NAME TestLab3_3 COMMAND $<TARGET_FILE:Lab3CPP> ${CMAKE_CURRENT_SOURCE_DIR}/input3.txt)
set_property(TEST TestLab3_3 PROPERTY PASS_REGULAR_EXPRESSION "^-1\n$")