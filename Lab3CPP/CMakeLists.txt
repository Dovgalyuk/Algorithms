
add_executable(Lab3CPP main.cpp)

target_include_directories(Lab3CPP PRIVATE ../LibraryCPP)
target_link_libraries(Lab3CPP PRIVATE LibraryCPP)

enable_testing()

# Пример из условия
add_test(
    NAME test_example
    COMMAND Lab3CPP "${CMAKE_CURRENT_SOURCE_DIR}/input1.txt"
)
string(JOIN "\n" expected_example
    "0.######"
    "..#2...."
    ".1#....."
    "..#.###."
    "..#....."
    ".....###"
    ".#####.."
    "##......"
)
string(REPLACE "." "[.]" expected_example "${expected_example}")
string(REPLACE "\n" "\r?\n" expected_example "${expected_example}")
set_property(
    TEST test_example
    PROPERTY PASS_REGULAR_EXPRESSION
    "^${expected_example}(\r?\n)?$"
)

# Путь с препятствиями
add_test(
    NAME test_path
    COMMAND Lab3CPP "${CMAKE_CURRENT_SOURCE_DIR}/input2.txt"
)
string(JOIN "\n" expected_path
    "0......."
    "..#....."
    ".1......"
    "...#...."
    "..2.#..."
    "......5."
    "...3.#.."
    ".....4.6"
)
string(REPLACE "." "[.]" expected_path "${expected_path}")
string(REPLACE "\n" "\r?\n" expected_path "${expected_path}")
set_property(
    TEST test_path
    PROPERTY PASS_REGULAR_EXPRESSION
    "^${expected_path}(\r?\n)?$"
)

# Случай, когда пути нет
add_test(
    NAME test_no_path
    COMMAND Lab3CPP "${CMAKE_CURRENT_SOURCE_DIR}/input3.txt"
)
string(JOIN "\n" expected_no_path
    "E......."
    "..#....."
    ".#......"
    "........"
    "........"
    "........"
    "........"
    ".......K"
)
string(REPLACE "." "[.]" expected_no_path "${expected_no_path}")
string(REPLACE "\n" "\r?\n" expected_no_path "${expected_no_path}")
set_property(
    TEST test_no_path
    PROPERTY PASS_REGULAR_EXPRESSION
    "^${expected_no_path}(\r?\n)?$"
)
