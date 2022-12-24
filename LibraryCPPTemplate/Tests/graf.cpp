#include <iostream>
#include "graf.h"


int main() {
    auto graf = new Graf<int>(10, 1);

    if (graf->getDataVertex(0) != 1) {
        std::cout << "graf initialization error\n";
        return 1;
    }

    for (int i = 0; i < 10; i++) {
        graf->setDataVertex(i, i);
    }

    for (int i = 0; i < 10; i++) {
        if (graf->getDataVertex(i) != i) {
            std::cout << "setDataVertex error\n";
            return 1;
        }

        std::cout << graf->getDataVertex(i) << " ";
    }
    std::cout << "\n";

    graf->addEdge(graf->getVertex(0), graf->getVertex(9));

    if (!graf->checkEdge(graf->getVertex(0), graf->getVertex(9))) {
        std::cout << "addEdge error";
        return 1;
    }

    graf->addEdge(graf->getVertex(0), graf->getVertex(9));
    graf->addEdge(graf->getVertex(0), graf->getVertex(2));

    graf->removeEdge(graf->getVertex(0), graf->getVertex(9));

    if (graf->checkEdge(graf->getVertex(0), graf->getVertex(9))) {
        std::cout << "removeEdge error\n";
        return 1;
    }

    Graf<int>::EdgeIterator iterator(graf->getVertex(0));

    int count = 0;

    while (*iterator != nullptr) {
        count++;
        ++iterator;
    }

    if (count != 1) {
        std::cout << "Error iterator";
        return 1;
    }

    graf->removeVertex(8);

    if (graf->sizeVertexes() != 10 - 1) {
        std::cout << "removeVertex error\n";
        return 1;
    }

    for (int i = 0; i < 10 - 1; i++) {
        std::cout << graf->getDataVertex(i) << " ";
    }

    std::cout << std::endl;
    delete graf;
}