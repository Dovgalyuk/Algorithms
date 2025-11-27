add_executable(Lab1CPP "lab3.cpp")
target_include_directories(Lab1CPP PUBLIC ../LibraryCPPClass)
target_link_libraries(Lab1CPP LibraryCPPClass)

add_test(NAME TestLab1CPP COMMAND Lab1CPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_property(TEST TestLab1CPP PROPERTY PASS_REGULAR_EXPRESSION "2(.|\n)*IMPOSSIBLE(.|\n)*0(.|\n)*3(.|\n)*3")
