add_executable(Laba1 zadanie1.cpp)
target_include_directories(Laba1 PUBLIC ../LibraryCPP)
target_link_libraries(Laba1 LibraryCPP)

add_executable(Laba2 zadanie2.cpp)
target_include_directories(Laba2 PUBLIC ../LibraryCPP)
target_link_libraries(Laba2 LibraryCPP)