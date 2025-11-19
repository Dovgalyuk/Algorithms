#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include "stack.h"
#include "list.h"

using namespace std;

string readFile(const string& path)
{
    ifstream f(path);
    if (!f) { 
        cerr << "Cannot open file: " << path << endl; 
        exit(1); 
    }
    return string((istreambuf_iterator<char>(f)), istreambuf_iterator<char>());
}

int stack_bottom(Stack& st)
{
    Stack temp;
    int last = 0;

    while (!st.empty())
    {
        last = st.get();
        temp.push(last);
        st.pop();
    }
    while (!temp.empty())
    {
        st.push(temp.get());
        temp.pop();
    }

    return last;
}

void stack_remove_bottom(Stack& st)
{
    Stack temp;

    while (!st.empty())
    {
        temp.push(st.get());
        st.pop();
    }

    if (!temp.empty())
        temp.pop();

    while (!temp.empty())
    {
        st.push(temp.get());
        temp.pop();
    }
}

string stack_join(Stack& st)
{
    string out;
    Stack temp;

    while (!st.empty())
    {
        char c = (char)st.get();
        temp.push(c);
        st.pop();
    }
    while (!temp.empty())
    {
        char c = (char)temp.get();
        out.push_back(c);
        st.push(c);
        temp.pop();
    }

    return out;
}

int main(int argc, char** argv)
{
    if (argc < 3)
    {
        cerr << "Usage: program <script.as> <input.txt>" << endl;
        return 1;
    }

    string script = readFile(argv[1]);
    string input = readFile(argv[2]);

    Stack st;
    unordered_map<int, int> vars;

    int ip = 0;
    int inputPos = 0;

    while (ip < (int)script.size())
    {
        char cmd = script[ip];

        if (cmd == '+')
        {
            ip++;
            if (ip >= script.size()) break;
            st.push((int)script[ip]);
        }
        else if (cmd == '-')
        {
            stack_remove_bottom(st);
        }
        else if (cmd == '<')
        {
            Stack tmp;
            while (!st.empty())
            {
                tmp.push(st.get());
                st.pop();
            }
            st = tmp;
        }
        else if (cmd == '>')
        {
            ip++;
            if (script[ip] != '{') break;
            ip++;
            while (ip < script.size() && script[ip] != '}')
            {
                cout << script[ip];
                ip++;
            }
        }
        else if (cmd == '.')
        {
            if (inputPos < input.size())
                st.push((int)input[inputPos++]);
        }
        else if (cmd == '?')
        {
            ip++;
            if (ip >= script.size()) break;

            char expected = script[ip];
            int bottom = stack_bottom(st);

            if ((char)bottom != expected)
            {
                while (ip < script.size() && script[ip] != '|')
                    ip++;
            }
        }
        else if (cmd == '|')
        {
        }
        else if (cmd == '!')
        {
            ip++;
            int target = 0;
            while (ip < script.size() && isdigit(script[ip]))
            {
                target = target * 10 + (script[ip] - '0');
                ip++;
            }
            ip = target;
            continue;
        }
        else if (cmd == '=')
        {
            ip++;
            if (isdigit(script[ip]))
            {
                int var = script[ip] - '0';
                vars[var] = stack_bottom(st);
            }
        }
        else if (cmd == '@')
        {
            ip++;
            int var = script[ip] - '0';
            if (vars.count(var))
                st.push(vars[var]);
        }

        ip++;
    }

    cout << "Final stack state:\n";
    while (!st.empty())
    {
        cout << (char)st.get() << "\n";
        st.pop();
    }

    return 0;
}