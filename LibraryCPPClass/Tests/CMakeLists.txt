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


add_executable(TestStackCPPClass stack.cpp)

target_link_libraries(TestStackCPPClass PRIVATE LibraryCPPClass)

target_include_directories(TestStackCPPClass PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

add_test(NAME TestStackCPPClass COMMAND TestStackCPPClass)


add_executable(TestQueueCPPClass queue.cpp)

target_link_libraries(TestQueueCPPClass PRIVATE LibraryCPPClass)

target_include_directories(TestQueueCPPClass PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

add_test(NAME TestQueueCPPClass COMMAND TestQueueCPPClass)


add_executable(TestVectorCPPClass vector.cpp)

target_link_libraries(TestVectorCPPClass PRIVATE LibraryCPPClass)

target_include_directories(TestVectorCPPClass PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

add_test(NAME TestVectorCPPClass COMMAND TestVectorCPPClass)
