add_executable(lab3_labyrinth labyrinth.cpp)
target_link_libraries(lab3_labyrinth LibraryCPP)
target_include_directories(lab3_labyrinth PRIVATE ../LibraryCPP)

add_test(NAME Lab3LabyrinthTest1 COMMAND lab3_labyrinth ${CMAKE_CURRENT_SOURCE_DIR}/Tests/Test1.txt)

add_test(NAME Lab3LabyrinthTest2 COMMAND lab3_labyrinth ${CMAKE_CURRENT_SOURCE_DIR}/Tests/Test2.txt)

add_test(NAME Lab3LabyrinthTest3 COMMAND lab3_labyrinth ${CMAKE_CURRENT_SOURCE_DIR}/Tests/Test3.txt)

add_test(NAME Lab3LabyrinthTest4 COMMAND lab3_labyrinth ${CMAKE_CURRENT_SOURCE_DIR}/Tests/Test4.txt)

add_test(NAME Lab3LabyrinthTest5 COMMAND lab3_labyrinth ${CMAKE_CURRENT_SOURCE_DIR}/Tests/Test5.txt)

add_test(NAME Lab3LabyrinthTest6 COMMAND lab3_labyrinth ${CMAKE_CURRENT_SOURCE_DIR}/Tests/Test6.txt)

add_test(NAME Lab3LabyrinthTest7 COMMAND lab3_labyrinth ${CMAKE_CURRENT_SOURCE_DIR}/Tests/Test7.txt)
