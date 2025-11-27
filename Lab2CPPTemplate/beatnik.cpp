#include "stack.h"

#include <cctype>
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>

using namespace std;

static const int SCRABBLE[26] = { 1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10 };

static int scrabble(char c)
{
    if (c < 'A' || c > 'Z') return 0;
    return SCRABBLE[c - 'A'];
}

static int wordValue(const string& word)
{
    int sum = 0;
    for (char c : word)
        if (isalpha(c))
            sum += scrabble(char(toupper(c)));
    return sum;
}

void runBeatnik(const string& script, const string& input)
{
    Stack<int> stack;
    istringstream inputStream(input);

    vector<string> words;
    string w;
    istringstream ss(script);
    while (ss >> w)
        words.push_back(w);

    for (int i = 0; i < (int)words.size(); ++i)
    {        
        int value = wordValue(words[i]);
        int a, b, n;
        char c;

        switch (value)
        {
            case 5:
                if (i + 1 < (int)words.size())
                    stack.push(wordValue(words[++i]));
                break;
            case 6:
                stack.pop();
                break;
            case 7:
                a = stack.get(); stack.pop();
                b = stack.get(); stack.pop();
                stack.push(a + b);
                break;
            case 8:
                inputStream.get(c);
                stack.push((unsigned char)c);
                break;
            case 9:
                c = static_cast<char>(static_cast<unsigned char>(stack.get()));
                stack.pop();
                cout << c << endl;
                break;
            case 10:
                a = stack.get(); stack.pop();
                b = stack.get(); stack.pop();
                stack.push(b - a);
                break;
            case 11:
                a = stack.get(); stack.pop();
                b = stack.get(); stack.pop();
                stack.push(a);
                stack.push(b);
                break;
            case 12:
                a = stack.get();
                stack.push(a);
                break;
            case 13:
                a = stack.get(); stack.pop();
                n = wordValue(words[i + 1]);
                if (a == 0)
                    i += n + 1;
                else
                    i++;
                break;
            case 14:
                a = stack.get(); stack.pop();
                n = wordValue(words[i + 1]);
                if (a != 0)
                    i += n + 1;
                else
                    i++;
                break;
            case 15:
                a = stack.get(); stack.pop();
                n = wordValue(words[i + 1]);
                if (a == 0)
                    i -= n;
                else
                    i++;
                break;
            case 16:
                a = stack.get(); stack.pop();
                n = wordValue(words[i + 1]);
                if (a != 0)
                    i -= n;
                else
                    i++;
                break;
            case 17:
                return;

            default:
                break;
        }
    }
}

int main(int argc, char* argv[])
{
    if (argc != 3)
        return 1;

    ifstream scriptFile(argv[1]);
    ifstream inputFile(argv[2]);

    stringstream script, input;
    script << scriptFile.rdbuf();
    input << inputFile.rdbuf();

    runBeatnik(script.str(), input.str());
    return 0;
}
