#include <iostream>
#include "graph.h"

using namespace std;

int main() {
    int amount = 10;
    auto graph = Graph<int>(amount);

    for (int i = 0; i < graph.getVershinaSum(); i++) {
        graph.getVershina(i)->data.length = i;
        if (graph.getVershina(i)->data.length != i) {
            cout << "Adding a vershina to the graph does not work correctly.";
            return 0;
        }
    }

    graph.getVershina(9)->data.length = 15;

    if (graph.getVershina(9)->data.length != 15) {
        cout << "Modifying the vertex data does not work correctly.";
        return 0;
    }

    graph.removeVershina(9);

    if (graph.getVershina(9) != NULL) {
        cout << "Deleting a vershina from the graph does not work correctly.";
        return 0;
    }

    graph.removeVershina(4);

    if (graph.getVershina(4)->data.length != 5) {
        cout << "Deleting a vershina from the graph does not work correctly.";
        return 0;
    }

    graph.setRebro(graph.getVershina(1), graph.getVershina(2), 10);

    if (!graph.containsRebroBetweenVershina(graph.getVershina(1), graph.getVershina(2))) {
        cout << "Adding a edge to the graph does not work correctly.";
        return 1;
    }

    if (graph.getRebro(graph.getVershina(1), graph.getVershina(2))->data != 10) {
        cout << "Modifying the rebro data does not work correctly.";
        return 0;
    }

    graph.getRebro(graph.getVershina(1), graph.getVershina(2))->data = 17;

    if (graph.getRebro(graph.getVershina(1), graph.getVershina(2))->data != 17) {
        cout << "Modifying the rebro data does not work correctly.";
        return 0;
    }

    graph.removeRebro(graph.getVershina(1), graph.getVershina(2));

    if (graph.containsRebroBetweenVershina(graph.getVershina(1), graph.getVershina(2))) {
        cout << "Deleting a rebro from the graph does not work correctly.";
        return 0;
    }

    graph.setRebro(graph.getVershina(0), graph.getVershina(1), 1);
    graph.setRebro(graph.getVershina(0), graph.getVershina(3), 7);
    graph.setRebro(graph.getVershina(1), graph.getVershina(7), 4);
    graph.setRebro(graph.getVershina(3), graph.getVershina(0), 29);
    graph.setRebro(graph.getVershina(3), graph.getVershina(4), 69);

    auto iteratorReber = graph.getRebroVershiniIterator(graph.getVershina(0));
    int check = 0;
    while (*iteratorReber) {
        check++;
        iteratorReber++;
    }

    if (check != 2) {
        cout << "The vershina iterator does not work correctly.";
        return 1;
    }

    auto iteratorVershini = graph.getVershinaIterator();
    for (int i = 0; i < 5; i++) {
        iteratorVershini++;
    }

    if (*iteratorVershini != graph.getVershina(5)) {
        cout << "Iterator vershini does not work correctly.";
        return 1;
    }

    return 0;
}