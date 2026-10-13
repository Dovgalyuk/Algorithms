#include <cstdint>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Instruction
{
    string command;
    int argument = 0;
    bool has_argument = false;
    int line_number = 0;
};

struct StackValue
{
    int value;
    bool is_address;
};

class VmStack
{
public:
    void push(int value)
    {
        values.push_back({value, false});
    }

    void push_address(int value)
    {
        values.push_back({value, true});
    }

    int get() const
    {
        return values.back().value;
    }

    bool is_address() const
    {
        return !values.empty() && values.back().is_address;
    }

    void pop()
    {
        if (!values.empty())
            values.pop_back();
    }

    bool empty() const
    {
        return values.empty();
    }

private:
    vector<StackValue> values;
};

static uint32_t bits(int value)
{
    return static_cast<uint32_t>(static_cast<int32_t>(value));
}

static int from_bits(uint32_t value)
{
    return static_cast<int>(static_cast<int32_t>(value));
}

static bool parse_int(const string &text, int &value)
{
    try
    {
        size_t used = 0;
        long long parsed = stoll(text, &used);
        if (used != text.size() || parsed < numeric_limits<int>::min() ||
            parsed > numeric_limits<int>::max())
            return false;
        value = static_cast<int>(parsed);
        return true;
    }
    catch (...)
    {
        return false;
    }
}

static bool is_local_command(const string &command, const string &prefix, int &index)
{
    if (command.size() != prefix.size() + 1 || command.compare(0, prefix.size(), prefix) != 0)
        return false;

    char digit = command.back();
    if (digit < '0' || digit > '3')
        return false;

    index = digit - '0';
    return true;
}

static bool is_known_command(const string &command)
{
    int index = 0;
    if (is_local_command(command, "iload_", index) || is_local_command(command, "istore_", index))
        return true;

    return command == "bipush" || command == "iload" || command == "istore" ||
           command == "invokestatic" || command == "return" || command == "swap" ||
           command == "dup" || command == "pop" || command == "ineg" ||
           command == "iadd" || command == "isub" || command == "imul" ||
           command == "idiv" || command == "irem" || command == "iand" ||
           command == "ior" || command == "ixor" || command == "ishl" ||
           command == "ishr" || command == "iushr";
}

static bool command_needs_argument(const string &command)
{
    return command == "bipush" || command == "iload" || command == "istore" ||
           command == "invokestatic";
}

static bool read_program(const string &file_name, vector<Instruction> &program)
{
    ifstream file(file_name);
    if (!file)
    {
        cerr << "Error: cannot open file " << file_name << '\n';
        return false;
    }

    string line;
    int line_number = 0;
    while (getline(file, line))
    {
        ++line_number;
        size_t comment = line.find('#');
        if (comment != string::npos)
            line.erase(comment);

        istringstream input(line);
        Instruction instruction;
        instruction.line_number = line_number;
        if (!(input >> instruction.command))
            continue;

        string argument;
        if (input >> argument)
        {
            if (!parse_int(argument, instruction.argument))
            {
                cerr << "Error: invalid argument at line " << line_number << '\n';
                return false;
            }
            instruction.has_argument = true;
        }

        string extra;
        if (input >> extra)
        {
            cerr << "Error: extra data at line " << line_number << '\n';
            return false;
        }

        if (!is_known_command(instruction.command))
        {
            cerr << "Error: unknown instruction " << instruction.command
                 << " at line " << line_number << '\n';
            return false;
        }

        if (command_needs_argument(instruction.command) != instruction.has_argument)
        {
            cerr << "Error: invalid arguments for " << instruction.command
                 << " at line " << line_number << '\n';
            return false;
        }

        if ((instruction.command == "iload" || instruction.command == "istore") &&
            (instruction.argument < 0 || instruction.argument > 3))
        {
            cerr << "Error: invalid local variable index at line " << line_number << '\n';
            return false;
        }

        program.push_back(instruction);
    }

    return true;
}

static bool pop_value(VmStack &stack, int &value)
{
    if (stack.empty() || stack.is_address())
        return false;

    value = stack.get();
    stack.pop();
    return true;
}

static bool fail_instruction(const Instruction &instruction, const string &message)
{
    cerr << "Error: " << message << " at line " << instruction.line_number << '\n';
    return false;
}

