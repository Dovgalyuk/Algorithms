add_executable(Labs "lab3.cpp")
target_include_directories(Labs PUBLIC ../LibraryCPP)
target_link_libraries(Labs LibraryCPP)
