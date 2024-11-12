add_executable(Lab1Cpp src/lab1.cpp)
target_include_directories(Lab1Cpp PUBLIC ../LibraryCPP)
target_link_libraries(Lab1Cpp LibraryCPP)

# add_test(NAME TestLab1Cpp COMMAND Lab1Cpp ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)

set(INPUT_FILE "${CMAKE_CURRENT_SOURCE_DIR}/input.txt")

set(OUTPUT_FILE "${CMAKE_BINARY_DIR}/output/output.txt")

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/output)

add_test(NAME TestLab1CPP
        COMMAND Lab1Cpp ${INPUT_FILE} ${OUTPUT_FILE}
)

