add_executable(Lab1CPP labb.cpp)
target_include_directories(Lab1CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab1CPP LibraryCPP)

add_test(NAME TestLab1CPP COMMAND lab_1 ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)

