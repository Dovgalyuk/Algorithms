#include <iostream>
#include "priorityQueue.h"

using namespace std;

int main() {
    // Test 1: Create and delete a priority queue
    cout << "Test 1: Creating and deleting a priority queue." << endl;
    PriorityQueue* queue = priorityQueue_create(10);
    priorityQueue_delete(queue);
    cout << "Priority queue created and deleted successfully." << endl;

    // Test 2: Insert and get nodes
    cout << "\nTest 2: Inserting and getting nodes." << endl;
    queue = priorityQueue_create(10);
    HuffmanNode* nodeA = huffman_createLeafNode('A', 1);
    HuffmanNode* nodeB = huffman_createLeafNode('B', 2);
    priorityQueue_insert(queue, nodeA);
    priorityQueue_insert(queue, nodeB);
    cout << "Nodes inserted. Size: " << priorityQueue_getSize(queue) << endl;
    HuffmanNode* fetchedNode = priorityQueue_getNode(queue);
    cout << "Fetched node symbol: " << huffman_getNodeChar(fetchedNode) << ", weight: " << huffman_getNodeWeight(fetchedNode) << endl;
    priorityQueue_delete(queue);

    // Test 3: Check queue size and emptiness
    cout << "\nTest 3: Checking queue size and emptiness." << endl;
    queue = priorityQueue_create(10);
    cout << "Is queue empty? " << (priorityQueue_empty(queue) ? "Yes" : "No") << endl;
    priorityQueue_insert(queue, huffman_createLeafNode('C', 3));
    cout << "After inserting one node, is queue empty? " << (priorityQueue_empty(queue) ? "Yes" : "No") << endl;
    cout << "Queue size: " << priorityQueue_getSize(queue) << endl;
    priorityQueue_delete(queue);

    huffman_deleteTree(nodeA);
    huffman_deleteTree(nodeB);
    huffman_deleteTree(fetchedNode);
    return 0;
}