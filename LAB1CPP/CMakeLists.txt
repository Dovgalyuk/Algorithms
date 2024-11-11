add_executable(LAB1CPP Lab1.cpp)
target_include_directories(LAB1CPP PUBLIC ../LibraryCPP)
target_link_libraries(LAB1CPP LibraryCPP)

add_test(NAME TestLAB1CPP COMMAND LAB1CPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)