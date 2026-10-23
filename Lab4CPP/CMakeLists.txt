add_executable(Lab4CPP main.cpp)
target_include_directories(Lab4CPP PRIVATE ../LibraryCPPTemplate)

enable_testing()

foreach(test_number RANGE 1 4)
    add_test(
        NAME Lab4Run${test_number}
        COMMAND Lab4CPP
            ${CMAKE_CURRENT_SOURCE_DIR}/input${test_number}.txt
            ${CMAKE_CURRENT_BINARY_DIR}/output${test_number}.txt
    )

    add_test(
        NAME Lab4Test${test_number}
        COMMAND ${CMAKE_COMMAND} -E compare_files
            ${CMAKE_CURRENT_BINARY_DIR}/output${test_number}.txt
            ${CMAKE_CURRENT_SOURCE_DIR}/expected${test_number}.txt
    )

    set_tests_properties(Lab4Test${test_number} PROPERTIES DEPENDS Lab4Run${test_number})
endforeach()

