add_executable(TaskFirstCPP Lab1/LabWork1.cpp)
target_include_directories(TaskFirstCPP PUBLIC ${PROJECT_SOURCE_DIR}/LibraryCPP)
target_link_libraries(TaskFirstCPP LibraryCPP)

add_executable(TaskSecondCPP Lab2/LabWork2.cpp)
target_include_directories(TaskSecondCPP PUBLIC ${PROJECT_SOURCE_DIR}/LibraryCPP)
target_link_libraries(TaskSecondCPP LibraryCPP)
