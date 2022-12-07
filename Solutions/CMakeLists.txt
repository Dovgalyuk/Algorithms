
add_executable(Solution1 lab1.cpp)
target_include_directories(Solution1 PUBLIC ../LibraryCPPTemplate)
target_link_libraries(Solution1 LibraryCPP)

add_executable(Solution2 lab2.cpp)
target_include_directories(Solution2 PUBLIC ../LibraryCPP)
target_link_libraries(Solution2 LibraryCPP)