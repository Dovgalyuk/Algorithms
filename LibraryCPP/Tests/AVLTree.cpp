//
// Created by KirilliriK on 22.10.2021.
//

#include <iostream>
#include <random>
#include "AVLTree.h"

int randomInt(int min, int max);

int main() {
    AVLTree tree;
    for (size_t i = 1; i <= 6; i++) {
        tree.addNode(std::to_string(i));
    }
    for (size_t i = 1; i <= 6; i++) {
        if (tree.findNode(std::to_string(i)) != nullptr) continue;
        std::cout << "Error with findNode" << std::endl;
        return -1;
    }

    tree.removeNode("3");

    if (tree.findNode("3") != nullptr) {
        std::cout << "Error with node deleting" << std::endl;
        return -1;
    }

    tree.clear();

    for (size_t i = 0 ; i < 1000; i++) {
        tree.addNode(std::to_string(i));
        if (!tree.isCorrectTree()) {
            std::cout << "Error with tree balancing" << std::endl;
            return -1;
        }
    }

    tree.clear();

    static const int checkSize = 1000000;

    std::cout << "Start adding" << std::endl;
    for (size_t i = 0 ; i < checkSize; i++)
        tree.addNode(std::to_string(i));
    std::cout << "End adding" << std::endl;

    std::cout << "Start removing" << std::endl;
    for (size_t i = 0 ; i < checkSize; i++)
        tree.removeNode(std::to_string(i));
    std::cout << "End removing" << std::endl;

    tree.clear();

    std::cout << "Start adding" << std::endl;
    for (int i = 0 ; i < checkSize; ++i)
        tree.addNode(std::to_string(randomInt(0, checkSize)));
    std::cout << "End adding" << std::endl;

    std::cout << "Start removing" << std::endl;
    for (int i = 0 ; i < checkSize; ++i)
        tree.removeNode(std::to_string(randomInt(0, checkSize)));
    std::cout << "End removing" << std::endl;

    return 0;
}

int randomInt(int min, int max) {
    std::random_device randomDevice;
    std::mt19937 randomAlgorithm(randomDevice());
    std::uniform_int_distribution<int> dist(min, max);

    return dist(randomAlgorithm);
}
