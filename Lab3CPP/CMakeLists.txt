
add_library(Lab3CPP STATIC Lab3CPP.cpp)

target_include_directories(Lab3CPP PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(Lab3CPP PUBLIC LibraryCPP)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE Lab3CPP)

set(COMPARE_SCRIPT
    "${CMAKE_CURRENT_SOURCE_DIR}/CompareOutput.cmake"
)

foreach(group RANGE 1 3)
    foreach(number RANGE 1 10)

        set(test_name "Lab3_Test${group}_${number}")

        set(input_file
            "${CMAKE_CURRENT_SOURCE_DIR}/Tests/Test${group}_${number}.txt"
        )

        set(expected_file
            "${CMAKE_CURRENT_SOURCE_DIR}/Tests/Expected_Test${group}_${number}.txt"
        )

        add_test(
            NAME ${test_name}
            COMMAND ${CMAKE_COMMAND}
                "-DPROGRAM=$<TARGET_FILE:main>"
                "-DINPUT=${input_file}"
                "-DEXPECTED=${expected_file}"
                -P "${COMPARE_SCRIPT}"
        )

    endforeach()
endforeach()

add_test(
    NAME Lab3_NoPath
    COMMAND ${CMAKE_COMMAND}
        "-DPROGRAM=$<TARGET_FILE:main>"
        "-DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/Tests/Test3_NoPath.txt"
        "-DEXPECTED=${CMAKE_CURRENT_SOURCE_DIR}/Tests/Expected_NoPath.txt"
        -P "${COMPARE_SCRIPT}"
)

add_test(
    NAME Lab3_Error_NoArgument
    COMMAND main
)

set_tests_properties(Lab3_Error_NoArgument PROPERTIES
    WILL_FAIL TRUE
)

add_test(
    NAME Lab3_Error_FileNotFound
    COMMAND main "${CMAKE_CURRENT_SOURCE_DIR}/Tests/Test3_NoSuchFile.txt"
)

set_tests_properties(Lab3_Error_FileNotFound PROPERTIES
    WILL_FAIL TRUE
)

foreach(error_case IN ITEMS Empty OnlyS OnlyE NoS NoE)

    add_test(
        NAME Lab3_Error_${error_case}
        COMMAND main
            "${CMAKE_CURRENT_SOURCE_DIR}/Tests/Test3_${error_case}.txt"
    )

    set_tests_properties(
        Lab3_Error_${error_case}
        PROPERTIES
        WILL_FAIL TRUE
    )

endforeach()

set_tests_properties(
    Lab3_Test1_1
    Lab3_Test1_2
    Lab3_Test1_3
    Lab3_NoPath
    PROPERTIES TIMEOUT 10
)
