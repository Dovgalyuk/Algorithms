add_executable(Lab6CPP lab6.cpp solution1.cpp solution2.cpp)
add_executable(performance_test performance_test.cpp solution1.cpp solution2.cpp)
#target_include_directories(Lab6CPP PUBLIC ../LibraryCPP)
#target_link_libraries(Lab6CPP LibraryCPP)

add_test(NAME TestLab6CPP COMMAND Lab6CPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
