add_executable(Lab3CPPTemplate lab3.cpp)
add_executable(Test test.cpp)
# target_include_directories(Lab3CPPTemplate PUBLIC ../LibraryCPPTemplate)
# target_link_libraries(Lab3CPPTemplate LibraryCPPTemplate)

include_directories(${CMAKE_SOURCE_DIR}/LibraryCPPTemplate)

add_test(NAME TestLab3CPPTemplate COMMAND Lab3CPPTemplate ${CMAKE_CURRENT_SOURCE_DIR}/input.txt ${CMAKE_BINARY_DIR}/output.txt)
add_test(NAME TestLab3CPPTemplate_EqualFiles COMMAND Test ${CMAKE_BINARY_DIR}/output.txt ${CMAKE_CURRENT_SOURCE_DIR}/best_output.txt)
