#include "graph.h"

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

void check(bool condition, const char *message)
{
    if (!condition)
        throw runtime_error(message);
}

int main()
{
    try
    {
        Graph<int, string> graph(3);
        const GridVertex a{0, 0}, b{0, 1}, c{0, 2};

        // проверка добавления рёбер, их направление и пометки
        graph.setVertexLabel(a, "начало");
        check(graph.addEdge(a, b, 7), "Не удалось добавить ребро");
        check(!graph.addEdge(a, b, 8), "Граф принял повторное ребро");
        check(!graph.hasEdge(b, a), "Обнаружено лишнее обратное ребро");

        graph.setEdgeLabel(a, b, 9);
        check(graph.edgeLabel(a, b) == 9, "Неверная пометка ребра");

        graph.addEdge(a, c);
        vector<GridVertex> neighbors;
        for (const auto &neighbor : graph.neighbors(a))
            neighbors.push_back(neighbor);

        check(neighbors == vector<GridVertex>{b, c}, "Неверный список соседей");
        check(graph.removeEdge(a, c) && !graph.hasEdge(a, c), "Ребро не удалено");

        // проверка удаления и восстановления вершин
        graph.addEdge(b, c);
        check(graph.removeVertex(b), "Вершина не удалена");
        check(!graph.hasVertex(b) && !graph.hasEdge(a, b),
              "Вершина или её входящее ребро остались в графе");
        check(graph.vertexLabels().size() == 2, "Неверное количество пометок вершин");
        check(graph.addVertex(b, "середина"), "Не удалось восстановить вершину");
        check(!graph.hasEdge(b, c), "После восстановления осталось старое исходящее ребро");

        // проверка сохранения рёбер и пометок при изменении размера
        graph.resize(2, 3);
        const GridVertex retained{1, 1};
        graph.addEdge(a, retained, 4);
        graph.addEdge(a, c);
        graph.resize(2, 2);

        check(graph.rows() == 2 && graph.columns() == 2, "Неверный размер сетки");
        check(graph.hasEdge(a, retained) && !graph.hasEdge(a, c),
              "Неверный набор рёбер после изменения размера");

        const auto labels = graph.vertexLabels();
        check(labels.get(0) == "начало" && labels.get(1) == "середина",
              "Неверные пометки вершин");

        // проверка чтения графа из потока
        istringstream valid("2 1 верх низ 1 0 0 1 0 42");
        check(static_cast<bool>(valid >> graph), "Не удалось прочитать граф");
        check(graph.vertexLabel({1, 0}) == "низ", "Неверная пометка вершины после чтения");
        check(graph.edgeLabel(a, {1, 0}) == 42, "Неверная пометка ребра после чтения");

        istringstream invalid("1 1 вершина 1 0 0 0 1 5");
        check(!(invalid >> graph), "Приняты некорректные входные данные");
        check(graph.edgeLabel(a, {1, 0}) == 42, "Некорректный ввод изменил граф");
    }
    catch (const exception &error)
    {
        cerr << error.what() << '\n';
        return 1;
    }
    return 0;
}