add_executable(Lab1C lab1.cpp "lab1.cpp")
target_include_directories(Lab1PP PUBLIC ../LibraryCPP)
target_link_libraries(Lab1CPP LibraryCPP)

add_test(NAME TestLab1CPP COMMAND Lab1CPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_property(TEST TestLab1CPP PROPERTY PASS_REGULAR_EXPRESSION "1 2 3 4 5")
