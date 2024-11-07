add_executable(Lab1 lab1.cpp)
target_include_directories(Lab1 PUBLIC ../LibraryCPP)
target_link_libraries(Lab1 LibraryCPP)

add_test(NAME TestLab1CPPClass COMMAND Lab1CPPClass ${CMAKE_CURRENT_SOURCE_DIR}/input.txt ${CMAKE_BINARY_DIR}/output.txt ${CMAKE_CURRENT_SOURCE_DIR}/random.txt)
