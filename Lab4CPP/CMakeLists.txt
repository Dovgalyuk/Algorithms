add_executable(Floyd floyd.cpp)
target_link_libraries(Floyd PRIVATE LibraryCPPTemplate)

foreach(example IN ITEMS detour negative cycle invalid)
    add_test(NAME Floyd_${example} COMMAND "${CMAKE_COMMAND}"
        "-DPROGRAM=$<TARGET_FILE:Floyd>"
        "-DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/${example}.txt"
        "-DEXPECTED=${CMAKE_CURRENT_SOURCE_DIR}/${example}.expected"
        -P "${CMAKE_CURRENT_SOURCE_DIR}/check_output.cmake")
endforeach()
