add_executable(Labs2 "lab2.cpp")
target_include_directories(Labs2 PUBLIC ../LibraryCPP)
target_link_libraries(Labs2 LibraryCPP)