add_executable(Lab4C_PR main.cpp)
include_directories(${CMAKE_SOURCE_DIR}/LibraryCPPTemplate)

if (MSVC)
  target_compile_options(Lab4C_PR PRIVATE /utf-8)
endif()

add_test(NAME Lab4_Kruskal_Sample COMMAND Lab4C_PR ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_tests_properties(Lab4_Kruskal_Sample PROPERTIES PASS_REGULAR_EXPRESSION "MST weight =")