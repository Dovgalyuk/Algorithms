add_executable(Lab3CPP lab3.cpp lab3.h main.cpp)
target_include_directories(Lab3CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab3CPP LibraryCPP)

add_executable(TestTasks ../tests/test_lab3.cpp lab3.cpp lab3.h)
target_include_directories(TestTasks PUBLIC .)
target_include_directories(TestTasks PUBLIC ../LibraryCPP)
target_link_libraries(TestTasks LibraryCPP)
add_test(TestTasks TestTasks ${CMAKE_SOURCE_DIR}/tests/input_test_lab3.txt)