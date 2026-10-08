#include "stack.h"

#include <cctype>
#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

namespace
{
int word_score(const std::string &word)
{
    int score = 0;
    for (unsigned char ch : word)
    {
        if (!std::isalpha(ch)) continue;
        switch (std::toupper(ch))
        {
        case 'D': case 'G': score += 2; break;
        case 'B': case 'C': case 'M': case 'P': score += 3; break;
        case 'F': case 'H': case 'V': case 'W': case 'Y': score += 4; break;
        case 'K': score += 5; break;
        case 'J': case 'X': score += 8; break;
        case 'Q': case 'Z': score += 10; break;
        default: score += 1; break;
        }
    }
    return score;
}

std::vector<std::string> read_words(const std::string &path)
{
    std::ifstream file(path.c_str());
    if (!file) throw std::runtime_error("cannot open script file: " + path);
    std::vector<std::string> words;
    std::string word;
    while (file >> word) words.push_back(word);
    return words;
}

void run(const std::vector<std::string> &words, std::istream &input, std::ostream &output)
{
    std::unique_ptr<Stack, decltype(&stack_delete)> stack(stack_create(), stack_delete);
    long long pc = 0;
    while (pc >= 0 && static_cast<size_t>(pc) < words.size())
    {
        const int command = word_score(words[static_cast<size_t>(pc++)]);
        int parameter = 0;
        if (command == 5 || (command >= 13 && command <= 16))
        {
            if (static_cast<size_t>(pc) >= words.size()) throw std::runtime_error("missing command parameter");
            parameter = word_score(words[static_cast<size_t>(pc++)]);
        }

        switch (command)
        {
        case 5: stack_push(stack.get(), parameter); break;
        case 6: stack_pop(stack.get()); break;
        case 7: {
            const int right = stack_get(stack.get()); stack_pop(stack.get());
            const int left = stack_get(stack.get()); stack_pop(stack.get()); stack_push(stack.get(), left + right);
            break;
        }
        case 8: {
            char ch;
            if (!input.get(ch)) throw std::runtime_error("input exhausted");
            stack_push(stack.get(), static_cast<unsigned char>(ch));
            break;
        }
        case 9: {
            const int value = stack_get(stack.get()); stack_pop(stack.get());
            output.put(static_cast<char>(static_cast<unsigned char>(value)));
            break;
        }
        case 10: {
            const int first = stack_get(stack.get()); stack_pop(stack.get());
            const int second = stack_get(stack.get()); stack_pop(stack.get()); stack_push(stack.get(), second - first);
            break;
        }
        case 11: {
            const int first = stack_get(stack.get()); stack_pop(stack.get());
            const int second = stack_get(stack.get()); stack_pop(stack.get());
            stack_push(stack.get(), first); stack_push(stack.get(), second);
            break;
        }
        case 12: {
            const int value = stack_get(stack.get()); stack_push(stack.get(), value);
            break;
        }
        case 13: case 14: case 15: case 16: {
            const int value = stack_get(stack.get()); stack_pop(stack.get());
            const bool take = (command == 13 || command == 15) ? value == 0 : value != 0;
            if (take)
            {
                if (command == 13 || command == 14) pc += static_cast<long long>(parameter) + 1;
                else pc -= parameter;
            }
            break;
        }
        case 17: return;
        default: break;
        }
    }
}
}

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        std::cerr << "Usage: BeatnikCPP <script-file> <input-file>\n";
        return 1;
    }
    try
    {
        const std::vector<std::string> words = read_words(argv[1]);
        std::ifstream input(argv[2], std::ios::binary);
        if (!input) throw std::runtime_error(std::string("cannot open input file: ") + argv[2]);
        run(words, input, std::cout);
    }
    catch (const std::exception &error)
    {
        std::cerr << "Beatnik error: " << error.what() << '\n';
        return 1;
    }
    return 0;
}
