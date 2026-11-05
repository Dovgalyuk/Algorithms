cmake_minimum_required(VERSION 3.15)

add_executable(maze maze.cpp)
target_include_directories(maze PUBLIC ../LibraryCPP)
target_link_libraries(maze LibraryCPP)

set(TESTS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tests)
 
function(maze_ok name expected)
    add_test(NAME ${name} COMMAND maze ${TESTS_DIR}/${name}.txt)
    set_tests_properties(${name} PROPERTIES PASS_REGULAR_EXPRESSION "^${expected}[\r\n]*$")
endfunction()

function(maze_err name message)
    add_test(NAME ${name} COMMAND maze ${TESTS_DIR}/${name}.txt)
    set_tests_properties(${name} PROPERTIES PASS_REGULAR_EXPRESSION "${message}")
endfunction()

add_test(NAME usage COMMAND maze)
set_tests_properties(usage PROPERTIES PASS_REGULAR_EXPRESSION "Usage:")
 
add_test(NAME file_not_found COMMAND maze ${TESTS_DIR}/no_such_file.txt)
set_tests_properties(file_not_found PROPERTIES PASS_REGULAR_EXPRESSION "Error opening file")
 
# Корректные лабиринты
maze_ok(example 4)
maze_ok(tie_reverse 2)            # ничья, на ходу от старта первой находится меньшая цифра
maze_ok(tie_shared_neighbour 2)   # общая соседняя клетка: важна сортировка финишей
maze_ok(tie_odd_distance 3)       # ничья при нечётном расстоянии
maze_ok(digit_zero 0)             # ответ 0 не путается с "нет пути"
maze_ok(larger_nearer 5)          # ближайшая цифра важнее меньшей
maze_ok(wall_trap 3)              # ближайшая по прямой отрезана стеной
maze_ok(serpentine 7)             # длинный извилистый путь
maze_ok(unreachable_ignored 5)    # недостижимая цифра игнорируется
maze_ok(crlf 1)                   # окончания строк \r\n
maze_ok(big_field 8)              # рост кольцевого буфера очереди
maze_ok(tie_three 2)              # ничья трёх цифр, минимальная - в середине
maze_ok(tie_vertical 2)           # ничья по вертикали
maze_ok(tie_adjacent_vertical 2)  # цифры вплотную к старту сверху и снизу
maze_ok(multi_digit_neighbours 1) # две цифры рядом, ближе меньшая
maze_ok(nearer_bigger_digit 7)    # большая цифра ближе, меньшая за ней
maze_ok(no_border 4)              # лабиринт без стен по краям
maze_ok(one_column 3)             # ширина 1
maze_ok(blank_lines_ignored 1)    # пустые строки пропускаются
maze_ok(no_final_newline 5)       # нет перевода строки в конце файла
# Ошибки
maze_err(empty_file "The maze is empty")
maze_err(row_shorter "row 1 has a different length")
maze_err(invalid_char "Invalid character '@'")
maze_err(two_starts "more than one start")
maze_err(no_start "no start position")
maze_err(no_finish "no finish positions")
maze_err(finish_walled "No path found")   
maze_err(no_path "No path found")   