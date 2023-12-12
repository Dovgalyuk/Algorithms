add_executable(TestVectorCPP vector.cpp)
target_include_directories(TestVectorCPP PUBLIC ..)
target_link_libraries(TestVectorCPP LibraryCPP)
add_test(TestVectorCPP TestVectorCPP)

add_executable(TestStackCPP stack.cpp)
target_include_directories(TestStackCPP PUBLIC ..)
target_link_libraries(TestStackCPP LibraryCPP)
add_test(TestStackCPP TestStackCPP)

