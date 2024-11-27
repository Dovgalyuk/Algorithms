#include <fstream>
#include <vector>
#include "queue.h"
#include "vector.h"

using namespace std;

struct Pos {
    int stolbik;
    int stroka;
};

size_t privedenieint(int stroka, int stolbik, size_t num_stolbiki) {
    return (size_t)(stroka) * num_stolbiki + stolbik;
}

Pos privedeniepos(size_t queue, size_t num_stolbiki) {
    Pos pos;
        pos.stroka = int(queue / num_stolbiki);
    pos.stolbik = int(queue % num_stolbiki);
    return pos;
}

bool poiskpos(vector<string>& labirint, int stroka, int stolbik) {
    return stroka >= 0 && size_t(stroka) < labirint.size() &&
           stolbik >= 0 && size_t(stolbik) < labirint[0].size() && labirint[stroka][stolbik] == '.';
}

int bfs(vector<string>& labirint, Pos start) {
    int vsegopos = 0;
    Queue* queue = queue_create();
    int num_stolbiki = labirint[0].size();


    queue_insert(queue, privedenieint(start.stroka, start.stolbik, num_stolbiki));
    labirint[start.stroka][start.stolbik] = 'x';

    while (!queue_empty(queue)) {
        Pos tek = privedeniepos(queue_get(queue), num_stolbiki);
        queue_remove(queue);
        vsegopos++;

        Pos napravlen[4] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        for (int i = 0; i < 4; ++i) {
            int new_stroka = tek.stroka + napravlen[i].stroka;
            int new_stolbik = tek.stolbik + napravlen[i].stolbik;
            if (poiskpos(labirint, new_stroka, new_stolbik)) {
                labirint[new_stroka][new_stolbik] = 'x';
                queue_insert(queue, privedenieint(new_stroka, new_stolbik, num_stolbiki));
            }
        }
    }
    queue_delete(queue);
    return vsegopos;
}

int main(int argc, char* argv[]) {

    ifstream input(argv[1]);
    if (!input.is_open()) {
        cerr << "Error: could not open input file" << argv[1] << endl;
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
                start.stroka = int(i);
                start.stolbik = int(j);
                start_nahod = true;
                break;
            }
        }
        if (start_nahod) break;
    }

    if (!start_nahod) {
        cerr << "start otsutstvuet\n";
        return 1;
    }

    int vsegopos = bfs(labirint, start);
    cout << vsegopos << "\n";

    for (size_t i = 0; i < labirint.size(); ++i) {
        cout << labirint[i] << "\n";
    }
}