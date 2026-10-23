add_executable(Lab3CPP task.cpp)
target_include_directories(Lab3CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab3CPP LibraryCPP)

enable_testing()

add_test(
    NAME Lab3Run1
    COMMAND Lab3CPP
        ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt
        ${CMAKE_CURRENT_BINARY_DIR}/output1.txt
)

add_test(
    NAME Lab3Test1
    COMMAND ${CMAKE_COMMAND} -E compare_files
        ${CMAKE_CURRENT_BINARY_DIR}/output1.txt
        ${CMAKE_CURRENT_SOURCE_DIR}/proverka1.txt
)

set_tests_properties(Lab3Test1 PROPERTIES DEPENDS Lab3Run1)

add_test(
    NAME Lab3Run2
    COMMAND Lab3CPP
        ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt
        ${CMAKE_CURRENT_BINARY_DIR}/output2.txt
)

add_test(
    NAME Lab3Test2
    COMMAND ${CMAKE_COMMAND} -E compare_files
        ${CMAKE_CURRENT_BINARY_DIR}/output2.txt
        ${CMAKE_CURRENT_SOURCE_DIR}/proverka2.txt
)

set_tests_properties(Lab3Test2 PROPERTIES DEPENDS Lab3Run2)

add_test(
    NAME Lab3Run3
    COMMAND Lab3CPP
        ${CMAKE_CURRENT_SOURCE_DIR}/input3.txt
        ${CMAKE_CURRENT_BINARY_DIR}/output3.txt
)

add_test(
    NAME Lab3Test3
    COMMAND ${CMAKE_COMMAND} -E compare_files
        ${CMAKE_CURRENT_BINARY_DIR}/output3.txt
        ${CMAKE_CURRENT_SOURCE_DIR}/proverka3.txt
)

set_tests_properties(Lab3Test3 PROPERTIES DEPENDS Lab3Run3)