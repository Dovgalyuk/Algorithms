add_executable(Task4 task4.cpp)
target_include_directories(Task4 PUBLIC ../LibraryCPP)
target_link_libraries(Task4 LibraryCPP)
add_executable(Task5 task5.cpp)
target_include_directories(Task5 PUBLIC ../LibraryCPP)
target_link_libraries(Task5 LibraryCPP)

add_subdirectory(tests)