add_executable(LABACPP LABA.cpp)
target_include_directories(LABA.cpp PUBLIC ../LibraryCPP)
target_link_libraries(LABA.cpp LibraryCPP)
