#include <iostream>
#include <string>
#include "queue.h"
using namespace std;

const int count = 26;
bool visited[count] = { false };
bool neighbors[count][count] = { false };
int ascii = 'A';

int main()
{
    setlocale(LC_ALL, "rus");
    char initial_elem, elem, final_elem;
    string sign_trans;
    int count_trans;
    int check = 0;
    Queue* queue = queue_create();
    cout << "Введите начальный элемент: ";
    cin >> initial_elem;
    visited[initial_elem - ascii] = true;
    cout << "Введите количество превращений: ";
    cin >> count_trans;
    queue_insert(queue, initial_elem);
    system("cls");
    cout << "Введите желаемые превращения(использовать знак '->' для работы программы): " << endl;
    while (count_trans) {
        cin >> elem >> sign_trans >> final_elem;
        if (sign_trans != "->") {
            cout << "Неверный ввод знака преващений!" << endl;
        }
        else {
            neighbors[elem - ascii][final_elem - ascii] = true;
            count_trans--;
        }   
    }
    cout << endl;
    while (!queue_empty(queue)) {
        char current = queue_get(queue);
        queue_remove(queue);
        for (int i = 0; i < count; i++) {
            if (!visited[i] && neighbors[current - ascii][i]) {
                visited[i] = true;
                queue_insert(queue, i + ascii);
            }
        }
    }
    cout << "Превращения из начального элемента: " << endl;
    for (int i = 0; i < count; i++) {
        if (visited[i]) {
            cout << char(i + ascii) << endl;
        }
    }
    queue_delete(queue);
    return 0;
}
