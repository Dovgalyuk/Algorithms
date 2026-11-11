add_executable(TestArrayCPP array.cpp)
target_include_directories(TestArrayCPP PUBLIC ..)
target_link_libraries(TestArrayCPP LibraryCPP)
add_test(TestArrayCPP TestArrayCPP)

add_executable(TestListCPP list.cpp)
target_include_directories(TestListCPP PUBLIC ..)
target_link_libraries(TestListCPP LibraryCPP)
add_test(TestListCPP TestListCPP)

add_executable(TestQueueCPP queue.cpp)
target_include_directories(TestQueueCPP PUBLIC ..)
target_link_libraries(TestQueueCPP LibraryCPP)
add_test(TestQueueCPP TestQueueCPP)
set_tests_properties(TestQueueCPP PROPERTIES TIMEOUT 10)

add_executable(TestStackCPP stack.cpp)
target_include_directories(TestStackCPP PUBLIC ..)
target_link_libraries(TestStackCPP LibraryCPP)
add_test(TestStackCPP TestStackCPP)

add_executable(TestVectorCPP vector.cpp)
target_include_directories(TestVectorCPP PUBLIC ..)
target_link_libraries(TestVectorCPP LibraryCPP)
add_test(TestVectorCPP TestVectorCPP)
set_tests_properties(TestVectorCPP PROPERTIES TIMEOUT 10)

# Additional direct checks for the containers used by laboratory 3.
add_executable(TestLab3ContainersCPP containers_lab3.cpp)
target_include_directories(TestLab3ContainersCPP PRIVATE ..)
target_link_libraries(TestLab3ContainersCPP PRIVATE LibraryCPP)
add_test(NAME TestLab3ContainersCPP COMMAND TestLab3ContainersCPP)
