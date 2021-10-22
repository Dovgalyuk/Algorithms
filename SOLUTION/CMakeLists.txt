add_executable(labone labone.cpp)
target_include_directories(labone PUBLIC ../LibraryCPP)
target_link_libraries(labone LibraryCPP)

add_executable(labtwo labtwo.cpp)
target_include_directories(labtwo PUBLIC ../LibraryCPP)
target_link_libraries(labtwo LibraryCPP)