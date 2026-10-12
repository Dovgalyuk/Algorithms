add_executable(Lab4Prim prim.cpp)
target_include_directories(Lab4Prim PUBLIC ../LibraryCPPTemplate)

foreach(test_name connected disconnected single_vertex)
    add_test(NAME TestPrim_${test_name} COMMAND ${CMAKE_COMMAND}
        -DPROGRAM=$<TARGET_FILE:Lab4Prim>
        -DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/${test_name}.txt
        -DEXPECTED=${CMAKE_CURRENT_SOURCE_DIR}/${test_name}_expected.txt
        -P ${CMAKE_CURRENT_SOURCE_DIR}/check_output.cmake)
endforeach()
