add_executable(LabCPP lab2.cpp)
target_include_directories(LabCPP PUBLIC ../LibraryCPP)
target_link_libraries(LabCPP LibraryCPP)