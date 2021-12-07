#include <iostream>
#include "graph.h"

using namespace std;

DirectedGraph<int, int>* createGraph(int vershiniKol, int rebraKol) {
    auto* graphTemp = new DirectedGraph<int, int>(vershiniKol);
    for (int i = 0; i < vershiniKol; ++i) {
        graphTemp->getVershina(i)->data = i + 1;
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

void createMassiveVershin(int vershiniKol, int** massiveVershin, int startVershina) {
    for (int i = 0; i < vershiniKol; i++) {
        massiveVershin[i] = new int[3];
        massiveVershin[i][0] = i + 1;
        massiveVershin[i][1] = 2147483647;
        massiveVershin[i][2] = 0;
    }
    massiveVershin[startVershina - 1][1] = 0;
}

void outputBeautifulOtvet(int startVershina, int vershiniKol, int** massiveVershin) {
    cout << "\nPaths from vershina " << startVershina << " to others:\n";
    int numbering = 1;
    for (int i = 0; i < vershiniKol; i++) {
        if (massiveVershin[i][2] == 2 && i + 1 != startVershina) {
            cout << numbering << ") " << startVershina << " -> " << i + 1 << " = " << massiveVershin[i][1] << "\n";
            numbering++;
        }
    }
}

int findingNeighborsOfVershina(int** massiveVershin, int workingVershina, int vershiniKol, DirectedGraph<int, int>* graph) {
    int length = massiveVershin[workingVershina - 1][1];
    massiveVershin[workingVershina - 1][2] = 2;
    for (int i = 0; i < vershiniKol; i++) {
        if (graph->containsRebroBetweenVershina(graph->getVershina(workingVershina - 1), graph->getVershina(i)) && 
            massiveVershin[i][1] > length + graph->getRebro(graph->getVershina(workingVershina - 1), graph->getVershina(i))->data) {
                massiveVershin[i][1] = length + graph->getRebro(graph->getVershina(workingVershina - 1), graph->getVershina(i))->data;
                massiveVershin[i][2] = 1;
        }
    }
    return 0;
}

int toTheNextVershina(int vershiniKol, int** massiveVershin, int startVershina, int *workingVershina, bool *ending) {
    int counter = 0;
    while (counter < vershiniKol && massiveVershin[counter][2] != 1) {
        counter++;
    }
    if (counter >= vershiniKol) {
        outputBeautifulOtvet(startVershina, vershiniKol, massiveVershin);
        *ending = false;
    }
    else {
        *workingVershina = massiveVershin[counter][0];
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
    workingVershina = startVershina;
    int** massiveVershin = new int* [vershiniKol]; // 0)номер элемента; 1)путь до него; 2)посещённый или нет
    createMassiveVershin(vershiniKol, massiveVershin, workingVershina);

    // Searching using Dijkstra's algorithm
    bool ending = true;
    while (ending) {
        findingNeighborsOfVershina(massiveVershin, workingVershina, vershiniKol, graph);
        toTheNextVershina(vershiniKol, massiveVershin, startVershina, &workingVershina, &ending);
    }
    
    // Deleting everything
    for (int i = 0; i < vershiniKol; i++) {
        delete[] massiveVershin[i];
    }
    graph->~DirectedGraph();
    return 0;
}

