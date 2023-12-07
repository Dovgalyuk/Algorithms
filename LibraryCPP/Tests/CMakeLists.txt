add_executable(TestArrayCPP array.cpp)
target_include_directories(TestArrayCPP PUBLIC ..)
target_link_libraries(TestArrayCPP LibraryCPP)
add_test(TestArrayCPP TestArrayCPP)

add_executable(TestStackCPP stack.cpp)
target_include_directories(TestStackCPP PUBLIC ..)
target_link_libraries(TestStackCPP LibraryCPP)
add_test(TestStackCPP TestStackCPP)

add_executable(TestVectorCPP vector.cpp)
target_include_directories(TestVectorCPP PUBLIC ..)
target_link_libraries(TestVectorCPP LibraryCPP)
add_test(TestVectorCPP TestVectorCPP)