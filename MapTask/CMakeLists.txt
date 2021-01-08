project(MapTask)

add_executable(MapTask main.cpp)

target_include_directories(MapTask PUBLIC ../LibraryCPP)

target_link_libraries(MapTask LibraryCPP)