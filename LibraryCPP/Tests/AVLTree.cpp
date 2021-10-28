//
// Created by KirilliriK on 22.10.2021.
//

#include <iostream>
#include "AVLTree.h"

int main() {
    AVLTree tree;
    for (size_t i = 1; i <= 6; i++) {
        tree.addNode(i);
    }
    for (size_t i = 1; i <= 6; i++) {
        if (tree.findNode(i) != nullptr) continue;
        std::cout << "Error with findNode" << std::endl;
        return -1;
    }

    if (tree.findNode(4)->height != 3 ) {
        std::cout << "Error with tree balancing" << std::endl;
        return -1;
    }

    tree.removeNode(3);

    if (tree.findNode(3) != nullptr) {
        std::cout << "Error with node deleting" << std::endl;
        return -1;
    }

    tree.addNode(3);

    for (int i = 7 ; i < 1000000; ++i)
        tree.addNode(i);

    return 0;
}
