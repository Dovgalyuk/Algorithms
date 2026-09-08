add_executable(Task1
        Task1/task1.cpp
        reader/reader.cpp
        Tests/tests.cpp)
add_executable(Task2
        Task2/task2.cpp
        reader/reader.cpp)
target_include_directories(Task1 PUBLIC ../LibraryCPP reader)
target_include_directories(Task2 PUBLIC ../LibraryCPP reader)
target_link_libraries(Task1 LibraryCPP)
target_link_libraries(Task2 LibraryCPP)
