#include <iostream>
#include "stack.h"
#include "vector.h"
#include <string>
#include <math.h>

using namespace std;

int step(int s) {
    int num = 1;
    while (s > 0) {
        num = num * 10;
        s--;
    };
    return(num);
}

int main() {
    string primer;
    int size = 0;
    cout << "Input primer: ";
    getline(cin, primer);
    Stack* sta = stack_create();
    Stack* Stanly = stack_create();
    int masdig[200]; int sizedig = 0;
    int sizezna = 0;
    for (int i = 0; i < primer.size(); i++) {
        if (isdigit(primer[i])) {
            int kol = 0; int j = i;
            while (isdigit(primer[j])) {
                j++;
            }
            int time = primer[i] - '0';
            masdig[sizedig] = time;
            for (int r = 1; r < j - i; r++) {
                masdig[sizedig] = masdig[sizedig] * 10 + (primer[i + r] - '0');
            }
            i = j - 1;
            stack_push(sta, masdig[sizedig]);
            sizedig++;
        }
        else if (!isdigit(primer[i])) {
            if (stack_empty(Stanly) == 0) {
                stack_push(Stanly, primer[i]);
                sizezna++;
            }
            else if ((stack_get(Stanly) == '*' || stack_get(Stanly) == '/' || stack_get(Stanly) == '-')) {
                if (stack_get(Stanly) == '*') {
                    int a = stack_get(sta);
                    stack_pop(sta);
                    int b = stack_get(sta);
                    stack_pop(sta);
                    sizedig--;
                    stack_push(sta, a * b);
                    stack_pop(Stanly);
                    stack_push(Stanly, primer[i]);
                }
                else if (stack_get(Stanly) == '/') {
                    int a = stack_get(sta);
                    stack_pop(sta);
                    int b = stack_get(sta);
                    stack_pop(sta);
                    sizedig--;
                    stack_push(sta, b / a);
                    stack_pop(Stanly);
                    stack_push(Stanly, primer[i]);
                }
                else if (stack_get(Stanly) == '-') {
                    stack_pop(Stanly);
                    stack_push(Stanly, '+');
                    int a = stack_get(sta);
                    stack_pop(sta);
                    stack_push(sta, -a);
                    stack_push(Stanly, primer[i]);
                    sizezna++;
                }
            }
            else {
                stack_push(Stanly, primer[i]);
                sizezna++;
            }
        }
    }
    for (int i = 0; i < sizezna; i++) {
        int a = stack_get(sta);
        stack_pop(sta);
        int b = stack_get(sta);
        stack_pop(sta);
        sizedig--;
        if (stack_get(Stanly) == '+') {
            stack_push(sta, a + b);
        }
        else if (stack_get(Stanly) == '*') {
            stack_push(sta, b * a);
        }
        else if (stack_get(Stanly) == '/') {
            stack_push(sta, b / a);
        }
        else if (stack_get(Stanly) == '-') {
            stack_push(sta, b - a);
        }
        stack_pop(Stanly);
    }
    cout << "\nOtvet:" << stack_get(sta);
    stack_delete(sta);
    stack_delete(Stanly);
    return 0;
}