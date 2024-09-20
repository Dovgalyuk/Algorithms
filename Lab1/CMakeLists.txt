add_executable(Lab1 lab1.cpp)
target_include_directories(Lab1 PUBLIC ../LibraryCPPClass)
target_link_libraries(Lab1 LibraryCPPClass)

add_test(NAME TestLab1 COMMAND Lab1 ${CMAKE_CURRENT_SOURCE_DIR}/input.txt ${CMAKE_CURRENT_SOURCE_DIR}/output.txt)