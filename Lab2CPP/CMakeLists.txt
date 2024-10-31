add_executable(Lab2CPP src/lab2.cpp)

target_include_directories(Lab2CPP PUBLIC ../LibraryCPPClass)
target_link_libraries(Lab2CPP LibraryCPPClass)

set(INPUT_FILE "${CMAKE_CURRENT_SOURCE_DIR}/input.txt")

set(OUTPUT_FILE "${CMAKE_BINARY_DIR}/output/output.txt")

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/output)

add_test(NAME TestLab2CPPClass
        COMMAND Lab2CPP ${INPUT_FILE} ${OUTPUT_FILE})
