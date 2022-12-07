add_executable(LABACPP LABA.cpp)
target_include_directories(LABA.cpp PUBLIC ../LibraryCPP)
target_link_libraries(LABA.cpp LibraryCPP)

add_executable(Laba2CPP Laba2.cpp)
target_include_directories(Laba2.cpp PUBLIC ../LibraryCPP)
target_link_libraries(Laba2.cpp LibraryCPP)

