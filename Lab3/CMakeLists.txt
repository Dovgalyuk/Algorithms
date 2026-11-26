add_executable(Lab3 libirth.cpp)
target_link_libraries(Lab3 PRIVATE LibraryCPP)

add_test(
    NAME TestLab3
    COMMAND ${CMAKE_COMMAND}
        "-DPROGRAM=$<TARGET_FILE:Lab3>"
        "-DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/Test/input.txt"
        "-DEXPECTED=${CMAKE_CURRENT_SOURCE_DIR}/Test/expected.txt"
        -P "${CMAKE_CURRENT_SOURCE_DIR}/Test/check_output.cmake"
)

foreach(case IN ITEMS adjacent no_path boundary multiple_paths medium)
    add_test(
        NAME TestLab3_${case}
        COMMAND ${CMAKE_COMMAND}
            "-DPROGRAM=$<TARGET_FILE:Lab3>"
            "-DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/Test/input_${case}.txt"
            "-DEXPECTED=${CMAKE_CURRENT_SOURCE_DIR}/Test/expected_${case}.txt"
            -P "${CMAKE_CURRENT_SOURCE_DIR}/Test/check_output.cmake"
    )
endforeach()
