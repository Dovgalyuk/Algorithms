add_executable(Lab2TaskCPP lab2.cpp lab2.h TestTask.cpp)
target_include_directories(Lab2TaskCPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab2TaskCPP LibraryCPP)
add_test(NAME Lab2TaskCPP COMMAND Lab2TaskCPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)