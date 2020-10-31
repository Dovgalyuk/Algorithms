add_executable(IndividualTask main.cpp)
target_include_directories(IndividualTask PUBLIC ../LibraryCPP)
target_link_libraries(IndividualTask LibraryCPP)