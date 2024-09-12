add_executable(Lab2CPPClass lab2.cpp)
target_include_directories(Lab2CPPClass PUBLIC ../LibraryCPPClass)
target_link_libraries(Lab2CPPClass LibraryCPPClass)

add_test(NAME TestLab2CPPClass COMMAND Lab2CPPClass ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
