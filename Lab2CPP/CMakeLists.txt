add_executable(Lab2CPP brackets.cpp)
target_include_directories(Lab2CPP PUBLIC ../LibraryCPPClass)
target_link_libraries(Lab2CPP LibraryCPPClass)

# Тесты через compare_files (вход → программа → выход → сравнение с эталоном)

add_test(NAME TestBrackets1
         COMMAND Lab2CPP
                 ${CMAKE_CURRENT_SOURCE_DIR}/tests/test1.txt
                 ${CMAKE_CURRENT_BINARY_DIR}/out1.txt)
add_test(NAME TestBrackets1_check
         COMMAND ${CMAKE_COMMAND} -E compare_files
                 ${CMAKE_CURRENT_BINARY_DIR}/out1.txt
                 ${CMAKE_CURRENT_SOURCE_DIR}/tests/test1_expected.txt)

add_test(NAME TestBrackets2
         COMMAND Lab2CPP
                 ${CMAKE_CURRENT_SOURCE_DIR}/tests/test2.txt
                 ${CMAKE_CURRENT_BINARY_DIR}/out2.txt)
add_test(NAME TestBrackets2_check
         COMMAND ${CMAKE_COMMAND} -E compare_files
                 ${CMAKE_CURRENT_BINARY_DIR}/out2.txt
                 ${CMAKE_CURRENT_SOURCE_DIR}/tests/test2_expected.txt)

add_test(NAME TestBrackets3
         COMMAND Lab2CPP
                 ${CMAKE_CURRENT_SOURCE_DIR}/tests/test3.txt
                 ${CMAKE_CURRENT_BINARY_DIR}/out3.txt)
add_test(NAME TestBrackets3_check
         COMMAND ${CMAKE_COMMAND} -E compare_files
                 ${CMAKE_CURRENT_BINARY_DIR}/out3.txt
                 ${CMAKE_CURRENT_SOURCE_DIR}/tests/test3_expected.txt)

add_test(NAME TestBrackets4
         COMMAND Lab2CPP
                 ${CMAKE_CURRENT_SOURCE_DIR}/tests/test4.txt
                 ${CMAKE_CURRENT_BINARY_DIR}/out4.txt)
add_test(NAME TestBrackets4_check
         COMMAND ${CMAKE_COMMAND} -E compare_files
                 ${CMAKE_CURRENT_BINARY_DIR}/out4.txt
                 ${CMAKE_CURRENT_SOURCE_DIR}/tests/test4_expected.txt)

add_test(NAME TestBrackets5
         COMMAND Lab2CPP
                 ${CMAKE_CURRENT_SOURCE_DIR}/tests/test5.txt
                 ${CMAKE_CURRENT_BINARY_DIR}/out5.txt)
add_test(NAME TestBrackets5_check
         COMMAND ${CMAKE_COMMAND} -E compare_files
                 ${CMAKE_CURRENT_BINARY_DIR}/out5.txt
                 ${CMAKE_CURRENT_SOURCE_DIR}/tests/test5_expected.txt)

add_test(NAME TestBrackets6
         COMMAND Lab2CPP
                 ${CMAKE_CURRENT_SOURCE_DIR}/tests/test6.txt
                 ${CMAKE_CURRENT_BINARY_DIR}/out6.txt)
add_test(NAME TestBrackets6_check
         COMMAND ${CMAKE_COMMAND} -E compare_files
                 ${CMAKE_CURRENT_BINARY_DIR}/out6.txt
                 ${CMAKE_CURRENT_SOURCE_DIR}/tests/test6_expected.txt)