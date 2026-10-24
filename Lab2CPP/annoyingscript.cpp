#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <random>

#include "stack.h"

static Stack* st = nullptr;
static std::string tilde;
static std::string vars[100];
static std::string input_data;
static size_t input_pos = 0;
static std::string code;
static size_t ip = 0;
static bool running = true;
static std::mt19937 gen(42);


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
    skip_ws();
    int sign = 1;
    if (ip < code.size() && code[ip] == '-')
    {
        sign = -1;
        ip++;
    }
    std::string n;
    while (ip < code.size() &&
           std::isdigit(static_cast<unsigned char>(code[ip])))
    {
        n += code[ip++];
    }
    if (n.empty()) return 0;
    int val = 0;
    for (size_t i = 0; i < n.size(); ++i)
    {
        val = val * 10 + (n[i] - '0');
    }
    return sign * val;
}

static void push_string(const std::string& s)
{
    for (int i = static_cast<int>(s.size()) - 1; i >= 0; --i)
    {
        stack_push(st, s[i]);
    }
}

static std::string pop_top_string()
{
    if (stack_empty(st)) return "";
    char c = stack_get(st);
    stack_pop(st);
    return std::string(1, c);
}

static std::string combine_stack()
{
    if (stack_empty(st)) return "";

    std::string result;
    while (!stack_empty(st))
    {
        char c = stack_get(st);
        result += c;
        stack_pop(st);
    }
    
    return result;
}


static std::string read_value_arg()
{
    skip_ws();
    if (ip >= code.size()) return "";

    if (code[ip] == '{') return read_braced();

    if (code[ip] == '~')
    {
        ip++;
        return tilde;
    }

    if (code[ip] == '@')
    {
        ip++;
        skip_ws();
        int idx = read_number();
        if (idx >= 0 && idx < 100) return vars[idx];
        return "";
    }

    char c = code[ip++];
    return std::string(1, c);
}

static void execute_one();

static void execute_until_pipe()
{
    int depth = 0;
    while (ip < code.size() && running)
    {
        char c = code[ip];
        if (c == '|' && depth == 0) { ip++; return; }
        if (c == '?') { depth++; ip++; continue; }
        if (c == '|') { depth--; ip++; continue; }
        execute_one();
    }
}

static void skip_until_pipe()
{
    int depth = 0;
    while (ip < code.size())
    {
        char c = code[ip];
        if (c == '?') { depth++; ip++; continue; }
        if (c == '|')
        {
            if (depth == 0) { ip++; return; }
            depth--;
        }
        ip++;
    }
}



