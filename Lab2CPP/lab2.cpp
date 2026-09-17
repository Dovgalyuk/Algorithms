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

// Пропускает блок if до соответствующего |
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

// Читает значение для +, ?, ?! — либо {строка}, либо один символ
string parse_value(const string& code, size_t& ip) {
    string value;
    if (ip < code.size() && code[ip] == '{') {
        ip++;
        while (ip < code.size() && code[ip] != '}') {
            value += code[ip];
            ip++;
        }
    } else if (ip < code.size()) {
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

    Stack stack; // основной стек
    string tilde; // переменная ~
    size_t ip = 0; // указатель на текущий символ скрипта

    // 100 ячеек для переменных интерпретатора, изначально пустые
    string variables[100];

    while (ip < code.size()) {
        char cmd = code[ip];

        // Пробелы и переводы строк игнорируем
        if (cmd == ' ' || cmd == '\t' || cmd == '\n' || cmd == '\r') {
            ip++;
            continue;
        }

        // +value — кладём символ или {строку} на верх стека
        if (cmd == '+') {
            ip++;
            string value = parse_value(code, ip);
            stack.push(value);
        }

        // - — удаляем нижний элемент.
        // Перекладываем в temp - нижний элемент окажется наверху.
        // Убираем его и перекладываем обратно
        else if (cmd == '-') {
            Stack temp;
            while (!stack.empty()){
                temp.push(stack.get());
                stack.pop();
            }
            if (!temp.empty()){
                temp.pop();
            }
            while (!temp.empty()){
                stack.push(temp.get());
                temp.pop();
            }
        }

        // >text — печатаем текст до конца строки или до |
        else if (cmd == '>') {
            ip++;
            string text;
            while (ip < code.size() && code[ip] != '\n' && code[ip] != '|') {
                text += code[ip];
                ip++;
            }
            cout << text;
            if (ip < code.size() && code[ip] == '\n') continue;
        }

        // ~\ — обнуляем ~
        else if (cmd == '~' && ip + 1 < code.size() && code[ip+1] == '\\') {
            tilde = "";
            ip++;
        }

        // ~(number — ~ = значение переменной number
        else if (cmd == '~' && ip + 1 < code.size() && code[ip+1] == '(') {
            ip += 2;
            int idx = parse_number(code, ip);
            if (idx >= 0 && idx < 100) {
                tilde = variables[idx];
            }
        }

        // ~ — берём нижний элемент стека в ~
        // Перекладываем стек в temp, при этом порядок переворачивается.
        // Нижний элемент исходного стека оказывается наверху temp.
        // Читаем его и возвращаем элементы обратно.
        else if (cmd == '~') {
            Stack temp;
            while (!stack.empty()) {
                temp.push(stack.get());
                stack.pop();
            }
            if (!temp.empty()) {
                tilde = temp.get();
            }
            while (!temp.empty()) {
                stack.push(temp.get());
                temp.pop();
            }
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
        //  Перекладываем в temp: там элементы идут в порядке низ -> верх
        else if (cmd == ':') {
            Stack temp;
            while (!stack.empty()) {
                temp.push(stack.get());
                stack.pop();
            }
            string combined;
            while (!temp.empty()) {
                combined += temp.get();
                temp.pop();
            }
            stack = Stack();
            stack.push(combined);
        }

        // !number — прыжок на позицию number в коде
        else if (cmd == '!') {
            ip++;
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
            string value = parse_value(code, ip);
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

        // = — создаём переменную со значением ~ (первая свободная)
        else if (cmd == '=') {
            for (int i = 0; i < 100; i++) {
                if (variables[i] == "") {
                    variables[i] = tilde;
                    break;
                }
            }
        }

        // @number — ~ = значение переменной number
        else if (cmd == '@') {
            ip++;
            int idx = parse_number(code, ip);
            if (idx >= 0 && idx < 100) {
                tilde = variables[idx];
            }
        }

        // &op — арифметика на двух нижних элементах стека
        // Перекладываем в temp: два верхних temp - это два нижних исходного
        else if (cmd == '&') {
            ip++;
            if(ip < code.size()) {
                char op = code[ip];
                Stack temp;
                while (!stack.empty()) {
                    temp.push(stack.get());
                    stack.pop();
                }
                if (temp.size() >= 2) {
                    int x = stoi(temp.get());
                    temp.pop();
                    int y = stoi(temp.get());
                    temp.pop();

                    int result = 0;
                    if (op == '+') result = x + y;
                    else if (op == '-') result = x - y;
                    else if (op == '*') result = x * y;
                    else if (op == '/') result = (y != 0) ? x / y : 0;
                    else if (op == '%') result = (y != 0) ? x % y : 0;

                    // Кладем результат вниз, остаток - сверху
                    Stack back;
                    back.push(to_string(result));
                    while (!temp.empty()) {
                        back.push(temp.get());
                        temp.pop();
                    }
                    // Разворачиваем обратно в основной стек
                    stack = back;
                } else {
                    // НЕ хватило элементов - вернуть как было
                    while (!temp.empty()) {
                        stack.push(temp.get());
                        temp.pop();
                    }
                }
            }
        }

        // # — останавливаем программу
        else if (cmd == '#') {
            break;
        }

        // _ — читаем строку из файла данных, кладём в низ стека
        // Перекладываем в temp, кладем input в пустой stack, возвращаем всё обратно
        else if (cmd == '_') {
            string input;
            while (data_pos < data.size() && data[data_pos] != '\n') {
                input += data[data_pos];
                data_pos++;
            }
            if (data_pos < data.size()) data_pos++;

            Stack temp;
            while (!stack.empty()) {
                temp.push(stack.get());
                stack.pop();
            }
            stack = Stack();
            stack.push(input);
            while (!temp.empty()) {
                stack.push(temp.get());
                temp.pop();
            }
        }

        // $number — кладём случайное число от 1 до number
        else if (cmd == '$') {
            ip++;
            int n = parse_number(code, ip);
            if (n > 0) {
                int r = rand() % n + 1;
                stack.push(to_string(r));
            }
        }

        // ^ — очистка экрана
        else if (cmd == '^') {
            cout << "\033[2J\033[1;1H";
        }

        // ;seconds — пауза на seconds секунд
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

    // Состояние стека после скрипта: печатаем снизу вверх
    // Перекладываем в temp: там элементы в нужном порядке
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
