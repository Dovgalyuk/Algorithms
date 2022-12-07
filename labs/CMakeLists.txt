add_executable(LABACPP LABA.cpp)
target_include_directories(LABA.cpp PUBLIC ../LibraryCPP)
target_link_libraries(LABA.cpp LibraryCPP)

add_executable(Lab2CPP Lab2.cpp)
target_include_directories(Lab2.cpp PUBLIC ../LibraryCPP)
target_link_libraries(Lab2.cpp LibraryCPP)

