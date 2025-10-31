add_executable(lab1 lab1.c)
target_link_libraries(lab1 LibraryC)

add_test(NAME Task4Test COMMAND lab1 WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})