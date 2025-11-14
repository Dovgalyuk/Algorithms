#include <iostream>
#include <fstream>
#include <string>
#include "queue.h"

using namespace std;

struct Reaction {
    string from;
    string to;
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
            reactions[rcount].from = line.substr(0, pos);
            reactions[rcount].to = line.substr(pos + 2);
            rcount++;
        }
    }

    string known[100];
    size_t kcount = 0;
    known[kcount++] = start;

    Queue* queue = queue_create();
    queue_insert(queue, 0);

    while (!queue_empty(queue)) {
        int idx = queue_get(queue);
        queue_remove(queue);
        string cur = known[idx];

        for (size_t i = 0; i < rcount; ++i) {
            if (reactions[i].from == cur) {
                string next = reactions[i].to;
                bool seen = false;
                for (size_t j = 0; j < kcount; ++j)
                    if (known[j] == next) { seen = true; break; }

                if (!seen) {
                    known[kcount++] = next;
                    queue_insert(queue, (Data)(kcount - 1));
                }
            }
        }
    }

    for (size_t i = 1; i < kcount; ++i)
        cout << known[i] << "\n";

    queue_delete(queue);

    return 0;
}
