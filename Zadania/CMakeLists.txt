add_executable(Zadanie1 Zadanie1.cpp)
target_include_directories(Zadanie1 PUBLIC ../LibraryCPP)
target_link_libraries(Zadanie1 LibraryCPP)

add_executable(Zadanie2 Zadanie2.cpp)
target_include_directories(Zadanie2 PUBLIC ../LibraryCPPTemplate)
