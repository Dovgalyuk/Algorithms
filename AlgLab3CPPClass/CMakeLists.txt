add_executable(AlgLab3CPPClass
        src/alg_lab3.cpp
        src/alg_lab3.h
        src/main.cpp
)

target_include_directories(AlgLab3CPPClass PUBLIC ../LibraryCPPClass)
target_link_libraries(AlgLab3CPPClass LibraryCPPClass)

set(INPUT_FILE "${CMAKE_CURRENT_SOURCE_DIR}/input.txt")
set(OUTPUT_FILE "${CMAKE_BINARY_DIR}/output/output.txt")

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/output)

add_test(NAME TestAlgLab3CPPClass
        COMMAND AlgLab3CPPClass ${INPUT_FILE} ${OUTPUT_FILE})