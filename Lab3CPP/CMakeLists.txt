add_executable(Labirint labirint.cpp)

target_include_directories(Labirint PUBLIC ../LibraryCPP)
target_link_libraries(Labirint LibraryCPP)

add_subdirectory(tests)