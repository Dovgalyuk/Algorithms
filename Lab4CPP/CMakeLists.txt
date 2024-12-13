add_executable(Lab4CPP lab4.cpp)
target_include_directories(Lab4CPP PUBLIC .)
target_include_directories(Lab4CPP PUBLIC ../LibraryCPPTemplate)
target_link_libraries(Lab4CPP LibraryCPPTemplate)

add_test(NAME TestLab COMMAND Lab4CPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)