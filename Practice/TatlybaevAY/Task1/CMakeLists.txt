add_executable(Task1_TatlybaevAY ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
target_include_directories(Task1_TatlybaevAY PRIVATE ${CMAKE_SOURCE_DIR}/LibraryCPPTemplate)

add_test(NAME Task1_TatlybaevAY_test1
    COMMAND ${CMAKE_COMMAND}
    -DEXE=$<TARGET_FILE:Task1_TatlybaevAY>
    -DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/input1.txt
    -DEXPECTED=${CMAKE_CURRENT_SOURCE_DIR}/output1.txt
    -P ${CMAKE_SOURCE_DIR}/Practice/test.cmake)

add_test(NAME Task1_TatlybaevAY_test2
    COMMAND ${CMAKE_COMMAND}
    -DEXE=$<TARGET_FILE:Task1_TatlybaevAY>
    -DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/input2.txt
    -DEXPECTED=${CMAKE_CURRENT_SOURCE_DIR}/output2.txt
    -P ${CMAKE_SOURCE_DIR}/Practice/test.cmake)