static void execute_one()
{
    skip_ws();
    if (ip >= code.size() || !running) return;

    char cmd = code[ip++];

    switch (cmd)
    {
        case '+':
        {
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
        case '-':
        {
            if (!stack_empty(st)) stack_pop(st);
            break;
        }
        case '>':
        {
            if (ip < code.size() && code[ip] == '{')
            {
                std::cout << read_braced();
            }
            else
            {
                std::string val = read_value_arg();
                std::cout << val;
            }
            std::cout.flush();
            break;
        }
        case '~':
        {
            if (ip < code.size() && code[ip] == '\\')
            {
                ip++;
                tilde.clear();
            }
            else if (ip < code.size() && code[ip] == '(')
            {
                ip++;
                skip_ws();
                int idx = read_number();
                if (idx >= 0 && idx < 100) tilde = vars[idx];
                else                        tilde.clear();
            }
            else
            {
                tilde = combine_stack();
            }
            break;
        }
        case '<':
        {
            Stack* tmp = stack_create();
            while (!stack_empty(st))
            {
                stack_push(tmp, stack_get(st));
                stack_pop(st);
            }
            stack_delete(st);
            st = tmp;
            tmp = nullptr;
            break;
        }
        case ':':
        {
            std::string combined = combine_stack();
            push_string(combined);
            break;
        }
        case '!':
        {
            int target = read_number();
            if (target >= 1 && target <= static_cast<int>(code.size()))
            {
                ip = static_cast<size_t>(target - 1);
            }
            break;
        }
        case '?':
        {
            bool negate = false;
            if (ip < code.size() && code[ip] == '!')
            {
                negate = true;
                ip++;
            }
            std::string val = read_value_arg();
            bool cond = (tilde == val);
            if (negate) cond = !cond;

            if (cond) execute_until_pipe();
            else      skip_until_pipe();
            break;
        }

        case '|':
            break;
        case '=':
        {
            if (ip < code.size() && code[ip] == '(')
            {
                ip++;
                skip_ws();
                int idx = read_number();
                if (idx >= 0 && idx < 100) vars[idx] = tilde;
            }
            else if (ip < code.size() && code[ip] == ')')
            {
                ip++;
                skip_ws();
                int idx = read_number();
                if (idx >= 0 && idx < 100) vars[idx].clear();
            }
            else
            {
                for (int i = 1; i < 100; ++i)
                {
                    if (vars[i].empty())
                    {
                        vars[i] = tilde;
                        break;
                    }
                }
            }
            break;
        }
        case '@':
        {
            skip_ws();
            int idx = read_number();
            if (idx >= 0 && idx < 100)
            {
                push_string(vars[idx]);
            }
            if (ip < code.size() && code[ip] == '+' &&
                ip + 1 < code.size() && code[ip + 1] == '@')
            {
                ip++;
            }
            break;
        }
        case '{':
        {
            ip--;
            read_braced();
            break;
        }
        case '&':
        {
            skip_ws();
            std::string op_str;
            if (ip < code.size() && code[ip] == '@')
            {
                ip++;
                skip_ws();
                int idx = read_number();
                if (idx >= 0 && idx < 100) op_str = vars[idx];
            }
            else if (ip < code.size())
            {
                op_str = std::string(1, code[ip++]);
            }

            if (op_str.empty()) break;
            if (stack_empty(st)) break;

            std::string b_str = pop_top_string();
            if (stack_empty(st))
            {
                push_string(b_str);
                break;
            }
            std::string a_str = pop_top_string();

            long long a = a_str.empty() ? 0 : (a_str[0] - '0');
            long long b = b_str.empty() ? 0 : (b_str[0] - '0');
            long long result = 0;

            char op = op_str[0];
            if      (op == '+') result = a + b;
            else if (op == '-') result = a - b;
            else if (op == '*') result = a * b;
            else if (op == '/') result = (b != 0) ? (a / b) : 0;
            else if (op == '%') result = (b != 0) ? (a % b) : 0;

            std::string res_str;
            if (result == 0) res_str = "0";
            else
            {
                bool neg = (result < 0);
                if (neg) result = -result;
                while (result > 0)
                {
                    res_str = std::string(1, char('0' + result % 10)) + res_str;
                    result /= 10;
                }
                if (neg) res_str = "-" + res_str;
            }
            push_string(res_str);
            break;
        }
        case '#':
        {
            running = false;
            break;
        }
        case '_':
        {
            if (input_pos >= input_data.size()) break;

            std::string line;
            while (input_pos < input_data.size() &&
                   input_data[input_pos] != '\n')
            {
                line += input_data[input_pos++];
            }
            if (input_pos < input_data.size() &&
                input_data[input_pos] == '\n')
            {
                input_pos++;
            }
            if (!line.empty() && line[line.size() - 1] == '\r')
            {
                line.erase(line.size() - 1);
            }

            push_string(line);
            break;
        }
        case '$':
        {
            int max_num = read_number();
            if (max_num < 1) max_num = 1;

            std::uniform_int_distribution<int> dist(1, max_num);
            int r = dist(gen);

            std::string res_str;
            int v = r;
            if (v == 0) res_str = "0";
            else
            {
                if (v < 0) { res_str = "-"; v = -v; }
                std::string tmp;
                while (v > 0)
                {
                    tmp = std::string(1, char('0' + v % 10)) + tmp;
                    v /= 10;
                }
                res_str += tmp;
            }
            push_string(res_str);
            break;
        }
        case '^':
        {
            break;
        }
        case ';':
        {
            int sec = read_number();
            (void)sec;
            break;
        }

        default:
            break;
    }
}

// ============================================================
//  Запуск и вывод состояния стека
// ============================================================

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

// ============================================================
//  main
// ============================================================

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        std::cerr << "USAGE: \"" << argv[0]
                  << " <SCRIPT_FILE> <INPUT_FILE> [--stack]\"\n";
        return 1;
    }

    bool show_stack = false;
    for (int i = 3; i < argc; ++i)
    {
        if (std::string(argv[i]) == "--stack") show_stack = true;
    }


    std::ifstream script(argv[1]);
    if (!script)
    {
        std::cerr << "Cannot open script: " << argv[1] << "\n";
        return 1;        
    }
    char c;
    while (script.get(c)) code += c;


    if (code.empty())
    {
        std::cerr << "Empty script: " << argv[1] << "\n";
        return 1;
    }

    std::ifstream input(argv[2]);
    if (!input)
    {
        std::cerr << "Cannot open input: " << argv[2] << "\n";
        return 1; 
    }
    while (input.get(c)) input_data += c;

    while (!input_data.empty() &&
           (input_data.back() == '\n' || input_data.back() == '\r'))
    {
        input_data.pop_back();
    }

    st = stack_create();
    run();
    if (show_stack) print_stack();
    stack_delete(st);
    st = nullptr;

    return 0;
}