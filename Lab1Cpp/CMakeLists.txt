add_executable(Lab1Cpp lab1.cpp)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input.txt
               ${CMAKE_CURRENT_BINARY_DIR}/input.txt
               COPYONLY)
target_include_directories(Lab1Cpp PUBLIC ../LibraryCPP)
target_link_libraries(Lab1Cpp LibraryCPP)

add_test(NAME TestLab1Cpp COMMAND Lab1Cpp ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_property(TEST TestLab1Cpp PROPERTY PASS_REGULAR_EXPRESSION "4 2 2.*maxSum: 27.*Array: 6 5 3 4 9")