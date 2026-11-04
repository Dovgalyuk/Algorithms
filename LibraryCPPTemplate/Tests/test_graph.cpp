#include <iostream>
#include <string>
#include "graph.h"

using namespace std;

int main() {
    cout << "Начало тестирования графа" << endl;

    Graph<string, int> g(3, 3);
    if (g.rows() != 3) { 
        cout << "ОШИБКА: количество строк должно быть 3" << endl; 
        return 1; 
    }
    if (g.cols() != 3) { 
        cout << "ОШИБКА: количество столбцов должно быть 3" << endl; 
        return 1; 
    }
    if (g.size() != 9) { 
        cout << "ОШИБКА: общее количество вершин должно быть 9" << endl; 
        return 1; 
    }
    cout << "Тест 1: Пройден" << endl;

    string names[] = { "A", "B", "C", "D", "E", "F", "G", "H", "I" };
    for (size_t i = 0; i < 9; i++) {
        g.set_vershina_label(i, names[i]);
    }

    if (g.get_vershina_label(4) != "E") { 
        cout << "ОШИБКА: метка вершины 4 должна быть 'E'" << endl; 
        return 1; 
    }
    if (g.poisk_vershina("F") != 5) { 
        cout << "ОШИБКА: вершина 'F' должна быть под индексом 5" << endl; 
        return 1; 
    }
    cout << "Тест 2: Пройден" << endl;

    g.add_rebro(4, 1, 10);
    g.add_rebro(4, 5, 20);
    g.add_rebro(4, 7, 30);
    g.add_rebro(4, 3, 40);

    if (!g.has_rebro(4, 1)) { 
        cout << "ОШИБКА: ребро 4->1 должно существовать" << endl; 
        return 1; 
    }
    if (g.get_rebro_label(4, 1) != 10) { 
        cout << "ОШИБКА: вес ребра 4->1 должен быть 10" << endl; 
        return 1; 
    }
    if (g.has_rebro(1, 4)) { cout << "ОШИБКА: ребро 1->4 не должно существовать" << endl; 
    return 1; 
    }

    try {
        g.add_rebro(4, 8, 50);
        cout << "ОШИБКА: ожидалось исключение для несоседних вершин" << endl;
        return 1;
    }
    catch (const invalid_argument&) {
    }
    cout << "Тест 3: Пройден" << endl;

    size_t expected_neighbors[] = { 3, 5, 1, 7 };
    int kolvo = 0;
    for (auto i = g.begin(4); i != g.end(4); i++) {
        if (kolvo >= 4) { 
            cout << "ОШИБКА: итератор вернул слишком много соседей" << endl; 
            return 1; 
        }
        if (*i != expected_neighbors[kolvo]) { 
            cout << "ОШИБКА: неожиданный сосед из итератора" << endl; 
            return 1; 
        }
        kolvo++;
    }
    if (kolvo != 4) { 
        cout << "ОШИБКА: должно быть найдено 4 соседа" << endl; 
        return 1; 
    }
    cout << "Тест 4: Пройден" << endl;

    g.remove_rebro(4, 1);
    if (g.has_rebro(4, 1)) { 
        cout << "ОШИБКА: ребро 4->1 должно быть удалено" << endl; 
        return 1; 
    }

    kolvo = 0;
    for (auto i = g.begin(4); i != g.end(4); i++) {
        kolvo++;
    }
    if (kolvo != 3) { 
        cout << "ОШИБКА: после удаления ребра должно остаться 3 соседа" << endl; 
        return 1; 
    }
    cout << "Тест 5: Пройден" << endl;

    g.resize(4, 3);
    if (g.rows() != 4) { 
        cout << "ОШИБКА: после resize количество строк должно быть 4" << endl; 
        return 1; 
    }
    if (g.cols() != 3) { 
        cout << "ОШИБКА: после resize количество столбцов должно быть 3" << endl; 
        return 1; 
    }
    if (g.size() != 12) { 
        cout << "ОШИБКА: после resize общее количество вершин должно быть 12" << endl; 
        return 1; 
    }
    if (g.get_vershina_label(4) != "E") { 
        cout << "ОШИБКА: метка вершины 4 должна сохраниться после resize" << endl; 
        return 1; 
    }
    if (!g.has_rebro(4, 5)) { 
        cout << "ОШИБКА: ребро 4->5 должно сохраниться после resize" << endl; 
        return 1; 
    }

    cout << "Тест 6 (Изменение размерности): Пройден" << endl;
    cout << "Все тесты пройдены!" << endl;

    return 0;
}