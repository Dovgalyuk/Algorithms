add_executable(lab_solution lab3.cpp) 
target_link_libraries(lab_solution PUBLIC LibraryCPP)
target_include_directories(lab_solution PUBLIC ../LibraryCPP)