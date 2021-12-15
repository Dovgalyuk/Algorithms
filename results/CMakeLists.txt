add_executable(lab1 lab1.cpp)
target_include_directories(lab1 PUBLIC ../LibraryCPP)
target_link_libraries(lab1 LibraryCPP)
add_test(lab1 TestArrayCPP)

add_executable(lab2 lab2.cpp)
target_include_directories(lab2 PUBLIC ../LibraryCPPTemplate)

add_executable(lab3 lab3.cpp)
target_include_directories(lab3 PUBLIC ../LibraryCPPTemplate)