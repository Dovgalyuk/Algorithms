#include "stack.h"
#include "vector.h"

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

struct Position {
    int row;
    int column;
    int direction;
};

int hexValue(char c)
{
    const std::string digits = "0123456789ABCDEF";
    std::size_t index = digits.find(c);
    return index == std::string::npos ? -1 : static_cast<int>(index);
}

char hexDigit(int value)
{
    return "0123456789ABCDEF"[value & 15];
}

void run(const Vector<std::string>& script, std::istream& input)
{
    if (script.empty()) {
        throw std::runtime_error("Empty script");
    }

    std::size_t start = script.get(0).find('*');
    if (start == std::string::npos) {
        throw std::runtime_error("No * on the first line");
    }

    Stack<int> values;
    Stack<Position> branches;
    Position current = {0, static_cast<int>(start), -1};
    Position ret = current;
    bool hasRet = false;
    bool printing = false;

    for (;;) {
        if (current.row < 0 ||
            static_cast<std::size_t>(current.row) >= script.size() ||
            current.column < 0 ||
            static_cast<std::size_t>(current.column) >=
                script.get(static_cast<std::size_t>(current.row)).size()) {
            throw std::runtime_error("Cursor left the script");
        }

        char c = script.get(static_cast<std::size_t>(current.row))
                           [static_cast<std::size_t>(current.column)];

        if (c == '"') {
            printing = !printing;
        } else if (printing) {
            std::cout << c;
        } else if (hexValue(c) >= 0) {
            values.push(hexValue(c));
        } else {
            switch (c) {
            case '^': {
                Position right = {current.row + 1, current.column + 1, 1};
                branches.push(right);
                current.direction = -1;
                break;
            }
            case '~':
                if (branches.empty()) return;
                current = branches.pop();
                continue;
            case '/':
                current.direction = -1;
                break;
            case '\\':
                current.direction = 1;
                break;
            case '+': {
                int a = values.pop();
                int b = values.pop();
                values.push((a + b) & 15);
                break;
            }
            case '-': {
                int a = values.pop();
                int b = values.pop();
                values.push((b - a + 16) & 15);
                break;
            }
            case ':':
                values.push(values.top());
                break;
            case '%': {
                int a = values.pop();
                int b = values.pop();
                values.push(a);
                values.push(b);
                break;
            }
            case '$':
                values.pop();
                break;
            case '?':
                if (values.top() == 0) {
                    current.direction = -1;
                } else {
                    --values.top();
                    current.direction = 1;
                }
                break;
            case '.':
                std::cout << hexDigit(values.top());
                break;
            case '#': {
                int digit = input.get();
                if (digit == std::char_traits<char>::eof()) {
                    values.push(0);
                } else {
                    int value = hexValue(static_cast<char>(digit));
                    if (value < 0) {
                        throw std::runtime_error("Invalid hex digit in input");
                    }
                    values.push(value);
                }
                break;
            }
            case 'n':
                std::cout << '\n';
                break;
            case ',': {
                int low = values.pop();
                int high = values.top();
                values.push(low);
                std::cout << static_cast<char>(high * 16 + low);
                break;
            }
            case '&': {
                int byte = input.get();
                if (byte == std::char_traits<char>::eof()) byte = 0;
                values.push((byte >> 4) & 15);
                values.push(byte & 15);
                break;
            }
            case '{':
                ret = current;
                hasRet = true;
                break;
            case '}':
                if (!hasRet) {
                    throw std::runtime_error("Return location is not set");
                }
                current.row = ret.row;
                current.column = ret.column;
                continue;
            default:
                break;
            }
        }

        ++current.row;
        current.column += current.direction;
    }
}

int main(int argc, char* argv[])
{
    if (argc != 3) {
        std::cerr << "Usage: Lab2JollyScript <script_file> <input_file>\n";
        return 1;
    }

    try {
        std::ifstream scriptFile(argv[1]);
        std::ifstream inputFile(argv[2], std::ios::binary);
        if (!scriptFile || !inputFile) {
            throw std::runtime_error("Cannot open script or input file");
        }

        Vector<std::string> script;
        std::string line;
        while (std::getline(scriptFile, line)) {
            if (!line.empty() && line.back() == '\r') line.pop_back();
            if (script.empty() && line.compare(0, 3, "\xEF\xBB\xBF") == 0) {
                line.erase(0, 3);
            }
            std::size_t index = 0;
            while ((index = line.find("\xC2\xA0", index)) != std::string::npos) {
                line.replace(index, 2, " ");
                ++index;
            }
            script.push_back(line);
        }

        run(script, inputFile);
    } catch (const std::exception& error) {
        std::cerr << error.what() << '\n';
        return 1;
    }
    return 0;
}