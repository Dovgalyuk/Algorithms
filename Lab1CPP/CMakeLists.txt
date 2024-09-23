add_executable(Lab1CPP main.cpp lab1.cpp lab1.h)

target_include_directories(Lab1CPP PUBLIC ../LibraryCPPClass)
target_link_libraries(Lab1CPP LibraryCPPClass)

add_test(NAME TestLab1CPP COMMAND Lab1CPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)

add_executable(TestTasks Tests/test_tasks.cpp lab1.cpp lab1.h)
target_include_directories(TestTasks PUBLIC .)
target_include_directories(TestTasks PUBLIC ../LibraryCPPClass)
target_link_libraries(TestTasks LibraryCPPClass)
add_test(TestTasks TestTasks ${CMAKE_CURRENT_SOURCE_DIR}/input_test_tasks.txt)