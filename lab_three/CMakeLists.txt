add_executable(lab_three lab.cpp)
target_include_directories(lab_three PUBLIC ../LibraryCPP)
target_link_libraries(lab_three LibraryCPP)

add_test(NAME Testlab_three COMMAND lab_three ${CMAKE_CURRENT_SOURCE_DIR}/input.txt ${CMAKE_BINARY_DIR}/output.txt)