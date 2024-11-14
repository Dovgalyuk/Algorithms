add_executable(LAB2CPPCLASS lab2.cpp)
target_include_directories(LAB2CPPCLASS PUBLIC ../LibraryCPPClass)
target_link_libraries(LAB2CPPCLASS LibraryCPPClass)

add_test(NAME TestLAB2CPP COMMAND LAB2CPPCLASS ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
