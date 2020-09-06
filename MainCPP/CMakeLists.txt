project(Main)

add_executable(MainCPP main.cpp)

target_include_directories(MainCPP PUBLIC ../LibraryCPP)

target_link_libraries(MainCPP LibraryCPP)