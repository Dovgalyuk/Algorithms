add_executable(LAB1CPPCLASS lab1.cpp)
target_include_directories(LAB1CPPCLASS PUBLIC ../LibraryCPPClass)
target_link_libraries(LAB1CPPCLASS LibraryCPPClass)

add_test(NAME TestLAB1CPP COMMAND LAB1CPPCLASS ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
