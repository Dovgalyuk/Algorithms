project(Main)
add_executable(src main.cpp)
target_include_directories(src PUBLIC ../LibraryCPP)
target_link_libraries(src LibraryCPP)
