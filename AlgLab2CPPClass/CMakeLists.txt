add_executable(AlgLab2CPPClass
        src/alg_lab2.cpp
        src/befunge_interpreter.cpp
        src/alg_lab2.h
        src/befunge_interpreter.h)

target_include_directories(AlgLab2CPPClass PUBLIC ../LibraryCPPClass)
target_link_libraries(AlgLab2CPPClass LibraryCPPClass)

set(INPUT_FILE "${CMAKE_CURRENT_SOURCE_DIR}/input.txt")
set(OUTPUT_FILE "${CMAKE_BINARY_DIR}/output/output.txt")

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/output)

add_test(NAME TestAlgLab2CPPClass
        COMMAND AlgLab2CPPClass ${INPUT_FILE} ${OUTPUT_FILE})
