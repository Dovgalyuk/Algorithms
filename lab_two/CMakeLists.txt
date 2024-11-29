add_executable(lab_two lab.cpp)
target_include_directories(lab_two PUBLIC ../LibraryCPP)
target_link_libraries(lab_two LibraryCPP)

add_test(NAME Testlab_two COMMAND lab_two ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)