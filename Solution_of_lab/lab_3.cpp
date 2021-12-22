#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "queue.h"
using namespace std;

class coordinates {
public:
    int x, y;
};

typedef Queue <coordinates> QueueOfPositions;
typedef vector <string> CellMap;

CellMap init_map();
coordinates start_pos(CellMap& map);
int find_free_cell(CellMap& map);
void check_cell_waves_alg(CellMap& map, QueueOfPositions& queue, int& free_cell_ñount);
void output_result(CellMap& map, const int free_cell_ñount);

int main() {
    CellMap map = init_map();
    output_result(map, find_free_cell(map));
}

void check_cell_waves_alg(CellMap& map, QueueOfPositions& queue, int& freeTilesCount) {

    while (!queue.empty()) {
        coordinates checkPosition = queue.get();

        const int dx[] = { -1, 1, 0, 0 };
        const int dy[] = { 0, 0, -1, 1 };

        for (size_t i = 0; i < 4; i++) {

            coordinates newPosition = checkPosition;

            newPosition.x += dx[i];
            newPosition.y += dy[i];

            if (newPosition.x < 0 || newPosition.y < 0 || newPosition.x >= map[newPosition.y].size()|| newPosition.y >= map.size()) continue;

            char ch = map[newPosition.y][newPosition.x];

            switch (ch) {
            case '#':
            case 'X':
                continue;
            case '.':
                queue.insert(newPosition);
                map[newPosition.y][newPosition.x] = 'X';
                freeTilesCount++;
                continue;
            default:
                cout << "Unknown cell type" << endl;
                exit(-1);
            }
        }
        queue.remove();
    }
}

int find_free_cell(CellMap& map) {
    int FreeCellsCount = 1;

    QueueOfPositions CoordinatesOfPositions;
    coordinates startPosition = start_pos(map);
    CoordinatesOfPositions.insert(startPosition);

    check_cell_waves_alg(map, CoordinatesOfPositions, FreeCellsCount);

    return FreeCellsCount;
}


CellMap init_map() {
    CellMap map;
    ifstream file("map.txt");
    string inputString;

    if (file.is_open()) {
        while (getline(file, inputString)) {
            map.push_back(inputString);
        }
    }
    else {
        cout << "File not found" << endl;
        exit(-1);
    }
    file.close();
    return map;
}


coordinates start_pos(CellMap& map) {

    coordinates startPosition{ 0, 0 };
    for (const string& str : map) {
        startPosition.x = str.find_first_of('X');
        if (startPosition.x != string::npos) break;
        startPosition.y++;
    }
    return startPosition;
}

void output_result(CellMap& map, const int free_cell_ñount) {

    cout << "Cells available for X: " << free_cell_ñount << endl;
    for (const string& str : map) {
        cout << str << endl;
    }

}