cmake_minimum_required(VERSION 3.10)
project(Lab2CPP)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(../LibraryCPP/Tests ${CMAKE_BINARY_DIR}/LibraryCPP_Tests)

add_executable(script annoyingscript.cpp)
target_include_directories(script PUBLIC ../LibraryCPP)
target_link_libraries(script PRIVATE LibraryCPP)

enable_testing()

# --- Скрипт 1: Hello, World + склейка стека ---
add_test(NAME script1_hello
    COMMAND script
        ${CMAKE_CURRENT_SOURCE_DIR}/script1.txt
        ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt
)
set_property(TEST script1_hello PROPERTY
    PASS_REGULAR_EXPRESSION "Hello, World!")

# --- Скрипт 2: чтение input + условие ---
add_test(NAME script2_cond_A
    COMMAND script
        ${CMAKE_CURRENT_SOURCE_DIR}/script2.txt
        ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt
)
set_property(TEST script2_cond_A PROPERTY
    PASS_REGULAR_EXPRESSION "GotA")

# --- Скрипт 2 (негативный): input = B ---
add_test(NAME script2_cond_notA
    COMMAND script
        ${CMAKE_CURRENT_SOURCE_DIR}/script2.txt
        ${CMAKE_CURRENT_SOURCE_DIR}/input2b.txt
)
set_property(TEST script2_cond_notA PROPERTY
    PASS_REGULAR_EXPRESSION "NotA")

# --- Скрипт 3: переворот, удаление дна, переменные ---
add_test(NAME script3_reverse_vars
    COMMAND script
        ${CMAKE_CURRENT_SOURCE_DIR}/script3.txt
        ${CMAKE_CURRENT_SOURCE_DIR}/input3.txt
)
set_property(TEST script3_reverse_vars PROPERTY
    PASS_REGULAR_EXPRESSION "AB")

# --- Скрипт 4: все ключевые символы ---
add_test(NAME script4_all_commands
    COMMAND script
        ${CMAKE_CURRENT_SOURCE_DIR}/script4.txt
        ${CMAKE_CURRENT_SOURCE_DIR}/input4.txt
)
set_property(TEST script4_all_commands PROPERTY
    PASS_REGULAR_EXPRESSION "Start:")
