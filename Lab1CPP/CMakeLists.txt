cmake_minimum_required(VERSION 3.10)
project(Lab1CPP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

add_executable(Lab1CPP main.cpp)
target_include_directories(Lab1CPP PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ../LibraryCPPClass
)
target_link_libraries(Lab1CPP LibraryCPPClass)

# --- Тест 1 (input1.txt) ---
# Матчим ОДНУ строку. Разрешаем любые пробелы. Не требуем \n в конце.
add_test(NAME TestLab1CPP_Input1
    COMMAND Lab1CPP ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt
)
set_tests_properties(TestLab1CPP_Input1 PROPERTIES
    PASS_REGULAR_EXPRESSION
    "Indices of elements greater than total sum \\([-+]?[0-9]+\\):[ \\t]*None[ \\t]+Unique elements:[ \\t]*2[ \\t]+3[ \\t]+20"
)

# --- Тест 2 (input2.txt) ---
add_test(NAME TestLab1CPP_Input2
    COMMAND Lab1CPP ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt
)
set_tests_properties(TestLab1CPP_Input2 PROPERTIES
    PASS_REGULAR_EXPRESSION
    "Indices of elements greater than total sum \\([-+]?[0-9]+\\):[ \\t]*None[ \\t]+Unique elements:[ \\t]*8[ \\t]+9"
)
