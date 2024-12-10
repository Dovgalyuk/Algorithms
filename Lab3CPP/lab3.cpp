#include <iostream>
#include <fstream>
#include <climits>
#include "queue.h"

void read_queue(Queue* queue, std::ifstream& input, int n) {
    for (int i = 0; i < n; ++i) {
        int time;
        input >> time;
        queue_insert(queue, time);
    }
}

Queue* find_min_time(Queue* queues[], int& min_time) {
    min_time = INT_MAX;
    Queue* min_queue = nullptr;

    for (int i = 0; i < 3; ++i) {
        if (!queue_empty(queues[i])) {
            int time = queue_get(queues[i]);
            if (time < min_time) {
                min_time = time;
                min_queue = queues[i];
            }
        }
    }

    return min_queue;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    std::ifstream input(argv[1]);
    if (!input) {
        std::cerr << "Error opening file: " << argv[1] << std::endl;
        return 1;
    }
    std::ofstream output("output.txt");

    int n[3];

    for (int i = 0; i < 3; ++i) {
        input >> n[i];
    }

    Queue* queues[3] = {
        queue_create(),
        queue_create(),
        queue_create()
    };

    for (int i = 0; i < 3; ++i) {
        read_queue(queues[i], input, n[i]);
    }

    while (!queue_empty(queues[0]) || !queue_empty(queues[1]) || !queue_empty(queues[2])) {
        int min_time;
        Queue* min_queue = find_min_time(queues, min_time);

        if (min_queue) {
            output << (min_queue == queues[0] ? 1 : (min_queue == queues[1] ? 2 : 3)) << " " << min_time << std::endl;
            queue_remove(min_queue);
        }
    }

    for (int i = 0; i < 3; ++i) {
        queue_delete(queues[i]);
    }

    input.close();
    output.close();

    return 0;
}
