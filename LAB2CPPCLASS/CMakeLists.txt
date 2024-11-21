add_executable(LAB2CPPCLASS lab2.cpp)
target_include_directories(LAB2CPPCLASS PUBLIC ../LibraryCPPClass)
target_link_libraries(LAB2CPPCLASS LibraryCPPClass)

set(INPUT_FILE "${CMAKE_CURRENT_SOURCE_DIR}/input.txt")
set(OUTPUT_FILE "${CMAKE_CURRENT_SOURCE_DIR}/output.txt")

add_test( NAME Lab2CPPCLASSTest 
        COMMAND LAB2CPPCLASS ${INPUT_FILE} ${OUTPUT_FILE})
