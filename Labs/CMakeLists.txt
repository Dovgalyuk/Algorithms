add_executable(Labs "lab1.cpp")
target_include_directories(Labs PUBLIC ../LibraryCPP)
target_link_libraries(Labs LibraryCPP)

add_executable(Labs2 "lab2.cpp")
target_include_directories(Labs2 PUBLIC ../LibraryCPP)
target_link_libraries(Labs2 LibraryCPP)