add_executable(Lab1C lab1.c)
target_include_directories(Lab1C PUBLIC ../LibraryC)
target_link_libraries(Lab1C LibraryC)

add_test(NAME TestLab1C COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/input.txt ${CMAKE_CURRENT_SOURCE_DIR}/input_2.txt  ${CMAKE_CURRENT_SOURCE_DIR}/input_3.txt)

