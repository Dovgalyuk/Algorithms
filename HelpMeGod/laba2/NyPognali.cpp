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
    int masdig[200]; int sizedig = 0;
    char maszna[199]; int sizezna = 0;
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
            sizedig++;
        }
        else {
            maszna[sizezna] = primer[i];
            sizezna++;
        }
    }
    for (int i = 0; i < sizezna; i++) {
        if (maszna[i] == '*') {
            masdig[i + 1] = masdig[i] * masdig[i + 1];
            masdig[i] = -1;
            maszna[i] = '1';
            stack_push(sta, masdig[i + 1]);
        }
        if (maszna[i] == '/') {
            masdig[i + 1] = masdig[i] / masdig[i + 1];
            masdig[i] = -1;
            maszna[i] = '1';
            stack_push(sta, masdig[i + 1]);
        }
    }
    for (int i = 0; i < sizezna; i++) {
        if (maszna[i] == '+') {
            int o = i + 1;
            while (masdig[o] == -1) {
                o++;
            }
            masdig[o] = masdig[i] + masdig[o];
            masdig[i] = -1;
            maszna[i] = '1';
            stack_push(sta, masdig[i + 1]);
        }
        if (maszna[i] == '-') {
            int o = i + 1;
            while (masdig[o] == -1) {
                o++;
            }
            masdig[o] = masdig[i] - masdig[o];
            masdig[i] = -1;
            maszna[i] = '1';
            stack_push(sta, masdig[i + 1]);
        }
    }
    stack_push(sta, masdig[sizedig - 1]);
    cout << "\nOtvet:" << stack_get(sta);
    stack_delete(sta);
    return 0;
}