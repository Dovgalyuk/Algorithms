#include <iostream>
#include <fstream>
#include "stack.h"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 2) return 1;

    ifstream fin(argv[1]);
    if (!fin.is_open()) return 1;

    int n = 0;
    if (!(fin >> n)) {
        return 1;
    }

    Stack *stack = stack_create();
    int count = 0;

    for (int i = 0; i < n; ++i)
    {
        int coord = 0;
        char charge = 0;
        if (!(fin >> coord >> charge))
            break;

        if (charge == '+')
        {
            stack_push(stack, (Data)coord);
        }
        else if (charge == '-')
        {
            if (!stack_empty(stack))
            {
                Data plus_coord = stack_get(stack);
                stack_pop(stack);
                cout << (int)plus_coord << " " << coord << "\n";
                count++;
            }
        }
    }

    cout << "Total: " << count << "\n";

    stack_delete(stack);
    fin.close();
    return 0;
}