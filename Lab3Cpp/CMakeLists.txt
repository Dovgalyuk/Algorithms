# Основная программа
add_executable(Lab3Cpp lab3.cpp)

if(TARGET LibraryCPP)
    target_link_libraries(Lab3Cpp LibraryCPP)
    target_include_directories(Lab3Cpp PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../LibraryCPP)
endif()

enable_testing()

# Основной тест
add_test(NAME Lab3Cpp_Test1 COMMAND Lab3Cpp ${CMAKE_CURRENT_SOURCE_DIR}/input.txt ${CMAKE_CURRENT_BINARY_DIR}/output1.txt)
add_test(NAME Lab3Cpp_Verify1 COMMAND ${CMAKE_COMMAND} -E compare_files ${CMAKE_CURRENT_BINARY_DIR}/output1.txt ${CMAKE_CURRENT_SOURCE_DIR}/expected1.txt)

# Дополнительные тесты
add_test(NAME Lab3Cpp_Test2 COMMAND Lab3Cpp ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt ${CMAKE_CURRENT_BINARY_DIR}/output2.txt)
add_test(NAME Lab3Cpp_Verify2 COMMAND ${CMAKE_COMMAND} -E compare_files ${CMAKE_CURRENT_BINARY_DIR}/output2.txt ${CMAKE_CURRENT_SOURCE_DIR}/expected2.txt)

add_test(NAME Lab3Cpp_Test3 COMMAND Lab3Cpp ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt ${CMAKE_CURRENT_BINARY_DIR}/output3.txt)
add_test(NAME Lab3Cpp_Verify3 COMMAND ${CMAKE_COMMAND} -E compare_files ${CMAKE_CURRENT_BINARY_DIR}/output3.txt ${CMAKE_CURRENT_SOURCE_DIR}/expected3.txt)