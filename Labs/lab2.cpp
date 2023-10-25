#include "stack.h"
#include <iostream>

using namespace std;

int main() {
    setlocale(LC_ALL, "ru");
    Stack* stack = stack_create();

    int N;
    cout << "������� ���������� ������: ";
    cin >> N;

    for (int i = 0; i < N; i++) {
        int position;
        char charge;
        cout << "������� ���������� � ����� " << (i + 1) << "-� ������� (��������, 4 +): ";
        cin >> position >> charge;

        if (charge == '+') {
            stack_push(stack, position);
        }
        else {
            if (!stack_empty(stack)) {
                int topPosition = stack_get(stack);
                cout << "������������: " << topPosition << " � " << position << endl;
                stack_pop(stack);
            }
        }
    }

    stack_delete(stack);
    return 0;
}