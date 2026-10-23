// Задание 1:
//Написать интерпретатор языка Hanoi: https://esolangs.org/wiki/Hanoi
//
//Программа получает на вход два файла: скрипт на языке Hanoi и входные данные для этого скрипта.
//Скрипт состоит из последовательности команд для манипуляции дисками на трех стержнях по правилам
//головоломки "Ханойские башни". Каждый стержень можно представить в виде стека.
//
//После завершения скрипта вывести состояние всех трех стеков.

#include <fstream>
#include <iostream>
#include <iterator>
#include <ostream>
#include <stdexcept>
#include <string>

#include "stack.h"

namespace
{
    const int EMPTY_VALUE = 255;
    typedef Stack<int> DiskStack;

    class HanoiError : public std::runtime_error
    {
    public:
        explicit HanoiError(const std::string &message) : std::runtime_error(message)
        {
        }
    };

    class Tower
    {
    public:
        void push(int value)
        {
            const int limit = disks_.empty() ? EMPTY_VALUE : disks_.get();
            if (value > limit)
                throw HanoiError("Towers of Hanoi rule violated: disk " + std::to_string(value) +
                                 " is larger than disk " + std::to_string(limit));
            disks_.push(value);
        }

        int pop()
        {
            if (disks_.empty())
                return EMPTY_VALUE;
            const int value = disks_.get();
            disks_.pop();
            return value;
        }

        std::string toString() const
        {
            DiskStack copy = disks_;
            DiskStack reversed;
            while (!copy.empty())
            {
                reversed.push(copy.get());
                copy.pop();
            }

            std::string result;
            while (!reversed.empty())
            {
                appendSymbol(result, reversed.get());
                reversed.pop();
            }
            return result;
        }

    private:
        static void appendSymbol(std::string &out, int value)
        {
            if (value >= 32 && value <= 126)
            {
                out += static_cast<char>(value);
            }
            else
            {
                const char *digits = "0123456789abcdef";
                out += "\\x";
                out += digits[(value >> 4) & 0xF];
                out += digits[value & 0xF];
            }
        }

        DiskStack disks_;
    };

    class Interpreter
    {
    public:
        Interpreter(const std::string &input, std::ostream &out) : out_(out), printed_(false)
        {
            for (size_t i = input.size(); i > 0; --i)
                input_.push(static_cast<unsigned char>(input[i - 1]));
        }

        void run(const std::string &script)
        {
            for (size_t pos = 0; pos < script.size(); ++pos)
            {
                try
                {
                    step(script[pos]);
                }
                catch (const HanoiError &e)
                {
                    throw HanoiError("command '" + std::string(1, script[pos]) + "' at position " +
                                     std::to_string(pos + 1) + ": " + e.what());
                }
            }
        }

        void printState()
        {
            if (printed_)
                out_ << '\n';
            out_ << tower1_.toString() << '\n'
                 << tower2_.toString() << '\n'
                 << tower3_.toString() << '\n';
        }

    private:
        void step(char command)
        {
            switch (command)
            {
            case '-':
            {
                const int a = tower2_.pop();
                const int b = tower2_.pop();
                tower2_.push(b);
                tower2_.push(b - a);
                break;
            }
            case '>':
            {
                const int a = tower2_.pop();
                tower2_.push(a);
                tower2_.push(a);
                break;
            }
            case '<':
            {
                const int a1 = tower2_.pop();
                const int a2 = tower2_.pop();
                if (a1 != a2)
                    throw HanoiError("irreversible operation: values " + std::to_string(a1) +
                                     " and " + std::to_string(a2) + " are not equal");
                tower2_.push(a1);
                break;
            }
            case '(':
                tower2_.push(tower1_.pop());
                break;
            case ')':
                tower1_.push(tower2_.pop());
                break;
            case '[':
                tower2_.push(tower3_.pop());
                break;
            case ']':
                tower3_.push(tower2_.pop());
                break;
            case '{':
                tower2_.push(readInput());
                break;
            case '}':
                out_.put(static_cast<char>(tower2_.pop()));
                printed_ = true;
                break;
            default:
                break;
            }
        }

        int readInput()
        {
            if (input_.empty())
                return 0;
            const int value = input_.get();
            input_.pop();
            return value;
        }

        Tower tower1_;
        Tower tower2_;
        Tower tower3_;
        DiskStack input_;
        std::ostream &out_;
        bool printed_;
    };

    std::string readFile(const std::string &path)
    {
        std::ifstream file(path, std::ios::binary);
        if (!file)
            throw std::runtime_error("cannot open file: " + path);
        return std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
    }
}

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        std::cerr << "Usage: " << argv[0] << " <script> <input>" << std::endl;
        return 2;
    }

    try
    {
        const std::string script = readFile(argv[1]);
        std::string input = readFile(argv[2]);
        while (!input.empty() && (input.back() == '\n' || input.back() == '\r'))
            input.pop_back();

        Interpreter interpreter(input, std::cout);
        interpreter.run(script);
        interpreter.printState();
    }
    catch (const HanoiError &e)
    {
        std::cout.flush();
        std::cerr << "Hanoi error: " << e.what() << std::endl;
        return 1;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 2;
    }
    return 0;
}