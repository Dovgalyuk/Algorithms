add_executable(Lab2CPPClass lab2.cpp)
target_include_directories(Lab2CPPClass PUBLIC ../LibraryCPPClass)
target_link_libraries(Lab2CPPClass LibraryCPPClass)

add_test(NAME TestLab2CPPClass COMMAND Lab2CPPClass ${CMAKE_CURRENT_SOURCE_DIR}/input.txt ${CMAKE_CURRENT_SOURCE_DIR}/output.txt)

# Сравнение выходного файла с эталонным
add_test(NAME CompareOutputs
    COMMAND ${CMAKE_COMMAND} -E compare_files ${CMAKE_CURRENT_BINARY_DIR}/output.txt ${CMAKE_CURRENT_BINARY_DIR}/best_output.txt
)