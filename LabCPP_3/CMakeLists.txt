add_executable(LabCPP_3 lab3.cpp)
target_include_directories(LabCPP_3 PUBLIC ../LibraryCPP)
target_link_libraries(LabCPP_3 LibraryCPP)

add_test(NAME Test_Lab3CPP COMMAND LabCPP_3 ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_property(TEST Test_Lab3CPP PROPERTY PASS_REGULAR_EXPRESSION "0.######
..#2....
.1#.....
..#.###.
..#.....
.....###
.#####..
##......")
