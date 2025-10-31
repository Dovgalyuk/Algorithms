add_executable(Lab2CPP main.cpp)
target_include_directories(Lab2CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab2CPP LibraryCPP)

# === ТЕСТЫ ===
# 1) Тест из условия: 1+2*3 (читаем из файла)
add_test(NAME Lab2_File_1plus2mul3
         COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt)
set_tests_properties(Lab2_File_1plus2mul3 PROPERTIES
  PASS_REGULAR_EXPRESSION
"PUSH 1
PUSH 2
PUSH 3
POP A
POP B
MUL A, B
PUSH A
POP A
POP B
ADD A, B
PUSH A"
)

# 2) Тест из условия: (1+2)*3 (как аргумент)
add_test(NAME Lab2_Paren
         COMMAND Lab2CPP "(1+2)*3")
set_tests_properties(Lab2_Paren PROPERTIES
  PASS_REGULAR_EXPRESSION
"PUSH 1
PUSH 2
POP A
POP B
ADD A, B
PUSH A
PUSH 3
POP A
POP B
MUL A, B
PUSH A"
)

# 3) Собственный: 10*(2+3)-4
add_test(NAME Lab2_Custom1
         COMMAND Lab2CPP "10*(2+3)-4")
set_tests_properties(Lab2_Custom1 PROPERTIES
  PASS_REGULAR_EXPRESSION
"PUSH 10
PUSH 2
PUSH 3
POP A
POP B
ADD A, B
PUSH A
POP A
POP B
MUL A, B
PUSH A
PUSH 4
POP A
POP B
SUB A, B
PUSH A"
)

# 4) Собственный со пробелами:  ( 7 + 8 ) * 2
add_test(NAME Lab2_Custom2_Spaces
         COMMAND Lab2CPP " ( 7 + 8 ) * 2 ")
set_tests_properties(Lab2_Custom2_Spaces PROPERTIES
  PASS_REGULAR_EXPRESSION
"PUSH 7
PUSH 8
POP A
POP B
ADD A, B
PUSH A
PUSH 2
POP A
POP B
MUL A, B
PUSH A"
)
