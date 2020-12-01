project(GraphTask)

add_executable(GraphTask main.cpp)

target_include_directories(GraphTask PUBLIC ../LibraryCPP)

target_link_libraries(GraphTask LibraryCPP)