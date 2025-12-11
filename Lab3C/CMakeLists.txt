add_executable(Lab3C lab3.c)
target_include_directories(Lab3C PUBLIC ../LibraryC)
target_link_libraries(Lab3C LibraryC)

add_test(NAME ___Name_Test___ COMMAND Lab3C ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_property(TEST ___Name_Test___ PROPERTY PASS_REGULAR_EXPRESSION "___PROGRAM_OUTPUT___")