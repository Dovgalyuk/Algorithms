add_executable(Lab3CPP main.cpp lab3.cpp lab3.h)

target_include_directories(Lab3CPP PUBLIC ../LibraryCPPClass)
target_link_libraries(Lab3CPP LibraryCPPClass)


add_executable(TestTasksLab3 ${CMAKE_CURRENT_SOURCE_DIR}/Tests/test_tasks.cpp lab3.cpp lab3.h)
target_include_directories(TestTasksLab3 PUBLIC .)
target_include_directories(TestTasksLab3 PUBLIC ../LibraryCPPClass)
target_link_libraries(TestTasksLab3 LibraryCPPClass)
add_test(TestTasksLab3 TestTasksLab3 ${CMAKE_CURRENT_SOURCE_DIR}/../TestsData/lab3in.txt ${CMAKE_CURRENT_SOURCE_DIR}/../TestsData/lab3out.txt)