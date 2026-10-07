#include <climits>
#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
#include "stack.h"

namespace
{
const std::string hex_digits = "0123456789ABCDEF";
using StackPtr = std::unique_ptr<Stack, decltype(&stack_delete)>;

struct Cursor
{
    int x;
    int y;
    int direction;
};

int pop(Stack *stack)
{
    int value = stack_get(stack);
    stack_pop(stack);
    return value;
}

// Each pending branch occupies three integers in the library stack.
void save_branch(Stack *branches, Cursor cursor)
{
    stack_push(branches, cursor.x);
    stack_push(branches, cursor.y);
    stack_push(branches, cursor.direction);
}

Cursor take_branch(Stack *branches)
{
    int direction = pop(branches);
    int y = pop(branches);
    int x = pop(branches);
    return {x, y, direction};
}

int read_byte(std::istream &input)
{
    int value = input.get();
    if (input.bad() || (input.fail() && !input.eof()))
        throw std::runtime_error("Cannot read input data");
    return value == std::char_traits<char>::eof() ? 0 : value;
}

void execute(const std::vector<std::string> &script, std::istream &input)
{
    if (script.empty())
        throw std::runtime_error("Empty script");
    auto start = script.front().find('*');
    if (start == std::string::npos || script.front().find('*', start + 1) != std::string::npos)
        throw std::runtime_error("The first line must contain exactly one '*'");

    StackPtr values(stack_create(), stack_delete);
    StackPtr branches(stack_create(), stack_delete);
    save_branch(branches.get(), {static_cast<int>(start), 0, -1});
    Cursor ret{0, 0, -1};
    bool has_ret = false;
    bool printing = false;

    while (!stack_empty(branches.get()))
    {
        Cursor cursor = take_branch(branches.get());
        // Finish the active branch before taking the next pending branch.
        bool finished = false;
        while (!finished)
        {
            if (cursor.y < 0 || static_cast<std::size_t>(cursor.y) >= script.size() ||
                cursor.x < 0 || static_cast<std::size_t>(cursor.x) >= script[cursor.y].size())
                throw std::runtime_error("Cursor outside the script");

            char command = script[cursor.y][cursor.x];
            try
            {
                if (command == '"')
                    printing = !printing;
                else if (printing)
                    std::cout.put(command);
                else
                {
                    auto digit = hex_digits.find(command);
                    if (digit != std::string::npos)
                        stack_push(values.get(), static_cast<int>(digit));
                    else
                    {
                        switch (command)
                        {
                        case '/': cursor.direction = -1; break;
                        case '\\': cursor.direction = 1; break;
                        case '^':
                            save_branch(branches.get(), {cursor.x + 1, cursor.y + 1, 1});
                            cursor.direction = -1;
                            break;
                        case '~': finished = true; break;
                        case '+':
                        case '-':
                        {
                            int a = pop(values.get());
                            int b = pop(values.get());
                            int result = command == '+' ? a + b : b - a;
                            stack_push(values.get(), (result + 16) % 16);
                            break;
                        }
                        case ':': stack_push(values.get(), stack_get(values.get())); break;
                        case '%':
                        {
                            int a = pop(values.get());
                            int b = pop(values.get());
                            stack_push(values.get(), a);
                            stack_push(values.get(), b);
                            break;
                        }
                        case '$': stack_pop(values.get()); break;
                        case '?':
                        {
                            int value = stack_get(values.get());
                            cursor.direction = value == 0 ? -1 : 1;
                            if (value != 0)
                            {
                                stack_pop(values.get());
                                stack_push(values.get(), value - 1);
                            }
                            break;
                        }
                        case '.': std::cout.put(hex_digits[stack_get(values.get())]); break;
                        case '#':
                        {
                            char value = static_cast<char>(read_byte(input));
                            auto number = value == '\0' && input.eof() ? 0 : hex_digits.find(value);
                            if (number == std::string::npos)
                                throw std::runtime_error("Invalid hexadecimal input");
                            stack_push(values.get(), static_cast<int>(number));
                            break;
                        }
                        case 'n': std::cout.put('\n'); break;
                        case ',':
                        {
                            int low = pop(values.get());
                            int high = stack_get(values.get());
                            stack_push(values.get(), low);
                            std::cout.put(static_cast<char>(high * 16 + low));
                            break;
                        }
                        case '&':
                        {
                            int value = read_byte(input);
                            stack_push(values.get(), value / 16);
                            stack_push(values.get(), value % 16);
                            break;
                        }
                        case '{': ret = cursor; has_ret = true; break;
                        case '}':
                            if (!has_ret)
                                throw std::runtime_error("Return location is not set");
                            cursor.x = ret.x;
                            cursor.y = ret.y;
                            continue;
                        default: break; // Comments, including spaces.
                        }
                    }
                }
            }
            catch (const std::exception &error)
            {
                throw std::runtime_error("Line " + std::to_string(cursor.y + 1) +
                    ", column " + std::to_string(cursor.x + 1) + ": " + error.what());
            }
            cursor.x += cursor.direction;
            ++cursor.y;
        }
    }
    if (!std::cout)
        throw std::runtime_error("Cannot write output");
}
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cerr << "Usage: JollyScript <script> <input-data>\n";
        return 1;
    }
    try
    {
        std::ifstream script_file(argv[1], std::ios::binary);
        if (!script_file)
            throw std::runtime_error("Cannot open script file");
        std::ifstream input_file(argv[2], std::ios::binary);
        if (!input_file)
            throw std::runtime_error("Cannot open input data file");
        std::vector<std::string> script;
        std::string line;
        while (std::getline(script_file, line))
        {
            if (!line.empty() && line.back() == '\r')
                line.pop_back();
            // Keep coordinates and diagonal steps representable as int.
            if (line.size() >= INT_MAX || script.size() >= INT_MAX - 1)
                throw std::runtime_error("Script is too large");
            script.push_back(line);
        }
        if (script_file.bad())
            throw std::runtime_error("Cannot read script file");
        execute(script, input_file);
        return 0;
    }
    catch (const std::exception &error)
    {
        std::cerr << "JollyScript: " << error.what() << '\n';
        return 1;
    }
}
