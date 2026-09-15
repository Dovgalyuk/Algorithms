add_executable(Task1 laba1_task1.cpp)
target_include_directories(Task1 PUBLIC ../LibraryCPP)
target_link_libraries(Task1 LibraryCPP)

add_executable(Task2 laba1_task2.cpp)
target_include_directories(Task2 PUBLIC ../LibraryCPP)
target_link_libraries(Task2 LibraryCPP)