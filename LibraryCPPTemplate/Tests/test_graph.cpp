#include <iostream>
#include <cassert>
#include <string>
#include "graph.h"

using namespace std;

#define CHECK(cond, msg)
    do {
        if (!(cond)) {
            cout << "ОШИБКА: " << msg << endl; 
            return 1;
        }
    } while(0)

int main() {
    cout << "Начало тестирования графа" << endl;

    Graph<string, int> g(3, 3);
    CHECK(g.rows() == 3, "количество строк должно быть 3");
    CHECK(g.cols() == 3, "количество столбцов должно быть 3");
    CHECK(g.size() == 9, "общее количество вершин должно быть 9");
    cout << "Тест 1: Пройден" << endl;

    string names[] = { "A", "B", "C", "D", "E", "F", "G", "H", "I" };
    for (size_t i = 0; i < 9; i++) {
        g.set_vershina_label(i, names[i]);
    }

    CHECK(g.get_vershina_label(4) == "E", "метка вершины 4 должна быть 'E'");
    CHECK(g.poisk_vershina("F") == 5, "вершина 'F' должна быть под индексом 5");
    cout << "Тест 2: Пройден" << endl;

    g.add_rebro(4, 1, 10);
    g.add_rebro(4, 5, 20);
    g.add_rebro(4, 7, 30);
    g.add_rebro(4, 3, 40);

    CHECK(g.has_rebro(4, 1) == true, "ребро 4->1 должно существовать");
    CHECK(g.get_rebro_label(4, 1) == 10, "вес ребра 4->1 должен быть 10");
    CHECK(g.has_rebro(1, 4) == false, "ребро 1->4 не должно существовать");

    try {
        g.add_rebro(4, 8, 50);
        return 1;
    }
    catch (const invalid_argument&) {
    }
    cout << "Тест 3: Пройден" << endl;

    size_t expected_neighbors[] = { 3, 5, 1, 7 };
    int kolvo = 0;
    for (auto i = g.begin(4); i != g.end(4); i++) {
        CHECK(kolvo < 4, "вернулось слишком много соседей");
        CHECK(*i == expected_neighbors[kolvo], "неожиданный сосед из итератора");
        kolvo++;
    }
    CHECK(kolvo == 4, "должно быть найдено 4 соседа");
    cout << "Тест 4: Пройден" << endl;

    g.remove_rebro(4, 1);
    CHECK(g.has_rebro(4, 1) == false, "ребро 4->1 должно быть удалено");

    kolvo = 0;
    for (auto i = g.begin(4); i != g.end(4); i++) {
        kolvo++;
    }
    CHECK(kolvo == 3, "после удаления ребра должно остаться 3 соседа");
    cout << "Тест 5: Пройден" << endl;

    g.resize(4, 3);
    CHECK(g.rows() == 4, "после resize количество строк должно быть 4");
    CHECK(g.cols() == 3, "после resize количество столбцов должно быть 3");
    CHECK(g.size() == 12, "после resize общее количество вершин должно быть 12");
    CHECK(g.get_vershina_label(4) == "E", "метка вершины 4 должна сохраниться после resize");
    CHECK(g.has_rebro(4, 5) == true, "ребро 4->5 должно сохраниться после resize");

    cout << "Тест 6: Пройден" << endl;
    cout << "Все тесты пройдены!" << endl;

    return 0;
}