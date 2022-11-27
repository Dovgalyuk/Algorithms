add_executable(Lab_First lab1.cpp)
target_include_directories(Lab_First PUBLIC ../LibraryCPP)
target_link_libraries(Lab_First LibraryCPP)
