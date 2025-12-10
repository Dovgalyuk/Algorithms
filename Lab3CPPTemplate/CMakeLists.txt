add_executable(KnightPath knightPath.cpp)

target_include_directories(KnightPath PUBLIC ../LibraryCPPTemplate)
target_link_libraries(KnightPath LibraryCPPTemplate)

enable_testing()

add_test(NAME TestKnightPath COMMAND KnightPath ${CMAKE_CURRENT_SOURCE_DIR}/input.txt ${CMAKE_CURRENT_SOURCE_DIR}/result.txt )
add_test(NAME CompareKnightPath COMMAND ${CMAKE_COMMAND} -E compare_files ${CMAKE_CURRENT_SOURCE_DIR}/result.txt ${CMAKE_CURRENT_SOURCE_DIR}/output.txt)

add_test(NAME TestKnightPath2 COMMAND KnightPath ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt ${CMAKE_CURRENT_SOURCE_DIR}/result.txt )
add_test(NAME CompareKnightPath2 COMMAND ${CMAKE_COMMAND} -E compare_files ${CMAKE_CURRENT_SOURCE_DIR}/result.txt ${CMAKE_CURRENT_SOURCE_DIR}/output2.txt)

add_test(NAME TestKnightPath3 COMMAND KnightPath ${CMAKE_CURRENT_SOURCE_DIR}/input3.txt ${CMAKE_CURRENT_SOURCE_DIR}/result.txt )
add_test(NAME CompareKnightPath3 COMMAND ${CMAKE_COMMAND} -E compare_files ${CMAKE_CURRENT_SOURCE_DIR}/result.txt ${CMAKE_CURRENT_SOURCE_DIR}/output3.txt)
