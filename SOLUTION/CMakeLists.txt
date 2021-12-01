add_executable(lab1 lab1.cpp)
target_include_directories(lab1 PUBLIC ../LibraryCPP)
target_link_libraries(lab1 LibraryCPP)

add_executable(lab2 lab2.cpp)
target_include_directories(lab2 PUBLIC ../LibraryCPP)
target_link_libraries(lab2 LibraryCPP)

add_executable(lab3 lab3.cpp)
target_include_directories(lab3 PUBLIC ../LibraryCPP)
target_link_libraries(lab3 LibraryCPP)

add_executable(lab4 lab4.cpp)
target_include_directories(lab4 PUBLIC ../LibraryCPP)
target_link_libraries(lab4 LibraryCPP)