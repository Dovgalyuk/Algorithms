add_executable(Prim prim.cpp)

target_include_directories(Prim PUBLIC ../LibraryCPPTemplate)
target_link_libraries(Prim LibraryCPPTemplate)

add_test(NAME TestPrim COMMAND Prim ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_property(TEST TestPrim PROPERTY PASS_REGULAR_EXPRESSION "A-C\nB-C\nC-D\nD-E")