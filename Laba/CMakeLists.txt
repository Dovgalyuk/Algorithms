add_executable(Laba1 zadanie1.cpp)
target_include_directories(Laba1 PUBLIC ../LibraryCPP)
target_link_libraries(Laba1 LibraryCPP)

add_executable(Laba2 zadanie2.cpp)
target_include_directories(Laba2 PUBLIC ../LibraryCPP)
target_link_libraries(Laba2 LibraryCPP)

add_executable(Laba3 zadanie3.cpp)
target_include_directories(Laba3 PUBLIC ../LibraryCPP)
target_link_libraries(Laba3 LibraryCPP)

add_executable(Laba4 zadanie4.cpp)
target_include_directories(Laba4 PUBLIC ../LibraryCPPTemplate)

add_executable(Laba5 zadanie5.cpp)
target_include_directories(Laba5 PUBLIC ../LibraryCPPTemplate)