add_executable(Lab2CPP main.cpp lab2.cpp lab2.h)

target_include_directories(Lab2CPP PUBLIC ../LibraryCPPClass)
target_link_libraries(Lab2CPP LibraryCPPClass)


add_executable(TestTasksLab2 ${CMAKE_CURRENT_SOURCE_DIR}/Tests/test_tasks.cpp lab2.cpp lab2.h)
target_include_directories(TestTasksLab2 PUBLIC .)
target_include_directories(TestTasksLab2 PUBLIC ../LibraryCPPClass)
target_link_libraries(TestTasksLab2 LibraryCPPClass)
add_test(TestTasksLab2 TestTasksLab2 ${CMAKE_CURRENT_SOURCE_DIR}/input_test_tasks.txt ${CMAKE_CURRENT_SOURCE_DIR}/output_test_tasks.txt)