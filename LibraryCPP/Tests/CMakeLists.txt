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

# дополнительные тесты списка (по 2 на контейнер)
add_executable(TestListInsertCPP list_insert.cpp)
target_include_directories(TestListInsertCPP PUBLIC ..)
target_link_libraries(TestListInsertCPP LibraryCPP)
add_test(TestListInsertCPP TestListInsertCPP)

add_executable(TestListEraseCPP list_erase.cpp)
target_include_directories(TestListEraseCPP PUBLIC ..)
target_link_libraries(TestListEraseCPP LibraryCPP)
add_test(TestListEraseCPP TestListEraseCPP)

# дополнительные тесты очереди
add_executable(TestQueueFifoCPP queue_fifo.cpp)
target_include_directories(TestQueueFifoCPP PUBLIC ..)
target_link_libraries(TestQueueFifoCPP LibraryCPP)
add_test(TestQueueFifoCPP TestQueueFifoCPP)

add_executable(TestQueueMixedCPP queue_mixed.cpp)
target_include_directories(TestQueueMixedCPP PUBLIC ..)
target_link_libraries(TestQueueMixedCPP LibraryCPP)
add_test(TestQueueMixedCPP TestQueueMixedCPP)
