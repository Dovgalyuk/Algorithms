add_executable(Lab1 lab1.cpp)
target_include_directories(Lab1 PUBLIC ../LibraryCPP)
target_link_libraries(Lab1 PUBLIC LibraryCPP)

add_executable(Lab2 lab2.cpp)
target_include_directories(Lab2 PUBLIC ../LibraryCPP)
target_link_libraries(Lab2 PUBLIC LibraryCPP)