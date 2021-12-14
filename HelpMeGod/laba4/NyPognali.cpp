#include <iostream>
#include "graph.h"

using namespace std;

struct Z {
    int length;
    int status;
};

DirectedGraph<Z, int>* createGraph(int vershiniKol, int rebraKol) {
    auto* graphTemp = new DirectedGraph<Z, int>(vershiniKol);
    for (int i = 0; i < vershiniKol; ++i) {
        graphTemp->getVershina(i)->data.length = 2147483647;
        graphTemp->getVershina(i)->data.status = 0;
    }
    cout << "Input rebra(from rebro, to rebro, length of this rebro):";
    for (int i = 0; i < rebraKol; ++i) {
        int from, to, length;
        std::cin >> from >> to >> length;
        graphTemp->setRebro(graphTemp->getVershina(from - 1), graphTemp->getVershina(to - 1), length);
    }
    return graphTemp;
}

auto findVershina(DirectedGraph<Z, int>* graph, int* startVershina) {
    cout << "Input start vershina: ";
    cin >> *startVershina;
    auto iteratorVershini = graph->getVershinaIterator();
    for (int i = 0; i < *startVershina - 1; i++) {
        iteratorVershini++;
    }
    return iteratorVershini;
}

void outputBeautifulOtvet(int startVershina, int vershiniKol, DirectedGraph<Z, int>* graph) {
    cout << "\nPaths from vershina " << startVershina << " to others:\n";
    int numbering = 1;
    for (int i = 0; i < vershiniKol; i++) {
        if (graph->getVershina(i)->data.status == 2 && i + 1 != startVershina) {
            cout << numbering << ") " << startVershina << " -> " << i + 1 << " = " << graph->getVershina(i)->data.length << "\n";
            numbering++;
        }
    }
}

int findingNeighborsOfVershina(int workingVershina, int vershiniKol, DirectedGraph<Z, int>* graph) {
    int length = graph->getVershina(workingVershina - 1)->data.length;
    graph->getVershina(workingVershina - 1)->data.status = 2;
    auto iteratorReber = graph->getRebroVershiniIterator(graph->getVershina(workingVershina - 1));
    while (*iteratorReber) {
        if ((*iteratorReber)->to->data.length > length + (*iteratorReber)->data) {
            (*iteratorReber)->to->data.length = length + (*iteratorReber)->data;
            (*iteratorReber)->to->data.status = 1;
        }
        iteratorReber++;
    }
    return 0;
}

int toTheNextVershina(int vershiniKol, int startVershina, int* workingVershina, bool* ending, DirectedGraph<Z, int>* graph) {
    int counter = 0;
    int minZnachenieData = 2147483647;
    int minCounter = 0;
    for (int i = 0; i < vershiniKol; ++i) {
        if (graph->getVershina(i)->data.status == 1 && minZnachenieData > graph->getVershina(i)->data.length) {
            minZnachenieData = graph->getVershina(i)->data.length;
            minCounter = i;
        }
        if (graph->getVershina(i)->data.status != 1) {
            counter++;
        }
    }
    if (counter >= vershiniKol) {
        outputBeautifulOtvet(startVershina, vershiniKol, graph);
        *ending = false;
    }
    else {
        *workingVershina = minCounter + 1;
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
    graph->getVershina(startVershina - 1)->data.length = 0;
    workingVershina = startVershina;

    // Searching using Dijkstra's algorithm
    bool ending = true;
    while (ending) {
        findingNeighborsOfVershina(workingVershina, vershiniKol, graph);
        toTheNextVershina(vershiniKol, startVershina, &workingVershina, &ending, graph);
    }

    // Deleting everything
    graph->~DirectedGraph();
    delete graph;
    return 0;
}


