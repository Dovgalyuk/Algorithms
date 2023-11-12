add_executable(Lab1C lab3 1.cpp)
target_include_directories(Lab1C PUBLIC ../LibraryC)
target_link_libraries(Lab1C LibraryC)
