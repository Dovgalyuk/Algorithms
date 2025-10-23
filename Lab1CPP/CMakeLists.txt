add_executable(Lab1CPP lab1.cpp)
target_include_directories(Lab1CPP PUBLIC ../LibraryCPPTemplate)
target_link_libraries(Lab1CPP LibraryCPPTemplate)

add_test(NAME TestLab1CPP COMMAND Lab1CPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_property(TEST TestLab1CPP PROPERTY PASS_REGULAR_EXPRESSION "1 2 3 4 5")
