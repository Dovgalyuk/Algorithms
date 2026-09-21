#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>

#include "stack.h"

static Stack* st = nullptr;
static std::string tilde;
static std::vector<std::string> vars;
static std::string input_data;
static size_t input_pos = 0;
static std::string code;
static size_t ip = 0;
static bool running = true;


static void reverse_stack()
{
    Stack* a = stack_create();
    Stack* b = stack_create();

    while (!stack_empty(st))
    {
        stack_push(a, stack_get(st));
        stack_pop(st);
    }
    while (!stack_empty(a))
    {
        stack_push(b, stack_get(a));
        stack_pop(a);
    }
    while (!stack_empty(b))
    {
        stack_push(st, stack_get(b));
        stack_pop(b);
    }

    stack_delete(a);
    stack_delete(b);
}

static void skip_ws()
{
    while (ip < code.size() &&
           std::isspace(static_cast<unsigned char>(code[ip])))
    {
        ip++;
    }
}

static std::string read_braced()
{
    std::string s;
    if (ip >= code.size() || code[ip] != '{') return s;
    ip++;
    while (ip < code.size() && code[ip] != '}')
    {
        s += code[ip++];
    }
    if (ip < code.size() && code[ip] == '}') ip++;
    return s;
}

static int read_number()
{
    std::string n;
    while (ip < code.size() &&
           std::isdigit(static_cast<unsigned char>(code[ip])))
    {
        n += code[ip++];
    }
    return n.empty() ? 0 : std::stoi(n);
}

static void push_string(const std::string& s)
{
    for (int i = static_cast<int>(s.size()) - 1; i >= 0; i--)
    {
        stack_push(st, s[i]);
    }
}


static void execute_one();

static void execute_until_pipe()
{
    int depth = 0;
    while (ip < code.size())
    {
        char c = code[ip];

        if (c == '|' && depth == 0) { ip++; return; }
        if (c == '?') { depth++; ip++; continue; }
        if (c == '|') { depth--; ip++; continue; }

        execute_one();
        if (!running) return;
    }
}

