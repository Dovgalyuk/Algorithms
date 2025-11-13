add_executable(Lab3CPPClass lab3.cpp)
target_include_directories(Lab3CPPClass PUBLIC ../LibraryCPPClass)
target_link_libraries(Lab3CPPClass LibraryCPPClass)

add_subdirectory(Tests)