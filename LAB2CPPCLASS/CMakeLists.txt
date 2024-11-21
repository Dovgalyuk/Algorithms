add_executable(LAB2CPPCLASS lab2.cpp)
target_include_directories(LAB2CPPCLASS PUBLIC ../LibraryCPPClass)
target_link_libraries(LAB2CPPCLASS LibraryCPPClass)

set(INPUT_FILE "${CMAKE_CURRENT_SOURCE_DIR}/input.txt")
set(OUTPUT_FILE "${CMAKE_BINARY_DIR}/output/output.txt")
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/output)

add_test( NAME Lab2CPPCLASSTest 
        COMMAND LAB2CPPCLASS ${INPUT_FILE} ${OUTPUT_FILE})

set_tests_properties(Lab2CPPCLASSTest PROPERTIES PASS_REGULAR_EXPRESSION "A = 1")
