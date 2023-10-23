#include "stack.h"
#include "list.h"
#include <iostream>

using namespace std;

int main() {

    setlocale(LC_ALL, "ru");

    Stack* stack = stack_create();

    int N;
    cout << "Введите число частиц: ";
    cin >> N;

    for (int i = 0; i < N; i++) {
        int position;
        char charge;
        cout << "Введите координату и заряд " << (i + 1) << "-й частицы (например, 4 +): ";
        cin >> position >> charge;

        if (charge == '+') {
            stack_push(stack, position);
        }
        else if (charge == '-' && !stack_empty(stack)) {
            cout << "Столкновение: " << stack_get(stack) << " и " << position << endl;
            stack_pop(stack);
        }
    }

    stack_delete(stack);
    return 0;
}