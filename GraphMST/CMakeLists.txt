add_executable(Kruskal main.cpp)
target_include_directories(Kruskal PRIVATE ../LibraryCPPTemplate)

function(add_kruskal_test name input expected)
    add_test(NAME ${name} COMMAND ${CMAKE_COMMAND}
        -DPROGRAM=$<TARGET_FILE:Kruskal>
        -DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/${input}
        -DEXPECTED=${CMAKE_CURRENT_SOURCE_DIR}/${expected}
        -P ${CMAKE_CURRENT_SOURCE_DIR}/compare.cmake)
endfunction()

add_kruskal_test(TestKruskal input.txt valid.txt)
add_kruskal_test(TestKruskalDisconnected input_disconnected.txt valid_disconnected.txt)
add_kruskal_test(TestKruskalNegative input_negative.txt valid_negative.txt)
add_kruskal_test(TestKruskalSingle input_single.txt valid_single.txt)
