add_executable(Lab3CPP main.cpp)
target_include_directories(Lab3CPP PRIVATE ${PROJECT_SOURCE_DIR}/LibraryCPP)
target_link_libraries(Lab3CPP PRIVATE LibraryCPP)

add_test(NAME KnightPath COMMAND ${CMAKE_COMMAND}
    "-DPROGRAM=$<TARGET_FILE:Lab3CPP>"
    "-DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/Tests/input.txt"
    "-DEXPECTED=${CMAKE_CURRENT_SOURCE_DIR}/Tests/expected.txt"
    -P "${CMAKE_CURRENT_SOURCE_DIR}/Tests/check.cmake"
)

function(add_knight_test name)
    add_test(NAME KnightPath_${name} COMMAND ${CMAKE_COMMAND}
        "-DPROGRAM=$<TARGET_FILE:Lab3CPP>"
        "-DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/Tests/${name}.input"
        "-DEXPECTED=${CMAKE_CURRENT_SOURCE_DIR}/Tests/${name}.expected"
        -P "${CMAKE_CURRENT_SOURCE_DIR}/Tests/check.cmake"
    )
endfunction()

add_knight_test(one_move)
add_knight_test(two_moves)
add_knight_test(open_corners)
add_knight_test(open_center)
add_knight_test(edge_to_edge)
add_knight_test(start_surrounded)
add_knight_test(finish_surrounded)
add_knight_test(wall_isolates)
add_knight_test(single_route)
add_knight_test(blocked_center)
add_knight_test(checkerboard)
add_knight_test(long_detour)
