add_executable(Lab2CPP lab2.cpp)
target_include_directories(Lab2CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab2CPP LibraryCPP)

add_test(NAME TestLab2CPP COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt ${CMAKE_BINARY_DIR}/output.txt)
add_test(NAME TestLab2CPP_EqualFiles COMMAND ${CMAKE_COMMAND} -E compare_files ${CMAKE_BINARY_DIR}/output.txt ${CMAKE_CURRENT_SOURCE_DIR}/result.txt)