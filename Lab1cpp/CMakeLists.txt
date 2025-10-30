add_executable(Lab1cpp lab1.cpp)
target_include_directories(Lab1cpp PUBLIC ../LibraryCPP)
target_link_libraries(Lab1cpp LibraryCPP)

add_test(NAME TestLab1CPP COMMAND Lab1cpp ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_property(TEST TestLab1CPP PROPERTY PASS_REGULAR_EXPRESSION ".*5.*5.9.*6.1.*89.*56.*23.*78.*45.*291.*")
