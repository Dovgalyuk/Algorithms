add_executable(Lab1CPP main.cpp lab1.cpp lab1.h)
target_include_directories(Lab1CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab1CPP LibraryCPP)

add_test(NAME TestLab1C COMMAND Lab1CPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)

add_executable(TestTasks ../LibraryCPP/Tests/test_task.cpp lab1.cpp lab1.h)
target_include_directories(TestTasks PUBLIC .)
target_include_directories(TestTasks PUBLIC ../LibraryCPP)
target_link_libraries(TestTasks LibraryCPP)
add_test(TestTasks TestTasks ${CMAKE_CURRENT_SOURCE_DIR}/../LibraryCPP/Tests/input_test_task.txt)