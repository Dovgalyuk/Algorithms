#include <iostream>
#include "graph.h"

using namespace std;

DirectedGraph<int, int>* createGraph(int vershiniKol, int rebraKol) {
    auto* graphTemp = new DirectedGraph<int, int>(vershiniKol);
    for (int i = 0; i < vershiniKol; ++i) {
        graphTemp->getVershina(i)->data = 2147483647;
        graphTemp->getVershina(i)->status = 0;
    }
    cout << "Input rebra(from rebro, to rebro, length of this rebro):";
    for (int i = 0; i < rebraKol; ++i) {
        int from, to, length;
        std::cin >> from >> to >> length;
        graphTemp->setRebro(graphTemp->getVershina(from - 1), graphTemp->getVershina(to - 1), length);
    }
    return graphTemp;
}

auto findVershina(DirectedGraph<int, int>* graph, int* startVershina) {
    cout << "Input start vershina: ";
    cin >> *startVershina;
    auto iteratorVershini = graph->getVershinaIterator();
    for (int i = 0; i < *startVershina - 1; i++) {
        iteratorVershini++;
    }
    return iteratorVershini;
}

void outputBeautifulOtvet(int startVershina, int vershiniKol, DirectedGraph<int, int>* graph) {
    cout << "\nPaths from vershina " << startVershina << " to others:\n";
    int numbering = 1;
    for (int i = 0; i < vershiniKol; i++) {
        if (graph->getVershina(i)->status == 2 && i + 1 != startVershina) {
            cout << numbering << ") " << startVershina << " -> " << i + 1 << " = " << graph->getVershina(i)->data << "\n";
            numbering++;
        }
    }
}

int findingNeighborsOfVershina(int workingVershina, int vershiniKol, DirectedGraph<int, int>* graph) {
    int length = graph->getVershina(workingVershina - 1)->data;
    graph->getVershina(workingVershina - 1)->status = 2;
    for (int i = 0; i < vershiniKol; i++) {
        if (graph->containsRebroBetweenVershina(graph->getVershina(workingVershina - 1), graph->getVershina(i)) &&
            graph->getVershina(i)->data > length + graph->getRebro(graph->getVershina(workingVershina - 1), graph->getVershina(i))->data) {
            graph->getVershina(i)->data = length + graph->getRebro(graph->getVershina(workingVershina - 1), graph->getVershina(i))->data;
            graph->getVershina(i)->status = 1;
        }
    }
    return 0;
}

int toTheNextVershina(int vershiniKol, int startVershina, int* workingVershina, bool* ending, DirectedGraph<int, int>* graph) {
    int counter = 0;
    while (counter < vershiniKol && graph->getVershina(counter)->status != 1) {
        counter++;
    }
    if (counter >= vershiniKol) {
        outputBeautifulOtvet(startVershina, vershiniKol, graph);
        *ending = false;
    }
    else {
        *workingVershina = counter + 1;
    }
    return 0;
}

int main() {
    // Creating graph
    // 6 9  1 2 7 1 3 9 1 6 14 2 3 10 2 4 15 3 6 2 3 4 11 4 5 6 6 5 9  1 
    int vershiniKol, rebraKol;
    cout << "Input a number of vershin: ";
    cin >> vershiniKol;
    cout << "Input a number of reber: ";
    cin >> rebraKol;
    auto* graph = createGraph(vershiniKol, rebraKol);

    // Getting ready to search
    int workingVershina, startVershina;
    auto iteratorVershini = findVershina(graph, &startVershina);
    graph->getVershina(startVershina - 1)->data = 0;
    workingVershina = startVershina;

    // Searching using Dijkstra's algorithm
    bool ending = true;
    while (ending) {
        findingNeighborsOfVershina(workingVershina, vershiniKol, graph);
        toTheNextVershina(vershiniKol, startVershina, &workingVershina, &ending, graph);
    }

    // Deleting everything
    return 0;
}


