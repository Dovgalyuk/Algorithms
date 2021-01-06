add_executable(TestQueueC main.cpp)
target_include_directories(TestQueueC PUBLIC ../LibraryCPP)
target_link_libraries(TestQueueC LibraryCPP)
