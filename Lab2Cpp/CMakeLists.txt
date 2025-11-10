# Основная программа
add_executable(Lab2Cpp lab2.cpp)

if(TARGET LibraryCPP)
    target_link_libraries(Lab2Cpp LibraryCPP)
    target_include_directories(Lab2Cpp PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../LibraryCPP)
endif()

configure_file(input.txt input.txt COPYONLY)
configure_file(input1.txt input1.txt COPYONLY)
configure_file(input2.txt input2.txt COPYONLY)
configure_file(input3.txt input3.txt COPYONLY)
configure_file(input4.txt input4.txt COPYONLY)

enable_testing()

# Основной тест
add_test(NAME Lab2Cpp_Test1 COMMAND Lab2Cpp ${CMAKE_CURRENT_SOURCE_DIR}/input.txt ${CMAKE_CURRENT_BINARY_DIR}/output1.txt)
add_test(NAME Lab2Cpp_Verify1 COMMAND ${CMAKE_COMMAND} -E compare_files ${CMAKE_CURRENT_BINARY_DIR}/output1.txt ${CMAKE_CURRENT_SOURCE_DIR}/expected1.txt)

# Дополнительные тесты
add_test(NAME Lab2Cpp_Test2 COMMAND Lab2Cpp ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt ${CMAKE_CURRENT_BINARY_DIR}/output2.txt)
add_test(NAME Lab2Cpp_Verify2 COMMAND ${CMAKE_COMMAND} -E compare_files ${CMAKE_CURRENT_BINARY_DIR}/output2.txt ${CMAKE_CURRENT_SOURCE_DIR}/expected2.txt)

add_test(NAME Lab2Cpp_Test3 COMMAND Lab2Cpp ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt ${CMAKE_CURRENT_BINARY_DIR}/output3.txt)
add_test(NAME Lab2Cpp_Verify3 COMMAND ${CMAKE_COMMAND} -E compare_files ${CMAKE_CURRENT_BINARY_DIR}/output3.txt ${CMAKE_CURRENT_SOURCE_DIR}/expected3.txt)

add_test(NAME Lab2Cpp_Test4 COMMAND Lab2Cpp ${CMAKE_CURRENT_SOURCE_DIR}/input3.txt ${CMAKE_CURRENT_BINARY_DIR}/output4.txt)
add_test(NAME Lab2Cpp_Verify4 COMMAND ${CMAKE_COMMAND} -E compare_files ${CMAKE_CURRENT_BINARY_DIR}/output4.txt ${CMAKE_CURRENT_SOURCE_DIR}/expected4.txt)

add_test(NAME Lab2Cpp_Test5 COMMAND Lab2Cpp ${CMAKE_CURRENT_SOURCE_DIR}/input4.txt ${CMAKE_CURRENT_BINARY_DIR}/output5.txt)
add_test(NAME Lab2Cpp_Verify5 COMMAND ${CMAKE_COMMAND} -E compare_files ${CMAKE_CURRENT_BINARY_DIR}/output5.txt ${CMAKE_CURRENT_SOURCE_DIR}/expected5.txt)