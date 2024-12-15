#ifndef GRAPH_H
#define GRAPH_H
#include "vector.h"
#include <vector>
#include <stdexcept>
#include <limits>

template <typename ValueType>
struct Node {
    Node() {}
    Node(ValueType label) : label(label) {}

    ValueType label = ValueType();
};

template <typename EdgeType>
struct Connection {
    Connection() {}
    Connection(EdgeType label) : label(label) {}

    EdgeType label = EdgeType();
};

template<typename ValueType, typename EdgeType>
class GraphStructure {
public:
    enum class StructureType {
        Directed,
        Undirected
    };

    GraphStructure(StructureType structureType) : structureType(structureType) {}

    ~GraphStructure() {
        clearConnections();
    }

    GraphStructure& operator=(const GraphStructure& other) {
        if (this == &other) {
            return *this;
        }
        clearConnections();

        nodes = other.nodes;
        connectionMatrix.resize(other.connectionMatrix.size());
        for (size_t i = 0; i < other.connectionMatrix.size(); ++i) {
            if (other.connectionMatrix[i] != nullptr) {
                connectionMatrix[i] = new Connection(*other.connectionMatrix[i]);
            } else {
                connectionMatrix[i] = nullptr;
            }
        }

        structureType = other.structureType;
        return *this;
    }

    void addConnection(size_t fromNode, size_t toNode, EdgeType connectionLabel) {
        if (fromNode >= getNodeCount() || toNode >= getNodeCount()) {
            throw std::out_of_range("Index is out of range!");
        }

        Connection<EdgeType>*& existingConnection = connectionMatrix[fromNode * getNodeCount() + toNode];

        if (existingConnection != nullptr) {
            delete existingConnection;
        }

        existingConnection = new Connection<EdgeType>(connectionLabel);

        if (structureType == StructureType::Undirected) {
            Connection<EdgeType>*& existingReverseConnection = connectionMatrix[toNode * getNodeCount() + fromNode];

            if (existingReverseConnection != nullptr) {
                delete existingReverseConnection;
            }
            existingReverseConnection = new Connection<EdgeType>(connectionLabel);
        }
    }

    void removeConnection(size_t fromNode, size_t toNode) {
        if (fromNode >= getNodeCount() || toNode >= getNodeCount()) {
            throw std::out_of_range("Node index out of range.");
        }

        size_t index = fromNode * getNodeCount() + toNode;
        delete connectionMatrix[index];
        connectionMatrix[index] = nullptr;

        if (structureType == StructureType::Undirected) {
            size_t reverseIndex = toNode * getNodeCount() + fromNode;
            delete connectionMatrix[reverseIndex];
            connectionMatrix[reverseIndex] = nullptr;
        }
    }

    Connection<EdgeType>* getConnection(size_t fromNode, size_t toNode) const {
        size_t totalNodes = getNodeCount();
        return connectionMatrix[fromNode * totalNodes + toNode];
    }

    bool doesConnectionExist(size_t fromNode, size_t toNode) const {
        return getConnection(fromNode, toNode) != nullptr;
    }

    Node<ValueType>& getNode(size_t index) {
        if (index >= nodes.size()) {
            throw std::out_of_range("Index is out of range!");
        }
        return nodes[index];
    }

    size_t getNodeCount() const {
        return nodes.size();
    }

    size_t addNode(ValueType nodeLabel) {
        size_t index = nodes.size();
        nodes.push(Node<ValueType>(nodeLabel));

        size_t totalNodes = getNodeCount();
        Vector<Connection<EdgeType>*> newConnectionMatrix;
        newConnectionMatrix.resize(totalNodes * totalNodes);

        for (size_t i = 0; i < totalNodes - 1; ++i) {
            for (size_t j = 0; j < totalNodes - 1; ++j) {
                newConnectionMatrix.set(i * totalNodes + j, connectionMatrix.get(i * (totalNodes - 1) + j));
            }
        }

        for (size_t i = 0; i < totalNodes; ++i) {
            newConnectionMatrix.set(i * totalNodes + (totalNodes - 1), nullptr); // Новый столбец
            newConnectionMatrix.set((totalNodes - 1) * totalNodes + i, nullptr); // Новая строка
        }

        connectionMatrix.swap_data(newConnectionMatrix);

        return index;
}

void removeNode(size_t index) {
        size_t totalNodes = getNodeCount();
        if (index >= totalNodes) {
            return;
        }

        for (size_t i = 0; i < totalNodes; i++) {
            Connection<EdgeType>* connection = connectionMatrix.get(index * totalNodes + i);
            if (connection) {
                delete connection;
                connectionMatrix.set(index * totalNodes + i, nullptr);
            }
            connection = connectionMatrix.get(i * totalNodes + index);
            if (connection) {
                delete connection;
                connectionMatrix.set(i * totalNodes + index, nullptr);
            }
        }

        for (size_t i = index; i < totalNodes - 1; i++) {
            nodes.set(i, nodes.get(i + 1));
        }
        nodes.resize(totalNodes - 1);

        Vector<Connection<EdgeType>*> tempConnectionMatrix;
        size_t updatedNodeCount = getNodeCount();
        tempConnectionMatrix.resize(updatedNodeCount * updatedNodeCount);
        for (size_t i = 0; i < updatedNodeCount; i++) {
            for (size_t j = 0; j < updatedNodeCount; j++) {
                Connection<EdgeType>* connection = connectionMatrix.get(((i + (i >= index)) * totalNodes) + (j + (j >= index)));
                tempConnectionMatrix.set((i * updatedNodeCount) + j, connection);
            }
        }

        connectionMatrix.swap_data(tempConnectionMatrix);
    }

    std::vector<ValueType> getAllNodeData() const {
        std::vector<ValueType> allData;
        for (size_t i = 0; i < nodes.size(); i++) {
            allData.push_back(nodes[i].label);
        }
        return allData;
    }

    struct Iterator {
    private:
        const GraphStructure* graph;
        size_t currentNode;
        size_t nextNode;

        size_t findNextAdjacentNode() {
            for (size_t i = nextNode + 1; i < graph->getNodeCount(); i++) {
                if (graph->doesConnectionExist(currentNode, i)) {
                    return i;
                }
            }
            return static_cast<size_t>(-1);
        }

    public:
        Iterator(const GraphStructure* graph, size_t startNode) : graph(graph), currentNode(startNode), nextNode(static_cast<size_t>(-1)) {
            nextNode = findNextAdjacentNode();
        }

        bool hasNext() const {
            return nextNode != static_cast<size_t>(-1);
        }

        size_t next() {
            if (!hasNext()) {
                throw std::out_of_range("No more adjacent nodes");
            }
            size_t current = nextNode;
            nextNode = findNextAdjacentNode();
            return current;
        }

        size_t getCurrentNode() const {
            return nextNode;
        }

        int getStartNode() const {
            return currentNode;
        }
    };

    Iterator getIterator(size_t startNode) const {
        return Iterator(this, startNode);
    }

private:
    void clearConnections() {
        for (size_t i = 0; i < connectionMatrix.size(); i++) {
            delete connectionMatrix.get(i);
            connectionMatrix.set(i, nullptr);
        }
    }

    Vector<Node<ValueType>> nodes;
    Vector<Connection<EdgeType>*> connectionMatrix;
    StructureType structureType;
};

#endif