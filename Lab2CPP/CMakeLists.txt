add_executable(Lab2CPP lab2.cpp)
target_include_directories(Lab2CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab2CPP LibraryCPP)

add_custom_command(
    OUTPUT ${CMAKE_BINARY_DIR}/Lab2CPP/in.txt
    COMMAND ${CMAKE_COMMAND} -E echo "bipush 1\nbipush 2\nbipush 3\niadd\nistore_0" > ${CMAKE_BINARY_DIR}/Lab2CPP/in.txt
    DEPENDS lab2.cpp
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/Lab2CPP
    VERBATIM
)

add_custom_target(create_input_file ALL DEPENDS ${CMAKE_BINARY_DIR}/Lab2CPP/in.txt)

add_test(NAME TestLab2CPP COMMAND Lab2CPP)
set_tests_properties(TestLab2CPP PROPERTIES WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/Lab2CPP)
add_dependencies(Lab2CPP create_input_file)