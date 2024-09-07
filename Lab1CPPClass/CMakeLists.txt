add_executable(Lab1CPPClass lab1.cpp)
target_include_directories(Lab1CPPClass PUBLIC ../LibraryCPPClass)
target_link_libraries(Lab1CPPClass LibraryCPPClass)

add_test(NAME TestLab1CPPClass COMMAND Lab1CPPClass ${CMAKE_CURRENT_SOURCE_DIR}/input.txt ${CMAKE_CURRENT_SOURCE_DIR}/output.txt ${CMAKE_CURRENT_SOURCE_DIR}/randomInput.txt) 
