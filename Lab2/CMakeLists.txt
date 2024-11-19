add_executable(Lab2 lab2.cpp
        lab2.cpp)
target_include_directories(Lab2 PUBLIC ../LibraryCPPClass)
target_link_libraries(Lab2 LibraryCPPClass)

add_test(NAME TestLab2 COMMAND Lab2 ${CMAKE_CURRENT_SOURCE_DIR}/input.txt ${CMAKE_CURRENT_SOURCE_DIR}/output.txt)