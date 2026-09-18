#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <thread>
#include <chrono>
#include "stack.h"
using namespace std;

// Читаем весь файл в строку
string read_file(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) return "";
    return string((istreambuf_iterator<char>(file)),
                  istreambuf_iterator<char>());
}

// Пропускает блок if от позиции ip до соответствующего | (с учётом вложенности)
size_t skip_if_block(const string& code, size_t ip) {
    int depth = 0;
    while (ip < code.size()) {
        if (code[ip] == '?') depth++;
        else if (code[ip] == '|') {
            if (depth == 0) return ip;
            depth--;
        }
        ip++;
    }
    return ip;
}

// Читает число с позиции ip.
// После возврата ip стоит на последней цифре (основной цикл сделает ip++)
int parse_number(const string& code, size_t& ip) {
    string num_str;
    while (ip < code.size() && isdigit(code[ip])) {
        num_str += code[ip];
        ip++;
    }
    ip--;
    return num_str.empty() ? 0 : stoi(num_str);
}

// Читает значение для +, >, ?, ?! — {строка}, @номер или один символ
string parse_value(const string& code, size_t& ip, const string variables[]) {
    string value;
    if (ip < code.size() && code[ip] == '{') {
        // Строковый литерал в фигурных скобках
        ip++;
        while (ip < code.size() && code[ip] != '}') {
            value += code[ip];
            ip++;
        }
    } else if (ip < code.size() && code[ip] == '@') {
        // Ссылка на переменную: @номер
        ip++;
        int idx = parse_number(code, ip);
        if (idx >= 0 && idx < 100) value = variables[idx];
    } else if (ip < code.size()) {
        // Одиночный символ
        value = string(1, code[ip]);
    }
    return value;
}


