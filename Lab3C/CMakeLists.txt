file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/input.txt
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
add_executable(Lab3C lab3.c)
target_include_directories(Lab3C PUBLIC ../LibraryC)
target_link_libraries(Lab3C LibraryC)


add_test(NAME TestLab2C COMMAND Lab2C ${CMAKE_CURRENT_SOURCE_DIR}/input.txt ${OUTPUT_FILE})

