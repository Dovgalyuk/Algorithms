add_executable(Lab1CPP "lab2.cpp")
target_include_directories(Lab1CPP PUBLIC ../LibraryCPPClass)
target_link_libraries(Lab1CPP LibraryCPPClass)

add_test(NAME TestLab1CPP COMMAND Lab1CPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_property(TEST TestLab1CPP PROPERTY PASS_REGULAR_EXPRESSION "Collisions:.*4 8.*9 10.*Collisions:.*None.*Collisions:.*1 2.*3 4")
