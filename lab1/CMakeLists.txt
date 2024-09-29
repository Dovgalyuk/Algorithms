add_executable(Lab1 lab1.cpp)
target_include_directories(Lab1 PUBLIC ../LibraryCPP)
target_link_libraries(Lab1 LibraryCPP)

add_test(NAME TestLab1 COMMAND Lab1 ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
