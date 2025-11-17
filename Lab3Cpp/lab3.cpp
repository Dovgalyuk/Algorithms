#include <iostream>
#include <fstream>
#include <string>
#include "queue.h"

using namespace std;

struct Reaction {
    char from;
    char to;
};

int main(int argc, char* argv[]) {
    ifstream input;
    string start;
    if (argc > 1)
    {
        input.open(argv[1]);
    }
    getline(input, start);

    Reaction reactions[100];
    size_t rcount = 0;

    string line;
    while (getline(input, line)) {
        size_t pos = line.find("->");
        if (pos != string::npos) {
            reactions[rcount].from = line[0];
            reactions[rcount].to = line[pos + 2];
            rcount++;
        }
    }

    char order[26];
    size_t kcount = 0;

    bool used[26] = { false };
    if (!start.empty())
        used[start[0] - 'A'] = true;
    
    Queue* queue = queue_create();
    queue_insert(queue, (Data)start[0]);

    while (!queue_empty(queue)) {
        char cur = (char)queue_get(queue);
        queue_remove(queue);

        for (size_t i = 0; i < rcount; ++i) {
            if (reactions[i].from == cur) {
                char next = reactions[i].to;
                int id = next - 'A';
                if (!used[id]) {
                    used[id] = true;
                    order[kcount++] = next;
                    queue_insert(queue, (Data)next);
                }
            }
        }
    }

    for (size_t i = 0; i < kcount; ++i)
        cout << order[i] << "\n";

    queue_delete(queue);

    return 0;
}
