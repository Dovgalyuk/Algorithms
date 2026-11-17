#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "stack.h"

namespace {

void push_string(Stack& stack, std::vector<std::string>& pool, const std::string& value) {
    int id = static_cast<int>(pool.size());
    pool.push_back(value);
    stack.push(id);
}

std::string top_string(const Stack& stack, const std::vector<std::string>& pool) {
    return pool[static_cast<size_t>(stack.get())];
}

void reverse_stack(Stack& stack) {
    Stack reversed;
    while (!stack.empty()) {
        reversed.push(stack.get());
        stack.pop();
    }
    stack = reversed;
}

bool parse_ll(const std::string& s, long long& out) {
    try {
        size_t pos = 0;
        out = std::stoll(s, &pos);
        return pos == s.size();
    } catch (const std::exception&) {
        return false;
    }
}

std::string read_argument(const std::string& script, size_t& index, const std::string& holder,
                          const std::vector<std::string>& vars) {
    ++index;
    if (index >= script.size()) {
        return "";
    }

    if (script[index] == '{') {
        size_t close_pos = script.find('}', index + 1);
        if (close_pos == std::string::npos) {
            std::string arg = script.substr(index + 1);
            index = script.size() - 1;
            return arg;
        }
        std::string arg = script.substr(index + 1, close_pos - index - 1);
        index = close_pos;
        return arg;
    }

    if (script[index] == '@') {
        ++index;
        size_t start = index;
        while (index < script.size() && std::isdigit(static_cast<unsigned char>(script[index]))) {
            ++index;
        }
        std::string num_str = script.substr(start, index - start);
        --index;
        if (num_str.empty()) {
            return "";
        }
        size_t var_idx = static_cast<size_t>(std::stoul(num_str));
        if (var_idx >= 1 && var_idx <= vars.size()) {
            return vars[var_idx - 1];
        }
        return "";
    }

    if (script[index] == '~') {
        return holder;
    }

    return std::string(1, script[index]);
}

void skip_to_pipe(const std::string& script, size_t& index) {
    std::string dummy_holder;
    std::vector<std::string> dummy_vars;
    for (++index; index < script.size(); ++index) {
        char cmd = script[index];
        if (cmd == '|') {
            return;
        }
        if (cmd == '+' || cmd == '>' || cmd == '&' || cmd == '?' || cmd == '!' || cmd == '$') {
            read_argument(script, index, dummy_holder, dummy_vars);
        }
    }
}

}  // namespace

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <script_file> <input_file>\n";
        return 1;
    }

    std::ifstream script_stream(argv[1]);
    if (!script_stream) {
        std::cerr << "Unable to open script file: " << argv[1] << "\n";
        return 1;
    }

    std::ifstream input_stream(argv[2]);
    if (!input_stream) {
        std::cerr << "Unable to open input file: " << argv[2] << "\n";
        return 1;
    }

    std::ostringstream buffer;
    buffer << script_stream.rdbuf();
    std::string script = buffer.str();
    while (!script.empty() && (script.back() == '\n' || script.back() == '\r')) {
        script.pop_back();
    }

    Stack stack;
    std::vector<std::string> pool;
    std::vector<std::string> vars;
    std::string holder;

    const size_t max_steps = 100000;
    size_t steps = 0;

    for (size_t i = 0; i < script.size() && steps < max_steps; ++i, ++steps) {
        char cmd = script[i];
        if (cmd == '\r' || cmd == '\n') {
            continue;
        }

        switch (cmd) {
            case '+': {
                std::string val = read_argument(script, i, holder, vars);
                push_string(stack, pool, val);
                break;
            }
            case '-': {
                if (!stack.empty()) {
                    stack.pop();
                }
                break;
            }
            case '<': {
                reverse_stack(stack);
                break;
            }
            case ':': {
                std::string joined;
                while (!stack.empty()) {
                    joined += top_string(stack, pool);
                    stack.pop();
                }
                push_string(stack, pool, joined);
                break;
            }
            case '~': {
                if (!stack.empty()) {
                    holder = top_string(stack, pool);
                }
                break;
            }
            case '=': {
                vars.push_back(holder);
                break;
            }
            case '_': {
                std::string line;
                if (std::getline(input_stream, line)) {
                    if (!line.empty() && line.back() == '\r') {
                        line.pop_back();
                    }
                    push_string(stack, pool, line);
                } else {
                    push_string(stack, pool, "");
                }
                break;
            }
            case '>': {
                std::string val = read_argument(script, i, holder, vars);
                std::cout << val << "\n";
                break;
            }
            case '&': {
                std::string op = read_argument(script, i, holder, vars);
                if (stack.empty()) {
                    break;
                }
                long long b = 0;
                bool ok_b = parse_ll(top_string(stack, pool), b);
                stack.pop();

                if (stack.empty()) {
                    break;
                }
                long long a = 0;
                bool ok_a = parse_ll(top_string(stack, pool), a);
                stack.pop();

                long long result = 0;
                if (ok_a && ok_b && !op.empty()) {
                    switch (op[0]) {
                        case '+':
                            result = a + b;
                            break;
                        case '-':
                            result = a - b;
                            break;
                        case '*':
                            result = a * b;
                            break;
                        case '/':
                            result = (b != 0) ? (a / b) : 0;
                            break;
                        case '%':
                            result = (b != 0) ? (a % b) : 0;
                            break;
                        default:
                            break;
                    }
                }
                push_string(stack, pool, std::to_string(result));
                break;
            }
            case '?': {
                std::string expected = read_argument(script, i, holder, vars);
                if (holder != expected) {
                    skip_to_pipe(script, i);
                }
                break;
            }
            case '|': {
                break;
            }
            case '!': {
                std::string target_str = read_argument(script, i, holder, vars);
                long long target = 0;
                if (parse_ll(target_str, target) && target >= 0 && static_cast<size_t>(target) < script.size()) {
                    if (target == 0) {
                        // Перезапуск с 0-го символа после ++i в цикле
                        i = static_cast<size_t>(-1);
                    } else {
                        i = static_cast<size_t>(target) - 1;
                    }
                }
                break;
            }
            case '#': {
                i = script.size();
                break;
            }
            case '$': {
                std::string max_str = read_argument(script, i, holder, vars);
                long long max_val = 1;
                if (!max_str.empty()) {
                    parse_ll(max_str, max_val);
                }
                long long rnd = (max_val > 0) ? (1 + std::rand() % max_val) : 0;
                push_string(stack, pool, std::to_string(rnd));
                break;
            }
            default:
                break;
        }
    }

    Stack output_stack;
    while (!stack.empty()) {
        output_stack.push(stack.get());
        stack.pop();
    }
    while (!output_stack.empty()) {
        std::cout << top_string(output_stack, pool) << "\n";
        output_stack.pop();
    }

    return 0;
}