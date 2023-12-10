add_executable(Lab1C "lab1.cpp")
target_include_directories(Lab1C PUBLIC ../LibraryCPP)
target_link_libraries(Lab1C LibraryCPP)

add_executable(Lab2C "lab2.cpp")
target_include_directories(Lab2C PUBLIC ../LibraryCPPClass)
target_link_libraries(Lab2C LibraryCPPClass)
