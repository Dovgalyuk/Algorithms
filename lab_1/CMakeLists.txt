add_executable(lab_1 labb.cpp)
target_include_directories(lab_one PUBLIC ../LibraryCPP)
target_link_libraries(lab_one LibraryCPP)

add_test(NAME Testlab_one COMMAND lab_1 ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt, input2.txt)