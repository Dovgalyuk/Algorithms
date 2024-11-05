#include <iostream>
#include <fstream>
#include <vector>
#include "queue.h"
#include "vector.h"

using namespace std;

struct Pos {
    int strok;
    int stolb;
};

size_t privedenieint(int strok, int stolb, size_t num_stolbi) {
    return (size_t)(strok) * num_stolbi + stolb;
}

Pos privedeniepos(size_t encoded, size_t num_stolbi) {
    Pos pos;
    pos.strok = int(encoded / num_stolbi);
    pos.stolb = int(encoded % num_stolbi);
    return pos;
}

bool poiskpos(vector<string>& labirint, int strok, int stolb) {
    return strok >= 0 && size_t(strok) < labirint.size() &&
           stolb >= 0 && size_t(stolb) < labirint[0].size() && labirint[strok][stolb] == '.';
}

int bfs(vector<string>& labirint, Pos start) {
    int vsegopos = 0;
    Queue* queue = queue_create();
    int num_stolbi = labirint[0].size();


    queue_insert(queue, int(privedenieint(start.strok, start.stolb, num_stolbi)));
    labirint[start.strok][start.stolb] = 'x';

    while (!queue_empty(queue)) {
        Pos tek = privedeniepos(queue_get(queue), num_stolbi);
        queue_remove(queue);
        vsegopos++;

        Pos napravlen[4] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        for (int i = 0; i < 4; ++i) {
            int new_strok = tek.strok + napravlen[i].strok;
            int new_stolb = tek.stolb + napravlen[i].stolb;
            if (poiskpos(labirint, new_strok, new_stolb)) {
                labirint[new_strok][new_stolb] = 'x';
                queue_insert(queue, int(privedenieint(new_strok, new_stolb, num_stolbi)));
            }
        }
    }
    queue_delete(queue);
    return vsegopos;
}

int main() {
    ifstream input("input.txt");
    if (!input.is_open()) {
        cerr << "ne otkrit file\n";
        return 1;
    }

    vector<string> labirint;
    string line;
    Pos start = {-1, -1};

    while (getline(input, line)) {
        labirint.push_back(line);
    }
    input.close();


    bool start_nahod = false;
    for (size_t i = 0; i < labirint.size(); ++i) {
        for (size_t j = 0; j < labirint[i].size(); ++j) {
            if (labirint[i][j] == 'X') {
                start.strok = int(i);
                start.stolb = int(j);
                start_nahod = true;
                break;
            }
        }
        if (start_nahod) break;
    }

    if (!start_nahod) {
        cerr << "x otsutstvuet\n";
        return 1;
    }

    int vsegopos = bfs(labirint, start);
    cout << vsegopos << "\n";

    for (size_t i = 0; i < labirint.size(); ++i) {
        cout << labirint[i] << "\n";
    }
}
