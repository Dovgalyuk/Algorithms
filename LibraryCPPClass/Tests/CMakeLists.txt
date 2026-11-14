add_executable(TestArrayCPPClass array.cpp)

target_link_libraries(TestArrayCPPClass PRIVATE LibraryCPPClass)

target_include_directories(TestArrayCPPClass PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

add_test(NAME TestArrayCPPClass COMMAND TestArrayCPPClass)

add_executable(TestListCPPClass list.cpp)

target_link_libraries(TestListCPPClass PRIVATE LibraryCPPClass)

target_include_directories(TestListCPPClass PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

add_test(NAME TestListCPPClass COMMAND TestListCPPClass)

# add_executable(TestQueueCPPClass queue.cpp)
# target_include_directories(TestQueueCPPClass PUBLIC ..)
# target_link_libraries(TestQueueCPPClass LibraryCPPClass)
# add_test(TestQueueCPPClass TestQueueCPPClass)
# set_tests_properties(TestQueueCPPClass PROPERTIES TIMEOUT 10)

add_executable(TestStackCPPClass stack.cpp)

target_link_libraries(TestStackCPPClass PRIVATE LibraryCPPClass)

target_include_directories(TestStackCPPClass PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

add_test(NAME TestStackCPPClass COMMAND TestStackCPPClass)

# add_executable(TestVectorCPPClass vector.cpp)
# target_include_directories(TestVectorCPPClass PUBLIC ..)
# target_link_libraries(TestVectorCPPClass LibraryCPPClass)
# add_test(TestVectorCPPClass TestVectorCPPClass)
# set_tests_properties(TestVectorCPPClass PROPERTIES TIMEOUT 10)
