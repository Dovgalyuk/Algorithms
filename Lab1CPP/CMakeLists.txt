add_executable(Lab1_Task1 lab1_task1.cpp)
add_executable(Lab1_Task2 lab1_task2.cpp)

foreach(TARGET Lab1_Task1 Lab1_Task2)
    target_link_libraries(${TARGET} LibraryCPP)
    target_include_directories(${TARGET} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../LibraryCPP)
endforeach()

enable_testing()

add_test(NAME Lab1_Task1_Test COMMAND Lab1_Task1 ${CMAKE_CURRENT_SOURCE_DIR}/input_1 result_1)
add_test(NAME Lab1_Task2_Test COMMAND Lab1_Task2 ${CMAKE_CURRENT_SOURCE_DIR}/input_2 result_2)
