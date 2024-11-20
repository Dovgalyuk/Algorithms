add_executable(lab_one lab.cpp)
target_include_directories(lab_one PUBLIC ../LibraryCPP)
target_link_libraries(lab_one LibraryCPP)

add_test(NAME Testlab_one COMMAND lab_one ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