int main(int argc, char **argv) {
    if (argc < 3) {
        cerr << "Использование: " << argv[0] << " <скрипт> <данные>\n";
        return 1;
    }

    string code = read_file(argv[1]);
    if (code.empty()) {
        cerr << "Ошибка чтения скрипта\n";
        return 1;
    }

    // Второй файл — входные данные для команды _
    string data = read_file(argv[2]);
    size_t data_pos = 0;

    // Фиксируем seed, чтобы rand() в команде $ давал
    // одно и то же число при каждом запуске —
    // для детерминированного теста Guessing Game
    srand(36);
    Stack stack; // основной стек
    string tilde; // регистр ~ (переменная для временного хранения)
    size_t ip = 0; // указатель на текущий символ скрипта

    // 100 ячеек для переменных интерпретатора (используются 1..99)
    string variables[100];

    while (ip < code.size()) {
        char cmd = code[ip];

        // Пробелы и переводы строк игнорируем
        if (cmd == ' ' || cmd == '\t' || cmd == '\n' || cmd == '\r') {
            ip++;
            continue;
        }

        // +value — кладём символ, {строку} или @переменную на верх стека
        if (cmd == '+') {
            ip++;
            string value = parse_value(code, ip, variables);
            stack.push(value);
        }

        // - — удаляем нижний элемент стека
        else if (cmd == '-') {
            if (!stack.empty()) stack.remove_bottom();
        }

        // >text — выводим текст в консоль.
        // Если аргумент ~, печатаем значение регистра tilde
        else if (cmd == '>') {
            ip++;
            string text = parse_value(code, ip, variables);
            if (text == "~") {
                cout << tilde;
            } else {
                cout << text;
            }
        }

        // ~\ — обнуляем регистр ~
        else if (cmd == '~' && ip + 1 < code.size() && code[ip+1] == '\\') {
            tilde = "";
            ip++;
        }

        // ~(number — записываем в ~ значение переменной с указанным номером
        else if (cmd == '~' && ip + 1 < code.size() && code[ip+1] == '(') {
            ip += 2;
            int idx = parse_number(code, ip);
            if (idx >= 0 && idx < 100) {
                tilde = variables[idx];
            }
        }

        // ~ — копируем нижний элемент стека в регистр ~
        else if (cmd == '~') {
            if (!stack.empty()) tilde = stack.bottom();
        }

        // < — разворачиваем стек
        // Перекладываем в temp, он получится развернутым
        else if (cmd == '<') {
            Stack temp;
            while (!stack.empty()) {
                temp.push(stack.get());
                stack.pop();
            }
            stack = temp;
        }

        // : — склеиваем весь стек в одну строку
        else if (cmd == ':') {
            string combined = stack.join_to_string();
            stack = Stack();
            stack.push(combined);
        }

        // !number — безусловный прыжок на позицию number в коде
        // Если number в фигурных скобках {!N}, пропускаем скобку
        else if (cmd == '!') {
            ip++;
            if (ip < code.size() && code[ip] == '{') ip++;
            int target = parse_number(code, ip);
            ip = (size_t)target;
            continue;
        }

        // ?value — если ~ == value, выполняем блок до |, иначе прыгаем за него
        // ?!value — то же, но если ~ != value
        else if (cmd == '?') {
            ip++;
            bool negate = false;
            if (ip < code.size() && code[ip] == '!') {
                negate = true;
                ip++;
            }
            string value = parse_value(code, ip, variables);
            bool cond = (tilde == value);
            if (negate) cond = !cond;
            if (!cond) ip = skip_if_block(code, ip);
        }

        // | — конец блока if, тут ничего делать не нужно
        else if (cmd == '|') {
            // пусто
        }

        // =(number — записываем ~ в переменную number
        else if (cmd == '=' && ip + 1 < code.size() && code[ip+1] == '(') {
            ip += 2;
            int idx = parse_number(code, ip);
            if (idx >= 0 && idx < 100) {
                variables[idx] = tilde;
            }
        }

        // =)number — удаляем переменную number
        else if (cmd == '=' && ip + 1 < code.size() && code[ip+1] == ')') {
            ip += 2;
            int idx = parse_number(code, ip);
            if (idx >= 0 && idx < 100) {
                variables[idx] = "";
            }
        }

        // = — создаём переменную со значением ~ (первая свободная, начиная с 1)
        else if (cmd == '=') {
            for (int i = 1; i < 100; i++) {
                if (variables[i] == "") {
                    variables[i] = tilde;
                    break;
                }
            }
        }

        // @number — ~ = значение переменной с указанным номером
        else if (cmd == '@') {
            ip++;
            int idx = parse_number(code, ip);
            if (idx >= 0 && idx < 100) {
                tilde = variables[idx];
            }
        }

        // &op — арифметика на двух нижних элементах стека
        // op — оператор: символ или @номер_переменной.
        // Берём два нижних элемента, вычисляем, результат кладём в низ стека.
        else if (cmd == '&') {
            ip++;
            if (ip < code.size() && stack.size() >= 2) {
                char op;
                if (code[ip] == '@') {
                    // Оператор берётся из значения переменной
                    ip++;
                    int idx = parse_number(code, ip);
                    if (idx >= 0 && idx < 100 && !variables[idx].empty())
                        op = variables[idx][0];
                    else
                        op = '+';
                } else {
                    op = code[ip];
                }


                // Берём два нижних элемента: сначала первый, потом второй.
                int x = 0, y = 0;
                try { x = stoi(stack.bottom()); } catch (...) {}
                stack.remove_bottom();
                try { y = stoi(stack.bottom()); } catch (...) {}
                stack.remove_bottom();

                int result = 0;
                if      (op == '+') result = x + y;
                else if (op == '-') result = x - y;
                else if (op == '*') result = x * y;
                else if (op == '/') result = (y != 0) ? x / y : 0;
                else if (op == '%') result = (y != 0) ? x % y : 0;

                // Результат кладём в низ стека
                stack.push_bottom(to_string(result));
            }
        }

        // # — останавливаем программу
        else if (cmd == '#') {
            break;
        }

        // _ — читаем строку из файла данных до \n, кладём в низ стека
        else if (cmd == '_') {
            string input;
            while (data_pos < data.size() && data[data_pos] != '\n') {
                input += data[data_pos];
                data_pos++;
            }
            if (data_pos < data.size()) data_pos++;
            stack.push_bottom(input);
        }


        // $number — кладём случайное число от 1 до number на вершину стека
        // Если number в фигурных скобках ${N}, пропускаем скобку
        else if (cmd == '$') {
            ip++;
            if (ip < code.size() && code[ip] == '{') ip++;
            int n = parse_number(code, ip);
            if (n > 0) {
                int r = rand() % n + 1;
                stack.push(to_string(r));
            }
        }

        // ^ — очистка экрана (ANSI-коды)
        else if (cmd == '^') {
            cout << "\033[2J\033[1;1H";
        }

        // ;seconds — пауза на указанное число секунд
        else if (cmd == ';') {
            ip++;
            int sec = parse_number(code, ip);
            this_thread::sleep_for(chrono::seconds(sec));
        }

        // { — строковый литерал вне контекста, просто пропускаем до }
        else if (cmd == '{') {
            ip++;
            while (ip < code.size() && code[ip] != '}') ip++;
        }

        ip++;
    }

    // Выводим содержимое стека снизу вверх
    Stack temp;
    while (!stack.empty()) {
        temp.push(stack.get());
        stack.pop();
    }
    while (!temp.empty()) {
        cout << temp.get() << '\n';
        temp.pop();
    }

    return 0;
}
