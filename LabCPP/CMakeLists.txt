add_executable(LabCPP main.cpp)
target_include_directories(LabCPP PUBLIC ../LibraryCPP)
target_link_libraries(LabCPP LibraryCPP)

add_test(NAME TestLabCPP COMMAND LabCPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)