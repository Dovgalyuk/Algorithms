add_executable(Lab3TaskCPP lab3.cpp lab3.h TestTask.cpp)
target_include_directories(Lab3TaskCPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab3TaskCPP LibraryCPP)
add_test(NAME Lab3TaskCPP COMMAND Lab3TaskCPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)