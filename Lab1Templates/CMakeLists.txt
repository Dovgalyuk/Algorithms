add_executable(Lab1Templates lab1.cpp)
target_include_directories(Lab1Templates PUBLIC ../LibraryCPPTemplate)
target_link_libraries(Lab1Templates LibraryCPPTemplate)
add_test(NAME TestLab1Templates COMMAND TestLab1Templates ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
