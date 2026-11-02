add_executable(Maze main.cpp)
target_include_directories(Maze PRIVATE ../LibraryCPPClass)
target_link_libraries(Maze LibraryCPPClass)

add_test(NAME TestMaze COMMAND ${CMAKE_COMMAND}
    -DPROGRAM=$<TARGET_FILE:Maze>
    -DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/input.txt
    -DEXPECTED=${CMAKE_CURRENT_SOURCE_DIR}/valid.txt
    -P ${CMAKE_CURRENT_SOURCE_DIR}/compare.cmake)

add_test(NAME TestMazeImpossible COMMAND ${CMAKE_COMMAND}
    -DPROGRAM=$<TARGET_FILE:Maze>
    -DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/input_impossible.txt
    -DEXPECTED=${CMAKE_CURRENT_SOURCE_DIR}/valid_impossible.txt
    -P ${CMAKE_CURRENT_SOURCE_DIR}/compare.cmake)
