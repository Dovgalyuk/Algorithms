add_executable(Lab2CPPClass main.cpp)
target_include_directories(Lab2CPPClass PUBLIC ../LibraryCPPClass)
target_link_libraries(Lab2CPPClass LibraryCPPClass)

# add some tests