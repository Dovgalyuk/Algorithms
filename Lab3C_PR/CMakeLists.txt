add_executable(Lab3C_PR main.cpp)
target_include_directories(Lab3C_PR PUBLIC ../LibraryCPP)
target_link_libraries(Lab3C_PR LibraryCPP)

if (MSVC)
  target_compile_options(Lab3C_PR PRIVATE /utf-8)
endif()

add_test(NAME Lab3_Hex_BFS_Sample COMMAND Lab3C_PR ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_tests_properties(Lab3_Hex_BFS_Sample PROPERTIES PASS_REGULAR_EXPRESSION "S(.|\\r|\\n)*x(.|\\r|\\n)*x(.|\\r|\\n)*E")