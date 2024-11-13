add_executable(Lab3C lab3.c)
target_include_directories(Lab3C PUBLIC ../LibraryC)
target_link_libraries(Lab3C LibraryC)

add_test(NAME TestLab3C COMMAND Lab3C ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)