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
                kol++;
                j++;
            }
            int time = primer[i] - '0';
            masdig[sizedig] = time * step(kol - 1);
            kol--;
            for (int r = 1; r < j - i; r++) {
                masdig[sizedig] = masdig[sizedig] + (primer[i + r] - '0') * step(kol - 1);
                kol--;
            }
            i = j - 1;
            stack_push(sta, masdig[sizedig]);
            sizedig++;
        }
        if (!isdigit(primer[i])) {
            stack_push(Stanly, primer[i]);
            sizezna++;
            if (stack_get(Stanly) == '*' || stack_get(Stanly) == '/') {
                i++;
                int kol = 0; int j = i;
                while (isdigit(primer[j])) {
                    kol++;
                    j++;
                }
                int time = primer[i] - '0';
                masdig[sizedig] = time * step(kol - 1);
                kol--;
                for (int r = 1; r < j - i; r++) {
                    masdig[sizedig] = masdig[sizedig] + (primer[i + r] - '0') * step(kol - 1);
                    kol--;
                }
                i = j - 1;
                stack_push(sta, masdig[sizedig]);
                sizedig++;
                if (stack_get(Stanly) == '*') {
                    int a = stack_get(sta);
                    stack_pop(sta);
                    int b = stack_get(sta);
                    stack_pop(sta);
                    sizedig--;
                    stack_push(sta, a * b);
                    sizezna--;
                    stack_pop(Stanly);
                }
                if (stack_get(Stanly) == '/') {
                    int a = stack_get(sta);
                    stack_pop(sta);
                    int b = stack_get(sta);
                    stack_pop(sta);
                    sizedig--;
                    stack_push(sta, b / a);
                    sizezna--;
                    stack_pop(Stanly);
                }
            }
            if (stack_get(Stanly) == '-') {
                stack_pop(Stanly);
                stack_push(Stanly, '+');
                i++;
                int kol = 0; int j = i;
                while (isdigit(primer[j])) {
                    kol++;
                    j++;
                }
                int time = primer[i] - '0';
                masdig[sizedig] = time * step(kol - 1);
                kol--;
                for (int r = 1; r < j - i; r++) {
                    masdig[sizedig] = masdig[sizedig] + (primer[i + r] - '0') * step(kol - 1);
                    kol--;
                }
                i = j - 1;
                stack_push(sta, masdig[sizedig] * -1);
                sizedig++;
            }
        }
    }
    for (int i = 0; i < sizezna; i++) {
        if (stack_get(Stanly) == '+') {
            int a = stack_get(sta);
            stack_pop(sta);
            int b = stack_get(sta);
            stack_pop(sta);
            sizedig--;
            stack_push(sta, a + b);
            stack_pop(Stanly);
        }
    }
    cout << "\nOtvet:" << stack_get(sta);
    stack_delete(sta);
    stack_delete(Stanly);
    return 0;
}