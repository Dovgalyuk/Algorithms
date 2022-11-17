#include <iostream>
#include <string>
#include "queue.h"
using namespace std;

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
    cout << "Введите количество превращений: ";
    cin >> count_trans;
    queue_insert(queue, initial_elem);
    system("cls");
    cout << "Введите желаемые превращения(использовать знак '->' для работы программы): " << endl;
    while (check != count_trans) {
        cin >> elem >> sign_trans >> final_elem;
        if (sign_trans != "->") {
            cout << "Неверный ввод знака преващений!" << endl;
        }
        else {
            if (initial_elem == elem) {
                queue_insert(queue, final_elem);
            }
            else if (queue_get(queue) == elem) {
                queue_insert(queue, final_elem);
            }
            check++;
        }
    }
    cout << "Превращения из начального элемента: " << endl;
    while (queue_get(queue) != initial_elem) {
        cout << queue_get(queue) << endl;
        queue_remove(queue);
    }
    queue_delete(queue);
}
