add_executable(task1 main.cpp)
target_include_directories(task1 PUBLIC ../LibraryCPP)
target_link_libraries(task1 LibraryCPP)