static void execute_one()
{
    skip_ws();
    if (ip >= code.size()) return;

    char cmd = code[ip++];

    switch (cmd)
    {
        // + — положить символ или строку на верх
        case '+':
        {
            skip_ws();
            if (ip < code.size() && code[ip] == '{')
            {
                push_string(read_braced());
            }
            else if (ip < code.size())
            {
                stack_push(st, code[ip++]);
            }
            break;
        }

        // - — удалить нижний элемент
        case '-':
        {
            if (stack_empty(st)) break;
            reverse_stack();
            stack_pop(st);
            reverse_stack();
            break;
        }

        // > — вывести весь стек и очистить его
        case '>':
        {
            skip_ws();
            if (ip < code.size() && code[ip] == '{')
            {
                std::cout << read_braced();
            }
            else
            {
                while (!stack_empty(st))
                {
                    std::cout << stack_get(st);
                    stack_pop(st);
                }
            }
            break;
        }

        // ~ — взять нижний в tilde и удалить его; ~| — очистить tilde
        case '~':
        {
            if (ip < code.size() && code[ip] == '|')
            {
                ip++;
                tilde.clear();
            }
            else if (!stack_empty(st))
            {
                reverse_stack();
                tilde = std::string(1, stack_get(st));
                stack_pop(st);
                reverse_stack();
            }
            break;
        }

        // < — перевернуть стек
        case '<':
        {
            reverse_stack();
            break;
        }

        // : — склеить стек в строку (сверху вниз) и положить обратно
        case ':':
        {
            std::string s;
            while (!stack_empty(st))
            {
                s += stack_get(st);
                stack_pop(st);
            }
            push_string(s);
            break;
        }

        // ! — безусловный переход
        case '!':
        {
            skip_ws();
            ip = static_cast<size_t>(read_number());
            break;
        }

        // ? — if tilde == value; ?! — if tilde != value
        case '?':
        {
            bool negate = false;
            if (ip < code.size() && code[ip] == '!')
            {
                negate = true;
                ip++;
            }
            skip_ws();
            std::string val;
            if (ip < code.size() && code[ip] == '{')
            {
                val = read_braced();
            }
            else if (ip < code.size())
            {
                val = std::string(1, code[ip++]);
            }

            bool cond = (tilde == val);
            if (negate) cond = !cond;

            if (cond)
            {
                execute_until_pipe();
            }
            else
            {
                int depth = 0;
                while (ip < code.size())
                {
                    if (code[ip] == '?') 
                    { 
                        depth++; 
                        ip++; 
                        continue; 
                    }

                    if (code[ip] == '|')
                    {
                        if (depth == 0) 
                        { 
                            ip++;
                            break; 
                        }
                        depth--;
                    }
                    ip++;
                }
            }
            break;
        }

        // | — конец ветки, вне if игнорируется
        case '|':
            break;

        // = — создать переменную; =(N) — заменить; =)N — удалить
        case '=':
        {
            if (ip < code.size() && code[ip] == '(')
            {
                ip++;
                skip_ws();
                int idx = read_number();
                if (idx >= 0 && idx < static_cast<int>(vars.size()))
                {
                    vars[idx] = tilde;
                }
            }
            else if (ip < code.size() && code[ip] == ')')
            {
                ip++;
                skip_ws();
                int idx = read_number();
                if (idx >= 0 && idx < static_cast<int>(vars.size()))
                {
                    vars[idx].clear();
                }
            }
            else
            {
                vars.push_back(tilde);
            }
            break;
        }

        // @N — вернуть значение переменной N
        case '@':
        {
            skip_ws();
            int idx = read_number();
            if (idx >= 0 && idx < static_cast<int>(vars.size()))
            {
                push_string(vars[idx]);
            }
            break;
        }

        // { — строка вне контекста
        case '{':
        {
            ip--;
            read_braced();
            break;
        }

        // & op — арифметика над двумя верхними
        case '&':
        {
            skip_ws();
            if (ip >= code.size()) break;
            char op = code[ip++];
            if (stack_empty(st)) break;
            char b = stack_get(st); stack_pop(st);
            if (stack_empty(st)) { stack_push(st, b); break; }
            char a = stack_get(st); stack_pop(st);

            char result = 0;
            switch (op)
            {
                case '+': result = static_cast<char>(a + b); break;
                case '-': result = static_cast<char>(a - b); break;
                case '*': result = static_cast<char>(a * b); break;
                case '/': if (b != 0) result = static_cast<char>(a / b); break;
                case '%': if (b != 0) result = static_cast<char>(a % b); break;
            }
            stack_push(st, result);
            break;
        }

        // # — остановка
        case '#':
            running = false;
            break;

        // _ — прочитать один символ input и положить на верх
        case '_':
        {
            if (input_pos < input_data.size())
            {
                stack_push(st, input_data[input_pos++]);
            }
            break;
        }

        default:
            break;
    }
}

static void run()
{
    while (running && ip < code.size())
    {
        execute_one();
    }
}


static void print_stack()
{
    std::cout << "\n=== Stack state (top to bottom) ===\n";

    Stack* tmp = stack_create();
    while (!stack_empty(st))
    {
        stack_push(tmp, stack_get(st));
        stack_pop(st);
    }
    while (!stack_empty(tmp))
    {
        char c = stack_get(tmp);
        if (c == '\n')      std::cout << "\\n";
        else if (c == '\r') std::cout << "\\r";
        else if (c == '\t') std::cout << "\\t";
        else                std::cout << c;

        stack_push(st, c);
        stack_pop(tmp);
    }
    std::cout << "\n";
    stack_delete(tmp);
}


int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        std::cerr << "USAGE: \"./script <SCRIPT_FILE> <INPUT_FILE>\"\n" << std::endl;
        return 1;
    }

    std::ifstream script(argv[1]);
    if (!script)
    {
        std::cerr << "Cannot open script: " << argv[1] << "\n";
        return 1;
    }
    char c;
    while (script.get(c))
    {
        code += c;
    }

    std::ifstream input(argv[2]);
        if (!input)
        {
            std::cerr << "Cannot open input: " << argv[2] << "\n";
            return 1;
        }
        while (input.get(c))
        {
        input_data += c;
        }


    while (!input_data.empty() && (input_data.back() == '\n' || input_data.back() == '\r'))
    {
        input_data.pop_back();
    }

    st = stack_create();
    run();
    print_stack();
    stack_delete(st);

    return 0;
}
