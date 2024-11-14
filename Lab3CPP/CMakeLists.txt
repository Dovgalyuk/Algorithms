add_executable(Lab3CPP src/lab3.cpp)

target_include_directories(Lab3CPP PUBLIC ../LibraryCPPClass)
target_link_libraries(Lab3CPP LibraryCPPClass)

set(INPUT_FILE "${CMAKE_CURRENT_SOURCE_DIR}/input2.txt")

set(OUTPUT_FILE "${CMAKE_BINARY_DIR}/output/output3lab.txt")

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/output)

add_compile_definitions(INPUT_FILE="${INPUT_FILE}")
add_compile_definitions(OUTPUT_FILE="${OUTPUT_FILE}")

add_test(NAME TestLab3CPPClass
        COMMAND Lab3CPP ${INPUT_FILE} ${OUTPUT_FILE})
