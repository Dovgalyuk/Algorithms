add_executable(Task1 Task1.cpp)
target_include_directories(Task1 PUBLIC ../LibraryCPP)
target_link_libraries(Task1 LibraryCPP)

add_executable(Task2 Task2.cpp)
target_include_directories(Task2 PUBLIC ../LibraryCPP)
target_link_libraries(Task2 LibraryCPP)

add_executable(Task3 Task3.cpp)
target_include_directories(Task3 PUBLIC ../LibraryCPPTemplate)

