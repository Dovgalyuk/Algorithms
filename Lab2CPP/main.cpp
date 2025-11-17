#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "stack.h"
using namespace std;

int main()
{
    vector<string> prog;
    string line;
    while (getline(cin, line))
    {
        if (!line.empty())
            prog.push_back(line);
    }

    Stack* st = stack_create();
    Stack* flags = stack_create();
    int vars[4] = { 0, 0, 0, 0 };
    int size = 0;

    vector<int> calls;

    size_t ip = 0;
    bool error = false;

    while (ip < prog.size() && !error)
    {
        istringstream iss(prog[ip]);
        string op;
        iss >> op;
        if (!iss)
        {
            cout << "error\n";
            error = true;
            break;
        }

        if (op == "bipush")
        {
            int x;
            iss >> x;
            stack_push(st, x);
            stack_push(flags, 0);
            size++;
            ip++;
        }
        else if (op == "pop")
        {
            if (size == 0)
            {
                cout << "error\n";
                error = true;
            }
            else
            {
                int t = stack_get(flags);
                stack_pop(flags);
                stack_pop(st);
                size--;

                if (t == 1)
                {
                    cout << "error\n";
                    error = true;
                }
                else
                    ip++;
            }
        }
        else if (op == "iadd" || op == "isub" || op == "imul" ||
            op == "iand" || op == "ior" || op == "ixor")
        {
            if (size < 2)
            {
                cout << "error\n";
                error = true;
            }
            else
            {
                int t1 = stack_get(flags);
                int v1 = stack_get(st);
                stack_pop(flags);
                stack_pop(st);

                int t2 = stack_get(flags);
                int v2 = stack_get(st);
                stack_pop(flags);
                stack_pop(st);
                size -= 2;

                if (t1 == 1 || t2 == 1)
                {
                    cout << "error\n";
                    error = true;
                }
                else
                {
                    int r = 0;
                    if (op == "iadd")      r = v2 + v1;
                    else if (op == "isub") r = v2 - v1;
                    else if (op == "imul") r = v2 * v1;
                    else if (op == "iand") r = v2 & v1;
                    else if (op == "ior")  r = v2 | v1;
                    else if (op == "ixor") r = v2 ^ v1;

                    stack_push(st, r);
                    stack_push(flags, 0);
                    size++;
                    ip++;
                }
            }
        }
        else if (op == "swap")
        {
            if (size < 2)
            {
                cout << "error\n";
                error = true;
            }
            else
            {
                int t1 = stack_get(flags);
                int v1 = stack_get(st);
                stack_pop(flags);
                stack_pop(st);

                int t2 = stack_get(flags);
                int v2 = stack_get(st);
                stack_pop(flags);
                stack_pop(st);

                stack_push(st, v1);
                stack_push(flags, t1);
                stack_push(st, v2);
                stack_push(flags, t2);

                ip++;
            }
        }
        else if (op.rfind("iload_", 0) == 0)
        {
            int idx = op[op.size() - 1] - '0';
            stack_push(st, vars[idx]);
            stack_push(flags, 0);
            size++;
            ip++;
        }
        else if (op.rfind("istore_", 0) == 0)
        {
            if (size == 0)
            {
                cout << "error\n";
                error = true;
            }
            else
            {
                int t = stack_get(flags);
                int v = stack_get(st);
                stack_pop(flags);
                stack_pop(st);
                size--;

                if (t == 1)
                {
                    cout << "error\n";
                    error = true;
                }
                else
                {
                    int idx = op[op.size() - 1] - '0';
                    vars[idx] = v;
                    ip++;
                }
            }
        }
        else if (op == "invokestatic")
        {
            int addr;
            iss >> addr;

            int ret = (int)(ip + 1);
            stack_push(st, ret);
            stack_push(flags, 1);
            size++;

            calls.push_back(addr);
            ip = (size_t)addr;
        }
        else if (op == "return")
        {
            if (size == 0)
            {
                cout << "error\n";
                error = true;
            }
            else
            {
                int t = stack_get(flags);
                int v = stack_get(st);
                stack_pop(flags);
                stack_pop(st);
                size--;

                if (t != 1)
                {
                    cout << "error\n";
                    error = true;
                }
                else
                    ip = (size_t)v;
            }
        }
        else
        {
            cout << "error\n";
            error = true;
        }
    }

    if (!error)
    {
        if (!calls.empty())
        {
            cout << "calls:\n";
            for (size_t i = 0; i < calls.size(); i++)
                cout << calls[i] << "\n";
        }

        cout << "stack:\n";
        while (size > 0)
        {
            int t = stack_get(flags);
            int v = stack_get(st);
            (void)t;
            stack_pop(flags);
            stack_pop(st);
            size--;
            cout << v << "\n";
        }

        cout << "vars:\n";
        for (int i = 0; i < 4; i++)
            cout << vars[i] << "\n";
    }

    stack_delete(st);
    stack_delete(flags);
}