add_executable(Lab1AlgoritmsCPP Lab1Algoritms.cpp)
target_include_directories(Lab1AlgoritmsCPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab1AlgoritmsCPP LibraryCPP)

add_executable(lab2CPP lab2.cpp)
target_include_directories(lab2CPP PUBLIC ../LibraryCPP)
target_link_libraries(lab2CPP LibraryCPP)

add_executable(lab3CPP lab3.cpp)
target_include_directories(lab3CPP PUBLIC ../LibraryCPP)
target_link_libraries(lab3CPP LibraryCPP)
