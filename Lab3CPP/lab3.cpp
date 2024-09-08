#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include "queue.h"
#include "vector.h"

using namespace std;

struct Pos {
    int stolbik;
    int stroka;

    bool operator==(const Pos& other) const {
        return (stroka == other.stroka && stolbik == other.stolbik);
    }

    bool operator!=(const Pos& other) const {
        return !(*this == other);
    }
};


typedef vector<string>& vec_str;

size_t privedenieint(int stroka, int stolbik, size_t num_stolbiki) {
    return static_cast<size_t>(stroka) * num_stolbiki + stolbik;
}

Pos privedeniepos(size_t queue, size_t num_stolbiki) {
    Pos pos;
    pos.stroka = static_cast<int>(queue / num_stolbiki);
    pos.stolbik = static_cast<int>(queue % num_stolbiki);
    return pos;
}

bool poiskpos(vec_str labirint, int stroka, int stolbik) {
    return stroka >= 0 && size_t(stroka) < labirint.size() &&
           stolbik >= 0 && size_t(stolbik) < labirint[0].size() && 
           labirint[stroka][stolbik] != '#';
}

vector<Pos> bfs(vec_str labirint, Pos start, Pos end) {
    Queue* queue = queue_create();
    int num_stolbiki = labirint[0].size();
    
    queue_insert(queue, privedenieint(start.stroka, start.stolbik, num_stolbiki));
    labirint[start.stroka][start.stolbik] = 'x'; // Помечаем как посещённую

    vector<vector<Pos>> prev(labirint.size(), vector<Pos>(labirint[0].size(), {-1, -1}));

    while (!queue_empty(queue)) {
        Pos tek = privedeniepos(queue_get(queue), num_stolbiki);
        queue_remove(queue);

        if (tek == end) {
            queue_delete(queue); // Освобождаем память перед выходом
            vector<Pos> path;
            for (Pos at = end; at != Pos{-1, -1}; at = prev[at.stroka][at.stolbik]) {
                path.push_back(at);
            }
            reverse(path.begin(), path.end()); // Переворачиваем путь
            return path; // Возвращаем путь
        }

        Pos napravlen[4] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        for (int i = 0; i < 4; ++i) {
            int new_stroka = tek.stroka + napravlen[i].stroka;
            int new_stolbik = tek.stolbik + napravlen[i].stolbik;

            if (poiskpos(labirint, new_stroka, new_stolbik)) {
                labirint[new_stroka][new_stolbik] = 'x'; // Помечаем как посещённую
                queue_insert(queue, privedenieint(new_stroka, new_stolbik, num_stolbiki));
                prev[new_stroka][new_stolbik] = tek; // Сохраняем предшествующую позицию
            }
        }
    }

    queue_delete(queue); // Освобождаем память перед выходом
    return {}; // Возвращаем пустой вектор, если пути нет
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }

    ifstream input(argv[1]);
    if (!input.is_open()) {
        cerr << "Error: could not open input file " << argv[1] << endl;
        return 1;
    }

    vector<string> labirint;
    string line;
    Pos start = {-1, -1};
    Pos end = {-1, -1};

    while (getline(input, line)) {
        labirint.push_back(line);
    }
    
    input.close();

    bool start_nahod = false;
    bool end_nahod = false;

    for (size_t i = 0; i < labirint.size(); ++i) {
        for (size_t j = 0; j < labirint[i].size(); ++j) {
            if (labirint[i][j] == 'X') {
                start.stroka = static_cast<int>(i);
                start.stolbik = static_cast<int>(j);
                start_nahod = true;
            } else if (labirint[i][j] == 'Y') {
                end.stroka = static_cast<int>(i);
                end.stolbik = static_cast<int>(j);
                end_nahod = true;
                            }
        }
        if (start_nahod && end_nahod) break;
    }

    if (!start_nahod || !end_nahod) {
        cerr << "Start or End position not found\n";
        return 1;
    }

    vector<Pos> path = bfs(labirint, start, end);

    if (path.empty()) {
        cout << "IMPOSSIBLE\n";
    } else {
        cout << "Path length: " << path.size() - 1 << "\n"; // Длина пути
        for (const auto& pos : path) {
            cout << "(" << pos.stroka << ", " << pos.stolbik << ")\n"; // Выводим координаты пути
            labirint[pos.stroka][pos.stolbik] = '.'; // Отмечаем путь в лабиринте
        }
        cout << "\nLabyrinth with path:\n";
        for (const auto& row : labirint) {
            cout << row << "\n";
        }
    }

    return 0;
}
