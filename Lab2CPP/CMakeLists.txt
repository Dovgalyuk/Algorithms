add_executable(Lab2CPP lab2.cpp)
target_include_directories(Lab2CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab2CPP LibraryCPP)

add_custom_command(
    OUTPUT input.txt
    COMMAND ${CMAKE_COMMAND} -E echo "bipush 1\nbipush 2\nbipush 3\niadd\nistore_0" > input.txt
    DEPENDS lab2.cpp
    VERBATIM
)

add_custom_target(create_input_file ALL DEPENDS input.txt)

add_test(NAME TestLab2CPP COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)

#add_dependencies(TestLab2CPP create_input_file)