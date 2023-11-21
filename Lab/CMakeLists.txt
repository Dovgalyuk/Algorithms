add_executable(Lab2 "lab2.cpp")
target_include_directories(Lab2 PUBLIC ../LibraryCPP)
target_link_libraries(Lab2 LibraryCPP)

add_executable(Lab3 "lab3.cpp")
target_include_directories(Lab3 PUBLIC ../LibraryCPP)
target_link_libraries(Lab3 LibraryCPP)