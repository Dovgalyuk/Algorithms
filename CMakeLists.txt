cmake_minimum_required(VERSION 3.0)
project(Algorithms)

add_library(containers STATIC Library/array.cpp Library/list.cpp Library/queue.cpp
            Library/stack.cpp Library/vector.cpp)

add_executable(TestArray TestArray/main.cpp)
target_include_directories(TestArray PUBLIC Library)
target_link_libraries(TestArray containers)

add_executable(TestList TestList/main.cpp)
target_include_directories(TestList PUBLIC Library)
target_link_libraries(TestList containers)

add_executable(TestQueue TestQueue/main.cpp)
target_include_directories(TestQueue PUBLIC Library)
target_link_libraries(TestQueue containers)

add_executable(TestStack TestStack/main.cpp)
target_include_directories(TestStack PUBLIC Library)
target_link_libraries(TestStack containers)

add_executable(TestVector TestVector/main.cpp)
target_include_directories(TestVector PUBLIC Library)
target_link_libraries(TestVector containers)
