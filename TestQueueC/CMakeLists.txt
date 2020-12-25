add_executable(TestQueueC main.cpp)
target_include_directories(TestQueueC PUBLIC ../LibraryC)
target_link_libraries(TestQueueC LibraryC)
