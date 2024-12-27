add_executable(lab3 lab3.cpp)
target_include_directories(lab3 PUBLIC ../LibraryCPP)
target_link_libraries(lab3 LibraryCPP)

add_test(NAME TestLab3CPP COMMAND lab3 ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)