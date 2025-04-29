add_executable(Lab4CPP main.cpp)
include_directories(${CMAKE_SOURCE_DIR}/LibraryCPPTemplate)

add_test(NAME TestLab4CPP COMMAND Lab4CPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)