#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <thread>
#include <chrono>
#include "stack.h"
#include "vector.h"
using namespace std;

// Читаем весь файл в строку
string read_file(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) return "";
    return string((istreambuf_iterator<char>(file)),
                  istreambuf_iterator<char>());
}

// Возвращает содержимое стека как Vector в порядке [низ ... верх].
// Стек после вызова остаётся в исходном состоянии.
Vector stack_to_vec(Stack& s) {
    Vector v;
    while (!s.empty()) {
        v.push_back(s.get());
        s.pop();
    }
    v.reverse();
    for (size_t i = 0; i < v.size(); i++) {
        s.push(v.get(i));
    }
    return v;
}

// Заполняет стек элементами вектора в порядке низ -> верх
void vec_to_stack(const Vector& v, Stack& s) {
    s = Stack();
    for (size_t i = 0; i < v.size(); i++) {
        s.push(v.get(i));
    }
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
    Vector variables;
    for (int i = 0; i < 100; i++) {
        variables.push_back("");
    }

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

        // - — удаляем нижний элемент. Через Vector: пропускаем первый
        else if (cmd == '-') {
            Vector v = stack_to_vec(stack);
            if (v.size() > 0) {
                Vector temp;
                for (size_t i = 1; i < v.size(); i++) {
                    temp.push_back(v.get(i));
                }
                vec_to_stack(temp, stack);
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
            if (idx >= 0 && idx < (int)variables.size()) {
                tilde = variables.get(idx);
            }
        }

        // ~ — берём нижний элемент стека в ~
        else if (cmd == '~') {
            Vector v = stack_to_vec(stack);
            if (v.size() > 0) tilde = v.get(0);
        }

        // < — разворачиваем стек
        else if (cmd == '<') {
            Vector v = stack_to_vec(stack);
            v.reverse();
            vec_to_stack(v, stack);
        }

        // : — склеиваем весь стек в одну строку
        else if (cmd == ':') {
            Vector v = stack_to_vec(stack);
            string combined;
            for (size_t i = 0; i < v.size(); i++) {
                combined += v.get(i);
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
            if (idx >= 0 && idx < (int)variables.size()) {
                variables.set(idx, tilde);
            }
        }

        // =)number — удаляем переменную number
        else if (cmd == '=' && ip + 1 < code.size() && code[ip+1] == ')') {
            ip += 2;
            int idx = parse_number(code, ip);
            if (idx >= 0 && idx < (int)variables.size()) {
                variables.set(idx, "");
            }
        }

        // = — создаём переменную со значением ~ (первая свободная)
        else if (cmd == '=') {
            for (size_t i = 0; i < variables.size(); i++) {
                if (variables.get(i) == "") {
                    variables.set(i, tilde);
                    break;
                }
            }
        }

        // @number — ~ = значение переменной number
        else if (cmd == '@') {
            ip++;
            int idx = parse_number(code, ip);
            if (idx >= 0 && idx < (int)variables.size()) {
                tilde = variables.get(idx);
            }
        }

        // &op — арифметика на двух нижних элементах стека
        else if (cmd == '&') {
            ip++;
            if (ip < code.size()) {
                char op = code[ip];
                Vector v = stack_to_vec(stack);
                if (v.size() >= 2) {
                    int x = stoi(v.get(0));
                    int y = stoi(v.get(1));
                    int result = 0;
                    if      (op == '+') result = x + y;
                    else if (op == '-') result = x - y;
                    else if (op == '*') result = x * y;
                    else if (op == '/') result = (y != 0) ? x / y : 0;
                    else if (op == '%') result = (y != 0) ? x % y : 0;

                    // результат + оставшиеся элементы
                    Vector temp;
                    temp.push_back(to_string(result));
                    for (size_t i = 2; i < v.size(); i++) {
                        temp.push_back(v.get(i));
                    }
                    vec_to_stack(temp, stack);
                }
            }
        }

        // # — останавливаем программу
        else if (cmd == '#') {
            break;
        }

        // _ — читаем строку из файла данных, кладём в низ стека
        else if (cmd == '_') {
            string input;
            // читаем до конца строки или конца файла
            while (data_pos < data.size() && data[data_pos] != '\n') {
                input += data[data_pos];
                data_pos++;
            }
            if (data_pos < data.size()) data_pos++;   // пропустить \n

            Vector v = stack_to_vec(stack);
            Vector temp;
            temp.push_back(input);
            for (size_t i = 0; i < v.size(); i++) {
                temp.push_back(v.get(i));
            }
            vec_to_stack(temp, stack);
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
    Vector v = stack_to_vec(stack);
    for (size_t i = 0; i < v.size(); i++) {
        cout << v.get(i) << "\n";
    }

    return 0;
}
