add_executable(Lab1Cpp lab1.cpp) 

target_include_directories(Lab1Cpp PUBLIC ../LibraryCPP)
target_link_libraries(Lab1Cpp LibraryCPP)