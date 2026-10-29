add_executable(QueueVector QueueVector.cpp)

target_include_directories(QueueVector PRIVATE
    ${PROJECT_SOURCE_DIR}/LibraryCPP
)

target_link_libraries(QueueVector PRIVATE LibraryCPP)

add_test(
    NAME Lab2Test1
    COMMAND QueueVector ${CMAKE_CURRENT_SOURCE_DIR}/Test/input1.txt
)

add_test(
    NAME Lab2Test2
    COMMAND QueueVector ${CMAKE_CURRENT_SOURCE_DIR}/Test/input2.txt
)

add_test(
    NAME Lab2Test3
    COMMAND QueueVector ${CMAKE_CURRENT_SOURCE_DIR}/Test/input3.txt
)