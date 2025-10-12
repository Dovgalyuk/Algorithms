add_executable(Lab1CPP lab1.cpp)
target_include_directories(Lab1CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab1CPP LibraryCPP)

add_test(NAME TestLab1CPP COMMAND Lab1CPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_property(TEST TestLab1CPP PROPERTY PASS_REGULAR_EXPRESSION "In the first half of June, 135 mm of precipitation fell.
In the second half of June, 147 mm of precipitation fell.
90 mm of precipitation fell in the first decade of June.
95 mm of precipitation fell in the second decade of June.
97 mm of precipitation fell in the third decade of June.
As a result, more precipitation fell in the second half of June.
The third decade of June saw the most precipitation.
Elements that occur 2 times: 3 7 2")
