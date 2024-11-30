add_executable(lab_1 labb.cpp)
target_include_directories(lab_1 PUBLIC ../LibraryCPP)
target_link_libraries(lab_1 LibraryCPP)

add_test(NAME Testlab_1 COMMAND lab_1 ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)