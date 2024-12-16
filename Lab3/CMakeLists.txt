add_executable(Lab3 lab3.cpp)
target_include_directories(Lab3 PUBLIC ../LibraryCPPClass)
target_link_libraries(Lab3 LibraryCPPClass)

add_test(NAME TestLab3 COMMAND Lab3 ${CMAKE_CURRENT_SOURCE_DIR}/inputTest1.txt ${CMAKE_CURRENT_SOURCE_DIR}/inputTest2.txt)