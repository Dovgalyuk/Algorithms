add_executable(Lab1CPP lab1.cpp)
target_include_directories(Lab1CPP PUBLIC ../LibraryCPPClass)
target_link_libraries(Lab1CPP LibraryCPPClass)

add_test(NAME TestSubtractingArray COMMAND Lab1CPP -sub ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)

set_property(TEST TestSubtractingArray PROPERTY PASS_REGULAR_EXPRESSION "-2 -7 0 1 2 -11 4 5 -14 7")


add_test(NAME TestFrequinceNumber COMMAND Lab1CPP -freq ${CMAKE_CURRENT_SOURCE_DIR}/frequinceNumber.txt)

set_property(TEST TestFrequinceNumber PROPERTY PASS_REGULAR_EXPRESSION "FrequintNumber: 3")