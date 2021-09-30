add_executable(lab1 lab1.cpp)
target_include_directories(lab1 PUBLIC ../LibraryCPP)
target_link_libraries(lab1 PUBLIC LibraryCPP)