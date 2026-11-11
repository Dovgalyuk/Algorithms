add_executable(Task1
        Task1/main.cpp
        Task1/task1.cpp
        reader/reader.cpp
        Task1/main.cpp
)

add_executable(Task2
        Task2/main.cpp
        Task2/task2.cpp
        reader/reader.cpp
        Task2/main.cpp
)

add_executable(TestTasks
        Tests/tests.cpp
        Task1/task1.cpp
        Task2/task2.cpp
)

target_include_directories(Task1 PUBLIC ../LibraryCPP reader)
target_include_directories(Task2 PUBLIC ../LibraryCPP reader)
target_include_directories(TestTasks PUBLIC ../LibraryCPP Task1 Task2 reader)

target_link_libraries(Task1 LibraryCPP)
target_link_libraries(Task2 LibraryCPP)
target_link_libraries(TestTasks LibraryCPP)

add_subdirectory(Tests)