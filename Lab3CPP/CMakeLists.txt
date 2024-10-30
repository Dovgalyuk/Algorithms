add_executable(Lab3CPP lab3.cpp)
target_include_directories(Lab3CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab3CPP LibraryCPP)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input.txt ${CMAKE_BINARY_DIR}/Lab3CPP COPYONLY)
add_test(TestLab3CPP Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)