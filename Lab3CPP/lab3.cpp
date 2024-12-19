#include <iostream>
#include <fstream>
#include <string>
#include "vector.h"
#include "queue.h"

using namespace std;

int main(int argc, char** argv) {
    // Проверка наличия входного файла
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }

    ifstream input(argv[1]);
    if (!input.is_open()) {
        cerr << "Failed to open the input file." << endl;
        return 1;
    }

    // Считываем максимальный размер очереди
    size_t max_size;
    input >> max_size;

    Queue* queue = queue_create(); // Создаём очередь
    size_t current_size = 0;       // Текущий размер очереди

    string command;
    while (input >> command) {
        if (command == "ADD") {
            int value;
            input >> value;
            if (current_size >= max_size) {
                cout << "INVALID ADD" << endl; // Очередь переполнена
            } else {
                queue_insert(queue, value);   // Добавляем элемент в очередь
                current_size++;
            }
        } else if (command == "GET") {
            if (queue_empty(queue)) {
                cout << "INVALID GET" << endl; // Очередь пуста
            } else {
                cout << queue_get(queue) << endl; // Получаем первый элемент
                queue_remove(queue);             // Удаляем первый элемент
                current_size--;
            }
        }
    }

    // Вывод оставшихся элементов в очереди
    cout << "QUEUE" << endl;
    while (!queue_empty(queue)) {
        cout << queue_get(queue) << endl;
        queue_remove(queue);
    }

    // Удаляем очередь и закрываем файл
    queue_delete(queue);
    input.close();

    return 0;
}
