add_executable(LabCPP_1 lab1.cpp)
target_include_directories(LabCPP_1 PUBLIC ../LibraryCPP)
target_link_libraries(LabCPP_1 LibraryCPP)

add_test(NAME Test_Lab1CPP COMMAND LabCPP_1 ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_property(TEST Test_Lab1CPP PROPERTY PASS_REGULAR_EXPRESSION "absCount = 2.*3 4 0 0")
