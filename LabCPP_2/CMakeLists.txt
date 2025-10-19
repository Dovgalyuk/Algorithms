add_executable(LabCPP_2 lab2.cpp)
target_include_directories(LabCPP_2 PUBLIC ../LibraryCPP)
target_link_libraries(LabCPP_2 LibraryCPP)

add_test(NAME Test_Lab2CPP COMMAND LabCPP_2 ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_property(TEST Test_Lab2CPP PROPERTY PASS_REGULAR_EXPRESSION "6.*5.*-19.375")
