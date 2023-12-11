add_executable(Lab2 lab_2.cpp)
target_include_directories(Lab1C PUBLIC ../LibraryCPP)
target_link_libraries(Lab2 LibraryCPP)
