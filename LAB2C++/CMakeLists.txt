
add_executable(LAB2C++ main.cpp)

target_include_directories(LAB2C++ PRIVATE
    ${PROJECT_SOURCE_DIR}/LibraryCPP
)

target_link_libraries(LAB2C++ PRIVATE LibraryCPP)

set(LAB2CXX_TEST_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tests")
set(LAB2CXX_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/test_output")

file(MAKE_DIRECTORY "${LAB2CXX_OUTPUT_DIR}")

foreach(TEST_NUMBER RANGE 1 5)
    add_test(
        NAME LAB2CXXTest${TEST_NUMBER}
        COMMAND ${CMAKE_COMMAND}
            "-DPROGRAM=$<TARGET_FILE:LAB2C++>"
            "-DINPUT=${LAB2CXX_TEST_DIR}/input${TEST_NUMBER}.txt"
            "-DEXPECTED=${LAB2CXX_TEST_DIR}/expected${TEST_NUMBER}.txt"
            "-DACTUAL=${LAB2CXX_OUTPUT_DIR}/actual${TEST_NUMBER}.txt"
            -P "${CMAKE_CURRENT_SOURCE_DIR}/check_brackets.cmake"
    )
endforeach()
