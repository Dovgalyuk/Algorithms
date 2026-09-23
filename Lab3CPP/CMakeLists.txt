add_executable(Lab3CPPTask task.cpp)
target_include_directories(Lab3CPPTask PUBLIC ../LibraryCPPTemplate)

add_test(NAME EXAMPLE COMMAND Lab3CPPTask "${CMAKE_CURRENT_SOURCE_DIR}/example_test.txt")
set_property(TEST EXAMPLE PROPERTY PASS_REGULAR_EXPRESSION "4")
