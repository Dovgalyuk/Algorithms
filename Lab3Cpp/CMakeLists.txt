add_executable(Lab3Cpp src/lab3.cpp)
target_include_directories(Lab3Cpp PUBLIC ../LibraryCPPClass)
target_link_libraries(Lab3Cpp LibraryCPPClass)

# add_test(NAME TestLab1Cpp COMMAND Lab1Cpp ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)

set(INPUT_FILE "${CMAKE_CURRENT_SOURCE_DIR}/input.txt")

set(OUTPUT_FILE "${CMAKE_BINARY_DIR}/output/output.txt")

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/output)

add_test(NAME TestLab3CPP
        COMMAND Lab3Cpp ${INPUT_FILE} ${OUTPUT_FILE}
)

