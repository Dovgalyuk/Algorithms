add_executable(Lab3CPPMaze maze.cpp)
target_include_directories(Lab3CPPMaze PRIVATE ../LibraryCPP)
target_link_libraries(Lab3CPPMaze PRIVATE LibraryCPP)
target_compile_features(Lab3CPPMaze PRIVATE cxx_std_17)

add_executable(TestLab3Containers containers_test.cpp)
target_include_directories(TestLab3Containers PRIVATE ../LibraryCPP)
target_link_libraries(TestLab3Containers PRIVATE LibraryCPP)
target_compile_features(TestLab3Containers PRIVATE cxx_std_17)
add_test(NAME TestLab3Containers COMMAND TestLab3Containers)
set_tests_properties(TestLab3Containers PROPERTIES TIMEOUT 10)

if(MSVC)
    target_compile_options(Lab3CPPMaze PRIVATE /utf-8)
endif()

function(add_maze_test name file code error)
    add_test(
        NAME ${name}
        COMMAND ${CMAKE_COMMAND}
            "-DPROGRAM=$<TARGET_FILE:Lab3CPPMaze>"
            "-DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/tests/${file}.txt"
            "-DEXPECTED=${CMAKE_CURRENT_SOURCE_DIR}/tests/${file}.out"
            "-DEXPECTED_CODE=${code}"
            "-DEXPECTED_ERROR=${error}"
            -P "${CMAKE_CURRENT_SOURCE_DIR}/check_maze.cmake"
    )
    set_tests_properties(${name} PROPERTIES TIMEOUT 10)
endfunction()

add_maze_test(TestLab3Example example 0 "")
add_maze_test(TestLab3Single single 0 "")
add_maze_test(TestLab3Straight straight 0 "")
add_maze_test(TestLab3Descending descending 0 "")
add_maze_test(TestLab3Detour detour 0 "")
add_maze_test(TestLab3NoPath no_path 0 "")
add_maze_test(TestLab3Equal equal 0 "")
add_maze_test(TestLab3NoDiagonal no_diagonal 0 "")
add_maze_test(TestLab3Cycles cycles 0 "")
add_maze_test(TestLab3Large large 0 "")
add_maze_test(TestLab3Empty empty 1 "Ошибка: пустой лабиринт")
add_maze_test(TestLab3Invalid invalid 1 "Ошибка: неверный лабиринт")
