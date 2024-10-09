add_executable(Lab2CPPTemplate lab2.cpp)
target_include_directories(Lab2CPPTemplate PUBLIC ../LibraryCPPTemplate)
target_link_libraries(Lab2CPPTemplate LibraryCPPTemplate)

add_test(NAME TestLab2CPP COMMAND Lab2CPPTemplate ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)