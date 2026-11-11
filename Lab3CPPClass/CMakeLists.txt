add_executable(Lab3 lab3.cpp)
target_include_directories(Lab3 PUBLIC ../LibraryCPPClass)
target_link_libraries(Lab3 LibraryCPPClass)

add_test(NAME TestLab3_Work COMMAND Lab3 ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt)
set_property(TEST TestLab3_Work PROPERTY PASS_REGULAR_EXPRESSION "5")
