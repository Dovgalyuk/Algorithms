add_executable(LABACPP LABA.cpp)
target_include_directories(LABA.cpp PUBLIC ../LibraryCPP)
target_link_libraries(LABA.cpp LibraryCPP)

add_executable(Laba2CPP Laba2.cpp)
target_include_directories(Laba2.cpp PUBLIC ../LibraryCPP)
target_link_libraries(Laba2.cpp LibraryCPP)


add_executable(Laba3CPP Laba3.cpp)
target_include_directories(Laba3.cpp PUBLIC ../LibraryCPP)
target_link_libraries(Laba3.cpp LibraryCPP)
