add_executable(Lab2Cpp src/lab2.cpp)
target_include_directories(Lab2Cpp PUBLIC ../LibraryCPP)
target_link_libraries(Lab2Cpp LibraryCPP)

# add_test(NAME TestLab1Cpp COMMAND Lab1Cpp ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)

set(INPUT_FILE "${CMAKE_CURRENT_SOURCE_DIR}/input.txt")

set(OUTPUT_FILE "${CMAKE_BINARY_DIR}/output/output.txt")

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/output)

add_test(NAME TestLab2CPP
        COMMAND Lab2Cpp ${INPUT_FILE} ${OUTPUT_FILE}
)

