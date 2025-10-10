add_executable(LabCPP_1 lab1.cpp)
target_include_directories(LabCPP_1 PUBLIC ../LibraryCPP)
target_link_libraries(LabCPP_1 LibraryCPP)

add_test(NAME TestLab1CPP COMMAND LabCPP_1 ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_property(TEST TestLab1CPP PROPERTY PASS_REGULAR_EXPRESSION "-7 1 0 -8 -1 2 0 0 0 0")
