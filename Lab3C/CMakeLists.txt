add_executable(Lab3C lab3.cpp)
target_include_directories(Lab3C PUBLIC ../LibraryCPP)
target_link_libraries(Lab3C LibraryCPP)

add_test(NAME LabyrinthExample COMMAND Lab3C ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_property(TEST LabyrinthExample PROPERTY PASS_REGULAR_EXPRESSION "4")
