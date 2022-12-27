
add_executable(LAB1 LAB1.cpp)
target_include_directories(LAB1 PUBLIC ../LibraryCPP)
target_link_libraries(LAB1 LibraryCPP)

add_executable(LAB2 LAB2.cpp)
target_include_directories(LAB2 PUBLIC ../LibraryCPP)
target_link_libraries(LAB2 LibraryCPP)

add_executable(LAB3 LAB3.cpp)
target_include_directories(LAB3 PUBLIC ../LibraryCPP)
target_link_libraries(LAB3 LibraryCPP)

