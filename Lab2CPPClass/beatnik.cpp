#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cctype>

#include "stack.h"

static int evalWord(const std::string& token) {
    static const int alphaWeights[] = {
        1,3,3,2,1,4,2,4,1,8,5,1,3,
        1,1,3,10,1,1,1,1,4,4,8,4,10
    };

    int accum = 0;
    for (unsigned char ch : token) {
        if (std::isalpha(ch)) {
            accum += alphaWeights[std::toupper(ch) - 'A'];
        }
    }
    return accum;
}

int main(int argc, char** argv) {

    if (argc < 3) {
        std::cerr << "Недостаточно аргументов командной строки.\n";
        return 1;
    }

    std::ifstream programStream(argv[1]);
    std::ifstream dataStream(argv[2]);

    Stack stack;
    std::vector<int> opcodes;

    std::string lex;
    while (programStream >> lex) {
        opcodes.emplace_back(evalWord(lex));
    }

    for (size_t i = 0; i < opcodes.size(); ++i) {

        int op = opcodes[i];

        switch (op) {

            case 5: {
                if (i + 1 < opcodes.size()) {
                    stack.push(opcodes[++i]);
                }
                break;
            }

            case 6: {
                if (!stack.empty()) stack.pop();
                break;
            }

            case 7: {
                if (!stack.empty()) {
                    int a = stack.get(); stack.pop();
                    int b = stack.get(); stack.pop();
                    stack.push(a + b);
                }
                break;
            }

            case 8: {
                stack.push(dataStream.get());
                break;
            }

            case 9: {
                if (!stack.empty()) {
                    char c = static_cast<char>(stack.get());
                    stack.pop();
                    std::cout << c;
                }
                break;
            }

            case 10: {
                if (!stack.empty()) {
                    int a = stack.get(); stack.pop();
                    int b = stack.get(); stack.pop();
                    stack.push(b - a);
                }
                break;
            }

            case 11: {
                if (!stack.empty()) {
                    int a = stack.get(); stack.pop();
                    int b = stack.get(); stack.pop();
                    stack.push(a);
                    stack.push(b);
                }
                break;
            }

            case 12: {
                if (!stack.empty()) stack.push(stack.get());
                break;
            }

            case 13: {
                if (!stack.empty()) {
                    int cond = stack.get(); stack.pop();
                    if (cond == 0 && i + 1 < opcodes.size()) {
                        int delta = opcodes[i + 1];
                        i += delta + 1;
                        if (i >= opcodes.size()) i = opcodes.size() - 1;
                    }
                }
                break;
            }

            case 14: {
                if (!stack.empty()) {
                    int cond = stack.get(); stack.pop();
                    if (cond != 0 && i + 1 < opcodes.size()) {
                        int delta = opcodes[i + 1];
                        i += delta + 1;
                        if (i >= opcodes.size()) i = opcodes.size() - 1;
                    }
                }
                break;
            }

            case 15: {
                if (!stack.empty()) {
                    int cond = stack.get(); stack.pop();
                    if (cond == 0 && i + 1 < opcodes.size()) {
                        int delta = opcodes[i + 1];
                        if (delta > (int)i) i = 0;
                        else i -= delta;
                        --i;
                    }
                }
                break;
            }

            case 16: {
                if (!stack.empty()) {
                    int cond = stack.get(); stack.pop();
                    if (cond != 0 && i + 1 < opcodes.size()) {
                        int delta = opcodes[i + 1];
                        if (delta > (int)i) i = 0;
                        else i -= delta;
                        --i;
                    }
                }
                break;
            }

            case 17: {
                return 0;
            }

            default:
                break;
        }
    }

    return 0;
}