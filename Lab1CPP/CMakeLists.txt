add_executable(Lab1CPP lab1.cpp)
target_include_directories(Lab1CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab1CPP LibraryCPP)

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/input.txt")
    file(COPY input.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endif()

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/Tests")
    file(COPY Tests DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endif()

add_test(NAME TestLab1CPP COMMAND Lab1CPP)

file(GLOB TEST_FILES "${CMAKE_CURRENT_SOURCE_DIR}/Tests/*.txt")
foreach(TEST_FILE ${TEST_FILES})
    get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)
    
    add_test(
        NAME "Lab1_${TEST_NAME}"
        COMMAND ${CMAKE_COMMAND} -E copy "${TEST_FILE}" "${CMAKE_CURRENT_BINARY_DIR}/input.txt"
    )
    set_tests_properties("Lab1_${TEST_NAME}" PROPERTIES FIXTURES_SETUP "Fix_${TEST_NAME}")
    
    add_test(
        NAME "Run_${TEST_NAME}"
        COMMAND Lab1CPP
    )
    set_tests_properties("Run_${TEST_NAME}" PROPERTIES FIXTURES_REQUIRED "Fix_${TEST_NAME}")
endforeach()