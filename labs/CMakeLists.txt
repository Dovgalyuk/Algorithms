add_executable(LABACPP LABA.cpp)
target_include_directories(LABACPP PUBLIC ../LibraryCPP)
target_link_libraries(LABACPP LibraryCPP)

add_executable(Laba2CPP Laba2.cpp)
target_include_directories(Laba2CPP PUBLIC ../LibraryCPP)
target_link_libraries(Laba2CPP LibraryCPP)


add_executable(Laba3CPP Laba3.cpp)
target_include_directories(Laba3CPP PUBLIC ../LibraryCPP)
target_link_libraries(Laba3CPP LibraryCPP)
