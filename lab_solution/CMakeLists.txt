add_executable(lab_solution lab1.cpp)
target_include_directories(lab_solution PUBLIC ../LibraryCPP)
target_link_libraries(lab_solution PUBLIC LibraryCPP) 