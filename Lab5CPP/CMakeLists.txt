add_executable(Lab5CPP 
    ${CMAKE_CURRENT_SOURCE_DIR}/lab5.cpp
)

target_include_directories(Lab5CPP PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/../LibraryCPPClass
)

target_link_libraries(Lab5CPP LibraryCPPClass)

add_test(NAME TestLab5CPP COMMAND Lab5CPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_property(TEST TestLab5CPP PROPERTY PASS_REGULAR_EXPRESSION "Odd number of words found in file. Last word will be ignored.\nPairs read: 10\nUnique keys\\(splay_map\\): 8\nUnique keys\\(std::map\\): 8.*")
