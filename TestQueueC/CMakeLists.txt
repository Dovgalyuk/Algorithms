add_executable(TestQueueC main.cpp)
target_include_directories(TestQueueC PUBLIC ../LibraryCPPTemplate)
target_link_libraries(TestQueueC LibraryCPPTemplate)
