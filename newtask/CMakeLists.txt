add_executable(papka QueueTask.cpp)
target_include_directories(papka PUBLIC ../LibraryCPP)
target_link_libraries(papka LibraryCPP)