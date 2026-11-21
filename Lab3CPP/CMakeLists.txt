add_executable(Lab3CPP main.cpp)
target_include_directories(Lab3CPP PRIVATE ../LibraryCPP)
target_link_libraries(Lab3CPP PRIVATE LibraryCPP)

add_test(
    NAME TestLab3CPP_Run
    COMMAND Lab3CPP
        ${CMAKE_CURRENT_SOURCE_DIR}/input.txt
        ${CMAKE_CURRENT_BINARY_DIR}/output.txt
)

add_test(
    NAME TestLab3CPP_Compare
    COMMAND ${CMAKE_COMMAND} -E compare_files
        ${CMAKE_CURRENT_BINARY_DIR}/output.txt
        ${CMAKE_CURRENT_SOURCE_DIR}/valid.txt
)
set_tests_properties(TestLab3CPP_Compare PROPERTIES DEPENDS TestLab3CPP_Run)

add_test(
    NAME TestLab3CPP_NoPath_Run
    COMMAND Lab3CPP
        ${CMAKE_CURRENT_SOURCE_DIR}/input_no_path.txt
        ${CMAKE_CURRENT_BINARY_DIR}/output_no_path.txt
)
add_test(
    NAME TestLab3CPP_NoPath_Compare
    COMMAND ${CMAKE_COMMAND} -E compare_files
        ${CMAKE_CURRENT_BINARY_DIR}/output_no_path.txt
        ${CMAKE_CURRENT_SOURCE_DIR}/valid_no_path.txt
)
set_tests_properties(TestLab3CPP_NoPath_Compare PROPERTIES DEPENDS TestLab3CPP_NoPath_Run)

foreach(name cycle named wide)
    add_test(
        NAME TestLab3CPP_${name}_Run
        COMMAND Lab3CPP
            ${CMAKE_CURRENT_SOURCE_DIR}/input_${name}.txt
            ${CMAKE_CURRENT_BINARY_DIR}/output_${name}.txt
    )
    add_test(
        NAME TestLab3CPP_${name}_Compare
        COMMAND ${CMAKE_COMMAND} -E compare_files
            ${CMAKE_CURRENT_BINARY_DIR}/output_${name}.txt
            ${CMAKE_CURRENT_SOURCE_DIR}/valid_${name}.txt
    )
    set_tests_properties(TestLab3CPP_${name}_Compare PROPERTIES DEPENDS TestLab3CPP_${name}_Run)
endforeach()
