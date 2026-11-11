cmake_minimum_required(VERSION 3.12)
project(Lab3CPP CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Lab3CPP main.cpp)
target_include_directories(Lab3CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab3CPP LibraryCPP)

enable_testing()

add_test(
    NAME Lab3_Test1
    COMMAND ${CMAKE_COMMAND}
        -DEXEC=$<TARGET_FILE:Lab3CPP>
        -DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/Test/input1.txt
        -DEXPECTED=${CMAKE_CURRENT_SOURCE_DIR}/Test/output1.txt
        -P "${CMAKE_CURRENT_SOURCE_DIR}/RunTest.cmake"
)

add_test(
    NAME Lab3_Test2
    COMMAND ${CMAKE_COMMAND}
        -DEXEC=$<TARGET_FILE:Lab3CPP>
        -DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/Test/input2.txt
        -DEXPECTED=${CMAKE_CURRENT_SOURCE_DIR}/Test/output2.txt
        -P "${CMAKE_CURRENT_SOURCE_DIR}/RunTest.cmake"
)

add_test(
    NAME Lab3_Test3
    COMMAND ${CMAKE_COMMAND}
        -DEXEC=$<TARGET_FILE:Lab3CPP>
        -DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/Test/input3.txt
        -DEXPECTED=${CMAKE_CURRENT_SOURCE_DIR}/Test/output3.txt
        -P "${CMAKE_CURRENT_SOURCE_DIR}/RunTest.cmake"
)