#include <iostream>
#include <fstream>
#include <climits>
#include "queue.h"

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

    int n1, n2, n3;

    input >> n1;
    Queue* queue1 = queue_create();
    for (int i = 0; i < n1; ++i) {
        int time;
        input >> time;
        queue_insert(queue1, time);
    }

    input >> n2;
    Queue* queue2 = queue_create();
    for (int i = 0; i < n2; ++i) {
        int time;
        input >> time;
        queue_insert(queue2, time);
    }

    input >> n3;
    Queue* queue3 = queue_create();
    for (int i = 0; i < n3; ++i) {
        int time;
        input >> time;
        queue_insert(queue3, time);
    }

    while (!queue_empty(queue1) || !queue_empty(queue2) || !queue_empty(queue3)) {
        int min_time = INT_MAX;
        int queue_index = -1;
        int next_time = -1;

        if (!queue_empty(queue1)) {
            int time1 = queue_get(queue1);
            if (time1 < min_time) {
                min_time = time1;
                queue_index = 1;
                next_time = time1;
            }
        }


        if (!queue_empty(queue2)) {
            int time2 = queue_get(queue2);
            if (time2 < min_time) {
                min_time = time2;
                queue_index = 2;
                next_time = time2;
            }
        }

        if (!queue_empty(queue3)) {
            int time3 = queue_get(queue3);
            if (time3 < min_time) {
                min_time = time3;
                queue_index = 3;
                next_time = time3;
            }
        }

        if (queue_index == 1) {
            output << queue_index << " " << next_time << std::endl;
            queue_remove(queue1);
        }
        else if (queue_index == 2) {
            output << queue_index << " " << next_time << std::endl;
            queue_remove(queue2);
        }
        else if (queue_index == 3) {
            output << queue_index << " " << next_time << std::endl;
            queue_remove(queue3);
        }
    }

    queue_delete(queue1);
    queue_delete(queue2);
    queue_delete(queue3);

    input.close();
    output.close();

    return 0;
}
