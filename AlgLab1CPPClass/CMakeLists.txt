add_executable(AlgLab1CPPClass src/alg_lab1.cpp)

target_include_directories(AlgLab1CPPClass PUBLIC ../LibraryCPPClass)
target_link_libraries(AlgLab1CPPClass LibraryCPPClass)

set(INPUT_FILE "${CMAKE_CURRENT_SOURCE_DIR}/input.txt")

set(OUTPUT_FILE "${CMAKE_BINARY_DIR}/AlgLab1CPPClass/output/output.txt")

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/output)

add_test(NAME TestAlgLab1CPPClass
        COMMAND AlgLab1CPPClass ${INPUT_FILE} ${OUTPUT_FILE})

set_tests_properties(TestAlgLab1CPPClass PROPERTIES TIMEOUT 10)