static bool run_program(const vector<Instruction> &program, int vars[4], VmStack &stack)
{
    size_t pc = 0;

    while (pc < program.size())
    {
        const Instruction &instruction = program[pc];
        const string &command = instruction.command;
        int local_index = 0;

        if (command == "bipush")
        {
            stack.push(instruction.argument);
        }
        else if (command == "iload" || is_local_command(command, "iload_", local_index))
        {
            if (command == "iload")
                local_index = instruction.argument;
            stack.push(vars[local_index]);
        }
        else if (command == "istore" || is_local_command(command, "istore_", local_index))
        {
            if (command == "istore")
                local_index = instruction.argument;
            int value;
            if (!pop_value(stack, value))
                return fail_instruction(instruction, "invalid " + command);
            vars[local_index] = value;
        }
        else if (command == "invokestatic")
        {
            if (instruction.argument < 0 || static_cast<size_t>(instruction.argument) >= program.size())
                return fail_instruction(instruction, "invalid function address");

            stack.push_address(static_cast<int>(pc + 1));
            pc = static_cast<size_t>(instruction.argument);
            continue;
        }
        else if (command == "return")
        {
            // A return from the main program is allowed only with an empty stack.
            if (stack.empty())
                break;

            if (!stack.is_address())
                return fail_instruction(instruction, "invalid return");

            pc = static_cast<size_t>(stack.get());
            stack.pop();
            continue;
        }
        else if (command == "swap")
        {
            if (stack.empty())
                return fail_instruction(instruction, "invalid swap");
            StackValue first{stack.get(), stack.is_address()};
            stack.pop();

            if (stack.empty())
                return fail_instruction(instruction, "invalid swap");
            StackValue second{stack.get(), stack.is_address()};
            stack.pop();

            if (first.is_address)
                stack.push_address(first.value);
            else
                stack.push(first.value);
            if (second.is_address)
                stack.push_address(second.value);
            else
                stack.push(second.value);
        }
        else if (command == "dup")
        {
            if (stack.empty() || stack.is_address())
                return fail_instruction(instruction, "invalid dup");
            stack.push(stack.get());
        }
        else if (command == "pop")
        {
            if (stack.empty() || stack.is_address())
                return fail_instruction(instruction, "invalid pop");
            stack.pop();
        }
        else if (command == "ineg")
        {
            int value;
            if (!pop_value(stack, value))
                return fail_instruction(instruction, "invalid ineg");
            stack.push(from_bits(0u - bits(value)));
        }
        else
        {
            int right = 0;
            int left = 0;
            if (!pop_value(stack, right) || !pop_value(stack, left))
                return fail_instruction(instruction, "invalid " + command);

            int result = 0;
            if (command == "iadd")
                result = from_bits(bits(left) + bits(right));
            else if (command == "isub")
                result = from_bits(bits(left) - bits(right));
            else if (command == "imul")
                result = from_bits(bits(left) * bits(right));
            else if (command == "idiv")
            {
                if (right == 0)
                    return fail_instruction(instruction, "division by zero");
                if (left == numeric_limits<int>::min() && right == -1)
                    result = numeric_limits<int>::min();
                else
                    result = left / right;
            }
            else if (command == "irem")
            {
                if (right == 0)
                    return fail_instruction(instruction, "division by zero");
                if (left == numeric_limits<int>::min() && right == -1)
                    result = 0;
                else
                    result = left % right;
            }
            else if (command == "iand")
                result = from_bits(bits(left) & bits(right));
            else if (command == "ior")
                result = from_bits(bits(left) | bits(right));
            else if (command == "ixor")
                result = from_bits(bits(left) ^ bits(right));
            else if (command == "ishl")
                result = from_bits(bits(left) << (bits(right) & 31u));
            else if (command == "ishr")
            {
                unsigned int shift = bits(right) & 31u;
                uint32_t value = bits(left);
                if (shift != 0)
                {
                    value >>= shift;
                    if ((bits(left) & 0x80000000u) != 0)
                        value |= (~uint32_t{0}) << (32u - shift);
                }
                result = from_bits(value);
            }
            else if (command == "iushr")
                result = from_bits(bits(left) >> (bits(right) & 31u));

            stack.push(result);
        }

        ++pc;
    }

    return true;
}

int main(int argc, char *argv[])
{
    const string file_name = argc > 1 ? argv[1] : "input.txt";
    vector<Instruction> program;
    if (!read_program(file_name, program))
        return 1;

    VmStack stack;
    int vars[4] = {0, 0, 0, 0};
    if (!run_program(program, vars, stack))
        return 1;

    vector<int> stack_values;
    while (!stack.empty())
    {
        stack_values.push_back(stack.get());
        stack.pop();
    }

    cout << "Stack:";
    for (int value : stack_values)
        cout << ' ' << value;
    cout << '\n';

    cout << "Variables:";
    for (int value : vars)
        cout << ' ' << value;
    cout << '\n';
    return 0;
}
