if(MSVC)
    add_compile_options(/utf-8)
endif()

add_library(Lab6Core STATIC matrix_chain.cpp)
target_compile_features(Lab6Core PUBLIC cxx_std_11)
target_include_directories(Lab6Core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(Lab6BruteForce main.cpp)
target_link_libraries(Lab6BruteForce PRIVATE Lab6Core)

add_executable(Lab6Dynamic main.cpp)
target_link_libraries(Lab6Dynamic PRIVATE Lab6Core)
target_compile_definitions(Lab6Dynamic PRIVATE LAB6_USE_DYNAMIC)

add_executable(Lab6Benchmark benchmark.cpp)
target_link_libraries(Lab6Benchmark PRIVATE Lab6Core)

add_executable(Lab6Tests tests/test_matrix_chain.cpp)
target_link_libraries(Lab6Tests PRIVATE Lab6Core)

add_test(NAME Lab6Algorithms COMMAND Lab6Tests)
set_tests_properties(Lab6Algorithms PROPERTIES TIMEOUT 60)

foreach(program Lab6BruteForce Lab6Dynamic)
    foreach(test sample single pair classic right large avoid_overflow)
        add_test(NAME ${program}_${test}
            COMMAND ${CMAKE_COMMAND}
                -DPROGRAM=$<TARGET_FILE:${program}>
                -DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/tests/${test}.txt
                -DEXPECTED=${CMAKE_CURRENT_SOURCE_DIR}/tests/${test}.expected
                -P ${CMAKE_CURRENT_SOURCE_DIR}/tests/check_output.cmake)
    endforeach()
    foreach(test empty incomplete incompatible zero negative text overflow too_large)
        add_test(NAME ${program}_${test}
            COMMAND ${CMAKE_COMMAND}
                -DPROGRAM=$<TARGET_FILE:${program}>
                -DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/tests/${test}.txt
                -DFAIL_EXPECTED=ON
                -P ${CMAKE_CURRENT_SOURCE_DIR}/tests/check_output.cmake)
    endforeach()
    add_test(NAME ${program}_missing_file
        COMMAND ${CMAKE_COMMAND}
            -DPROGRAM=$<TARGET_FILE:${program}>
            -DINPUT=${CMAKE_CURRENT_BINARY_DIR}/missing_input_file.txt
            -DFAIL_EXPECTED=ON
            -P ${CMAKE_CURRENT_SOURCE_DIR}/tests/check_output.cmake)
    add_test(NAME ${program}_stdin
        COMMAND ${CMAKE_COMMAND}
            -DPROGRAM=$<TARGET_FILE:${program}>
            -DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/tests/sample.txt
            -DEXPECTED=${CMAKE_CURRENT_SOURCE_DIR}/tests/sample.expected
            -DUSE_STDIN=ON
            -P ${CMAKE_CURRENT_SOURCE_DIR}/tests/check_output.cmake)
endforeach()
