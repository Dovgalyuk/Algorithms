add_executable(Task2_TatlybaevAYu ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
target_include_directories(Task2_TatlybaevAYu PRIVATE ${CMAKE_SOURCE_DIR}/LibraryCPPTemplate)

add_test(NAME Task2_TatlybaevAY_test1
    COMMAND ${CMAKE_COMMAND}
    -DEXE=$<TARGET_FILE:Task2_TatlybaevAYu>
    -DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/input1.txt
    -DEXPECTED=${CMAKE_CURRENT_SOURCE_DIR}/output1.txt
    -P ${CMAKE_SOURCE_DIR}/Practice/test.cmake)

add_test(NAME Task2_TatlybaevAY_test2
    COMMAND ${CMAKE_COMMAND}
    -DEXE=$<TARGET_FILE:Task2_TatlybaevAYu>
    -DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/input2.txt
    -DEXPECTED=${CMAKE_CURRENT_SOURCE_DIR}/output2.txt
    -P ${CMAKE_SOURCE_DIR}/Practice/test.cmake)