add_executable(Lab3CPP main.cpp)

target_link_libraries(Lab3CPP LibraryCPP)

foreach(test_number RANGE 1 7)
    add_test(
        NAME TestLab3CPP_${test_number}
        COMMAND ${CMAKE_COMMAND}
            "-DPROGRAM=$<TARGET_FILE:Lab3CPP>"
            "-DTEST_DIR=${CMAKE_CURRENT_SOURCE_DIR}/Tests"
            "-DTEST_NUMBER=${test_number}"
            -P "${CMAKE_CURRENT_SOURCE_DIR}/check.cmake"
    )
endforeach()
