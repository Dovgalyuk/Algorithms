add_executable(Lab1CPP src/lab1.cpp)

target_include_directories(Lab1CPP PUBLIC ../LibraryCPPClass)
target_link_libraries(Lab1CPP LibraryCPPClass)

set(INPUT_FILE "${CMAKE_CURRENT_SOURCE_DIR}/input.txt")

set(OUTPUT_FILE "${CMAKE_BINARY_DIR}/output/output.txt")

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/output)

add_test(NAME TestLab1CPPClass
        COMMAND Lab1CPP ${INPUT_FILE} ${OUTPUT_FILE})
