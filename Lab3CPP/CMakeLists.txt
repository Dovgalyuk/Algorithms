add_executable(Lab3CPP main.cpp)
target_include_directories(Lab3CPP PRIVATE ${CMAKE_SOURCE_DIR}/LibraryCPP)
target_link_libraries(Lab3CPP PRIVATE LibraryCPP)

set(COMPARE_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/compare.cmake")

add_test(
    NAME TestLab3CPP_Test1
    COMMAND ${CMAKE_COMMAND}
        -DEXE=$<TARGET_FILE:Lab3CPP>
        -DIN=${CMAKE_CURRENT_SOURCE_DIR}/input1.txt
        -DEXPECTED=${CMAKE_CURRENT_SOURCE_DIR}/output1.txt
        -P ${COMPARE_SCRIPT}
)

add_test(
    NAME TestLab3CPP_Test2
    COMMAND ${CMAKE_COMMAND}
        -DEXE=$<TARGET_FILE:Lab3CPP>
        -DIN=${CMAKE_CURRENT_SOURCE_DIR}/input2.txt
        -DEXPECTED=${CMAKE_CURRENT_SOURCE_DIR}/output2.txt
        -P ${COMPARE_SCRIPT}
)

add_test(
    NAME TestLab3CPP_Test3
    COMMAND ${CMAKE_COMMAND}
        -DEXE=$<TARGET_FILE:Lab3CPP>
        -DIN=${CMAKE_CURRENT_SOURCE_DIR}/input3.txt
        -DEXPECTED=${CMAKE_CURRENT_SOURCE_DIR}/output3.txt
        -P ${COMPARE_SCRIPT}
)

add_test(
    NAME TestLab3CPP_Test4
    COMMAND ${CMAKE_COMMAND}
        -DEXE=$<TARGET_FILE:Lab3CPP>
        -DIN=${CMAKE_CURRENT_SOURCE_DIR}/input4.txt
        -DEXPECTED=${CMAKE_CURRENT_SOURCE_DIR}/output4.txt
        -P ${COMPARE_SCRIPT}
)