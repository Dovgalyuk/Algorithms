file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/input.txt
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/output.txt
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(Lab2C lab2.c)
target_include_directories(Lab2C PUBLIC ../LibraryC)
target_link_libraries(Lab2C LibraryC)

set(INPUT_FILE ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set(OUTPUT_FILE ${CMAKE_CURRENT_SOURCE_DIR}/output.txt)

add_test(NAME TestLab2C COMMAND Lab2C ${CMAKE_CURRENT_BINARY_DIR}/input.txt ${CMAKE_CURRENT_BINARY_DIR}/output.txt)

