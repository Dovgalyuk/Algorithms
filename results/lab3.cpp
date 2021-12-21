//
// Created by onisken on 15.12.2021.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include "queue.h"

struct Vertex {
    int id;
    int weight;

    Vertex() {
        id = -1;
        weight = -1;
    }
    Vertex(int id, int weight) {
        this->id = id;
        this->weight = weight;
    }
};

typedef Queue<int> IDQueue;

void findPath(int size, int finishID, std::vector<bool> &links, IDQueue &vertexQueue, std::vector<Vertex> &vertexes);

int main() {
    Queue<bool> queue;
    int size;
    int startID, finishID;
    std::cin >> size;
    std::cin >> startID;
    std::cin >> finishID;
    startID--;
    finishID--;
    std::vector<bool> links;
    links.resize(size * size);
    std::vector<Vertex> vertexes;
    vertexes.resize(size);
    for (int i = 0; i < size; i++) {
        int first, second;
        std::cin >> first;
        std::cin >> second;
        first--;
        second--;
        links[first + second * size] = true;
        links[second + first * size] = true;
        vertexes[i] = Vertex(i, 0);
    }
    vertexes[startID].weight = 1;
    IDQueue first;
    first.insert(vertexes[startID].id);
    findPath(size, finishID, links, first, vertexes);
    return 0;
}

void findPath(int size, int finishID, std::vector<bool> &links, IDQueue &vertexQueue, std::vector<Vertex> &vertexes) {
    while (!vertexQueue.empty()) {
        int ownerVertexID = vertexQueue.get();
        int ownerVertexWeight = vertexes[ownerVertexID].weight;
        vertexQueue.remove();
        for (int j = 0; j < size; j++) {
            if (!links[j + ownerVertexID * size]) continue;

            if (j == finishID) {
                std::cout << std::endl;
                vertexes[j].weight = ownerVertexWeight + 1;
                Vertex last = vertexes[j];
                std::string str;
                str.append(std::to_string(last.id + 1));
                str.append(" ");
                for(int g = 0; g < size * size ; g++) {
                    if (last.id == 0) break;

                    for (int x = 0; x < size; x++) {
                        if (!links[x + last.id * size]) continue;
                        if (last.weight - vertexes[x].weight != 1) continue;
                        str.append(std::to_string((vertexes[x].id + 1)));
                        str.append(" ");
                        last = vertexes[x];
                        break;
                    }
                }
                std::reverse(str.begin(), str.end());
                std::cout << str << std::endl;
                return;
            }

            if (vertexes[j].weight != 0 && vertexes[j].weight <= ownerVertexWeight) continue;

            vertexes[j].weight = ownerVertexWeight + 1;
            vertexQueue.insert(vertexes[j].id);
        }
    }
}