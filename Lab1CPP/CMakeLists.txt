include_directories(${CMAKE_SOURCE_DIR}/../../LibraryCPP)
add_executable(Lab1CPP main.cpp)

add_test(NAME TestLab1CPP COMMAND Lab1CPP &{CMAKE_CURRENT_SOURCE_DIR}/input.txt)
