#include "stack.h"

#include <cctype>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

namespace
{
typedef vector<string> Words;

int word_score(const string &word)
{
    int score = 0;
    for (unsigned char ch : word)
    {
        if (!isalpha(ch)) continue;
        switch (toupper(ch))
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

Words read_words(const string &path)
{
    ifstream file(path.c_str());
    if (!file) throw runtime_error("cannot open script file: " + path);
    Words words;
    string word;
    while (file >> word) words.push_back(word);
    return words;
}

void run(const Words &words, istream &input, ostream &output)
{
    Stack *stack = stack_create();
    long long pc = 0;
    while (pc >= 0 && static_cast<size_t>(pc) < words.size())
    {
        const int command = word_score(words[static_cast<size_t>(pc++)]);
        int parameter = 0;
        if (command == 5 || (command >= 13 && command <= 16))
        {
            if (static_cast<size_t>(pc) >= words.size()) throw runtime_error("missing command parameter");
            parameter = word_score(words[static_cast<size_t>(pc++)]);
        }

        switch (command)
        {
        case 5: stack_push(stack, parameter); break;
        case 6: stack_pop(stack); break;
        case 7: {
            const int right = stack_get(stack); stack_pop(stack);
            const int left = stack_get(stack); stack_pop(stack); stack_push(stack, left + right);
            break;
        }
        case 8: {
            char ch;
            if (!input.get(ch)) throw runtime_error("input exhausted");
            stack_push(stack, static_cast<unsigned char>(ch));
            break;
        }
        case 9: {
            const int value = stack_get(stack); stack_pop(stack);
            output.put(static_cast<char>(static_cast<unsigned char>(value)));
            break;
        }
        case 10: {
            const int first = stack_get(stack); stack_pop(stack);
            const int second = stack_get(stack); stack_pop(stack); stack_push(stack, second - first);
            break;
        }
        case 11: {
            const int first = stack_get(stack); stack_pop(stack);
            const int second = stack_get(stack); stack_pop(stack);
            stack_push(stack, first); stack_push(stack, second);
            break;
        }
        case 12: {
            const int value = stack_get(stack); stack_push(stack, value);
            break;
        }
        case 13: case 14: case 15: case 16: {
            const int value = stack_get(stack); stack_pop(stack);
            const bool take = (command == 13 || command == 15) ? value == 0 : value != 0;
            if (take)
            {
                if (command == 13 || command == 14) pc += static_cast<long long>(parameter) + 1;
                else pc -= parameter;
            }
            break;
        }
        case 17: stack_delete(stack); return;
        default: break;
        }
    }
    stack_delete(stack);
}
}

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        cout << "Usage: BeatnikCPP <script-file> <input-file>\n";
        return 1;
    }
    try
    {
        const Words words = read_words(argv[1]);
        ifstream input(argv[2], ios::binary);
        if (!input) throw runtime_error(string("cannot open input file: ") + argv[2]);
        run(words, input, cout);
    }
    catch (const exception &error)
    {
        cout << "Beatnik error: " << error.what() << '\n';
        return 1;
    }
    return 0;
}