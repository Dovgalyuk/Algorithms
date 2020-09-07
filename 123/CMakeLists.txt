add_executable(123 main.cpp)
target_include_directories(123 PUBLIC ../LibraryCPP)
target_link_libraries(123 LibraryCPP)
