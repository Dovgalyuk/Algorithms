add_executable(lab2 lab2.cpp)
target_include_directories(lab2 PUBLIC ../LibraryCPP)
target_link_libraries(lab2 LibraryCPP)

add_test(NAME TestLab2CPP COMMAND lab2 ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)