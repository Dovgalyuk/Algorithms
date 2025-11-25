#pragma once
#include <limits>
#include <queue>
#include "IGraph.h"
#include "vector.h"

template<class EdgeType>
class AStar {
    using TDVector = Vector<Vector<EdgeType>>;

    struct Node {
        EdgeType f = std::numeric_limits<EdgeType>::infinity();
        EdgeType g = std::numeric_limits<EdgeType>::infinity();
        EdgeType h = 0;
        std::size_t parent = 0;
        bool closed = false;
    };

    struct QueueNode {
        std::size_t index;
        EdgeType fScore;

        bool operator>(const QueueNode &other) const {
            return fScore > other.fScore;
        }
    };

public:
    static Vector<std::size_t> findPath(
        const std::shared_ptr<IGraph<std::string, EdgeType>>& graph,
        const std::size_t start,
        const std::size_t goal,
        std::size_t gridCols,
        EdgeType minCost) {

        const std::size_t vertexCount = graph->vertexCount();
        Vector<Node> nodes(vertexCount);

        std::priority_queue<QueueNode, Vector<QueueNode>, std::greater<> > openQueue;
        Vector inOpenSet(vertexCount, false);

        nodes[start].g = 0;
        nodes[start].h = heuristic(start, goal, gridCols, minCost);
        nodes[start].f = nodes[start].g + nodes[start].h;
        nodes[start].parent = start;

        openQueue.push({start, nodes[start].f});
        inOpenSet[start] = true;

        while (!openQueue.empty()) {
            auto [index, fScore] = openQueue.top();
            openQueue.pop();

            const std::size_t currentIndex = index;

            if (!inOpenSet[currentIndex]) continue;
            inOpenSet[currentIndex] = false;

            if (currentIndex == goal) {
                return reconstructPath(nodes, goal);
            }

            nodes[currentIndex].closed = true;

            for (auto it = graph->begin(currentIndex); it != graph->end(currentIndex); ++it) {
                auto [neighborIndex, neighborVertex, edgeWeight] = *it;

                if (nodes[neighborIndex].closed) continue;

                if (const double tentativeG = nodes[currentIndex].g + edgeWeight; tentativeG < nodes[neighborIndex].g) {
                    nodes[neighborIndex].parent = currentIndex;
                    nodes[neighborIndex].g = tentativeG;
                    nodes[neighborIndex].h = heuristic(neighborIndex, goal, gridCols, minCost);
                    nodes[neighborIndex].f = nodes[neighborIndex].g + nodes[neighborIndex].h;

                    if (!inOpenSet[neighborIndex]) {
                        openQueue.push({neighborIndex, nodes[neighborIndex].f});
                        inOpenSet[neighborIndex] = true;
                    }
                }
            }
        }

        return {};
    }

private:
    static Vector<std::size_t> reconstructPath(const Vector<Node>& nodes, std::size_t goal) {
        std::size_t length = 0;
        std::size_t current = goal;
        while (true) {
            length++;
            if (current == nodes[current].parent) break;
            current = nodes[current].parent;
        }

        Vector<std::size_t> path(length);
        current = goal;
        for (std::size_t i = length - 1; i < length; --i) {
            path[i] = current;
            current = nodes[current].parent;
        }

        return path;
    }

    static double heuristic(const std::size_t from, const std::size_t to, const std::size_t cols, const double minCost) {
        if (minCost <= 0.0) return 0.0;

        const std::size_t fromRow = from / cols;
        const std::size_t fromCol = from % cols;
        const std::size_t toRow = to / cols;
        const std::size_t toCol = to % cols;

        return (std::abs(static_cast<long>(fromRow) - static_cast<long>(toRow)) +
                std::abs(static_cast<long>(fromCol) - static_cast<long>(toCol))) * minCost;
    }
};
