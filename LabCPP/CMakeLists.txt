add_executable(LabCPP lab3.cpp)
target_include_directories(LabCPP PUBLIC ../LibraryCPP)
target_link_libraries(LabCPP LibraryCPP)