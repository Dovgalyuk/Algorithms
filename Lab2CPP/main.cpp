#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <cctype>
#include <chrono>
#include <thread>
#include <random>

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

Data stack_bottom(Stack& st)
{
    Stack temp;
    Data last = 0;
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
    st.remove_bottom();
}

string stack_join(Stack& st)
{
    return st.join_to_string();
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
    unordered_map<int, Data> vars;
    Data tilde = 0;

    size_t ip = 0;
    size_t inputPos = 0;

    mt19937 rng((unsigned)chrono::high_resolution_clock::now().time_since_epoch().count());

    while (ip < script.size())
    {
        char cmd = script[ip];

        if (cmd == '+')
        {
            ip++;
            if (ip >= script.size()) break;
            if (script[ip] == '{')
            {
                ip++;
                string lit;
                while (ip < script.size() && script[ip] != '}')
                {
                    lit.push_back(script[ip]);
                    ip++;
                }
                for (char c : lit)
                    st.push((Data)c);
            }
            else
            {
                st.push((Data)script[ip]);
            }
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
        else if (cmd == ':')
        {
            string s = stack_join(st);
            while (!st.empty()) st.pop();
            for (char c : s)
                st.push((Data)c);
        }
        else if (cmd == '>')
        {
            ip++;
            if (ip >= script.size()) break;
            if (script[ip] == '{')
            {
                ip++;
                while (ip < script.size() && script[ip] != '}')
                {
                    cout << script[ip];
                    ip++;
                }
            }
            else
            {
                cout << script[ip];
            }
        }
        else if (cmd == '~')
        {
            if (ip + 1 < script.size() && script[ip + 1] == '\\')
            {
                tilde = 0;
                ip++;
            }
            else if (ip + 1 < script.size() && script[ip + 1] == '(')
            {
                ip += 2;
                int n = 0;
                while (ip < script.size() && isdigit((unsigned char)script[ip]))
                {
                    n = n * 10 + (script[ip] - '0');
                    ip++;
                }
                if (vars.count(n)) tilde = vars[n];
            }
            else
            {
                if (!st.empty())
                    tilde = stack_bottom(st);
                else
                    tilde = 0;
            }
        }
        else if (cmd == '!')
        {
            size_t look = ip + 1;
            if (look < script.size() && isdigit((unsigned char)script[look]))
            {
                int target = 0;
                ip++;
                while (ip < script.size() && isdigit((unsigned char)script[ip]))
                {
                    target = target * 10 + (script[ip] - '0');
                    ip++;
                }
                if (target >= 0 && (size_t)target < script.size())
                {
                    ip = (size_t)target;
                    continue;
                }
                else
                {
                    ip = script.size();
                    continue;
                }
            }
        }
        else if (cmd == '?')
        {
            bool notEqual = false;
            size_t look = ip + 1;
            if (look < script.size() && script[look] == '!')
            {
                notEqual = true;
                ip++;
            }
            ip++;
            if (ip >= script.size()) break;
            char expected = 0;
            if (script[ip] == '{')
            {
                ip++;
                if (ip < script.size()) expected = script[ip];
                while (ip < script.size() && script[ip] != '}') ip++;
            }
            else
            {
                expected = script[ip];
            }
            bool cond = ((char)tilde == expected);
            if (notEqual) cond = !cond;

            if (!cond)
            {
                ip++;
                while (ip < script.size())
                {
                    if (script[ip] == '!')
                    {
                        size_t t = ip + 1;
                        bool digitAfter = (t < script.size() && isdigit((unsigned char)script[t]));
                        if (!digitAfter) { ip++; break; }
                        ip++;
                        while (ip < script.size() && isdigit((unsigned char)script[ip])) ip++;
                        continue;
                    }
                    if (script[ip] == '|')
                    {
                        ip++; break;
                    }
                    ip++;
                }
                continue;
            }
        }
        else if (cmd == '|')
        {
        }
        else if (cmd == '=')
        {
            if (ip + 1 < script.size() && script[ip + 1] == '(')
            {
                ip += 2;
                int n = 0;
                while (ip < script.size() && isdigit((unsigned char)script[ip]))
                {
                    n = n * 10 + (script[ip] - '0'); ip++;
                }
                vars[n] = tilde;
            }
            else if (ip + 1 < script.size() && script[ip + 1] == ')')
            {
                ip += 2;
                int n = 0;
                while (ip < script.size() && isdigit((unsigned char)script[ip]))
                {
                    n = n * 10 + (script[ip] - '0'); ip++;
                }
                vars.erase(n);
            }
            else
            {
                ip++;
                if (ip < script.size() && isdigit((unsigned char)script[ip]))
                {
                    int n = script[ip] - '0';
                    vars[n] = tilde;
                }
            }
        }
        else if (cmd == '@')
        {
            ip++;
            if (ip < script.size() && isdigit((unsigned char)script[ip]))
            {
                int n = script[ip] - '0';
                if (vars.count(n))
                    st.push(vars[n]);
            }
        }
        else if (cmd == '&')
        {
            ip++;
            if (ip < script.size())
            {
                char op = script[ip];
                Stack temp;
                vector<Data> all;
                while (!st.empty())
                {
                    all.push_back(st.get());
                    temp.push(st.get());
                    st.pop();
                }
                if (all.size() >= 2)
                {
                    Data bottom = all.back(); all.pop_back();
                    Data second = all.back(); all.pop_back();
                    Data result = 0;
                    if (op == '+') result = second + bottom;
                    else if (op == '-') result = second - bottom;
                    else if (op == '*') result = second * bottom;
                    else if (op == '/')
                    {
                        if (bottom != 0) result = second / bottom;
                        else result = 0;
                    }
                    else if (op == '%')
                    {
                        if (bottom != 0) result = second % bottom;
                        else result = 0;
                    }
                    else result = second;
                    all.push_back(result);
                }
                for (auto it = all.rbegin(); it != all.rend(); ++it)
                    st.push(*it);
            }
        }
        else if (cmd == '#')
        {
            break;
        }
        else if (cmd == '_')
        {
            if (inputPos < input.size())
            {
                char ch = input[inputPos++];
                Stack helper;
                while (!st.empty())
                {
                    helper.push(st.get());
                    st.pop();
                }
                st.push((Data)ch);
                while (!helper.empty())
                {
                    st.push(helper.get());
                    helper.pop();
                }
            }
        }
        else if (cmd == '$')
        {
            ip++;
            int N = 0;
            while (ip < script.size() && isdigit((unsigned char)script[ip]))
            {
                N = N * 10 + (script[ip] - '0');
                ip++;
            }
            if (N <= 0) N = 1;
            uniform_int_distribution<int> dist(1, N);
            int r = dist(rng);
            st.push(r);
            continue;
        }
        else if (cmd == '^')
        {
            cout << "\x1B[2J\x1B[H";
        }
        else if (cmd == ';')
        {
            ip++;
            int N = 0;
            while (ip < script.size() && isdigit((unsigned char)script[ip]))
            {
                N = N * 10 + (script[ip] - '0');
                ip++;
            }
            if (N > 0)
                this_thread::sleep_for(chrono::seconds(N));
            continue;
        }
        else if (cmd == '.')
        {
            if (inputPos < input.size())
                st.push((Data)input[inputPos++]);
        }

        ip++;
    }

    cout << "\nFinal stack state:\n";
    while (!st.empty())
    {
        cout << (char)st.get() << "\n";
        st.pop();
    }

    return 0;
}