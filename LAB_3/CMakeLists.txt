add_executable(Lab3Components components.cpp)
target_include_directories(Lab3Components PRIVATE ../LibraryCPPClass)
target_link_libraries(Lab3Components PRIVATE LibraryCPPClass)
target_compile_features(Lab3Components PRIVATE cxx_std_11)
target_compile_definitions(Lab3Components PRIVATE DEFAULT_INPUT_FILE="${CMAKE_CURRENT_SOURCE_DIR}/input.txt")

function(component_test name input expected status)
    file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/${name}.txt" "${input}")
    add_test(NAME ${name} COMMAND ${CMAKE_COMMAND}
        "-DPROGRAM=$<TARGET_FILE:Lab3Components>"
        "-DINPUT=${CMAKE_CURRENT_BINARY_DIR}/${name}.txt"
        "-DOUTPUT=${CMAKE_CURRENT_BINARY_DIR}/${name}.out"
        "-DEXPECTED=${expected}" "-DSTATUS=${status}"
        -P "${CMAKE_CURRENT_SOURCE_DIR}/check.cmake")
endfunction()

add_test(NAME ComponentsExample COMMAND ${CMAKE_COMMAND}
    "-DPROGRAM=$<TARGET_FILE:Lab3Components>"
    "-DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/input.txt"
    "-DOUTPUT=${CMAKE_CURRENT_BINARY_DIR}/example.out"
    "-DEXPECTED=2\n1 2 5\n3 4\n" -DSTATUS=0
    -P "${CMAKE_CURRENT_SOURCE_DIR}/check.cmake")
component_test(ComponentsEmpty "0\n" "0\n" 0)
component_test(ComponentsSingle "1\n0\n" "1\n1\n" 0)
component_test(ComponentsIsolated "3\n0 0 0\n0 0 0\n0 0 0\n" "3\n1\n2\n3\n" 0)
component_test(ComponentsCycle "3\n0 1 1\n1 0 1\n1 1 0\n" "1\n1 2 3\n" 0)
component_test(ComponentsLoop "1\n1\n" "1\n1\n" 0)
component_test(ComponentsIncomplete "2\n0 1\n1\n" "" 1)
component_test(ComponentsDirected "2\n0 1\n0 0\n" "" 1)
component_test(ComponentsInvalid "1\n2\n" "" 1)

# A wide BFS frontier exercises queue growth.
set(star "12\n")
foreach(i RANGE 0 11)
    foreach(j RANGE 0 11)
        if((i EQUAL 0 AND NOT j EQUAL 0) OR (j EQUAL 0 AND NOT i EQUAL 0))
            string(APPEND star "1 ")
        else()
            string(APPEND star "0 ")
        endif()
    endforeach()
    string(APPEND star "\n")
endforeach()
component_test(ComponentsStar "${star}" "1\n1 2 3 4 5 6 7 8 9 10 11 12\n" 0)
