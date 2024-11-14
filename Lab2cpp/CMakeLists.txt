add_executable(Lab2cpp lab2.cpp)
target_include_directories(Lab2cpp PUBLIC ../LibraryCPP)
target_link_libraries(Lab2cpp LibraryCPP)


add_test(NAME TestLab2C COMMAND Lab2cpp ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)