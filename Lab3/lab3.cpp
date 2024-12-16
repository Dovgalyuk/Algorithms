#include <fstream>
#include <iostream>
#include "queue.h"
using namespace std;

#define areaWall '#'
#define areaStart 'X'
#define areaEnd 'Y'
#define areaMinPath 'x'
#define areaPath '.'

struct Position {
    int x, y;
};

struct Area {
    // Clear memory
    ~Area() {
        for (Queue* queue : area) {
            delete queue;
        }
    }

    // Upload area from txt
    bool uploadFromTxt(ifstream& input) {
        bool flag = true;
        string line;
        row = -1;
        col = 0;

        Queue* areaY = nullptr;
        while (getline(input, line) && flag) {
            if (row == -1) {
                // First int row in area
                row = (int) line.size();
            } else if (row != (int) line.size()) {
                // If area with different row
                flag = false;
            }

            areaY = new Queue();
            for (int i = 0; i < (int) line.size(); i++) {
                if (line[i] == areaWall) {
                    areaY->insert(-2);
                } else if (line[i] == areaPath) {
                    areaY->insert(-1);
                } else if (line[i] == areaEnd && (end.x == -1 || end.y == -1)) {
                    areaY->insert(-1);
                    end.x = i;
                    end.y = col;
                } else if (line[i] == areaStart && (start.x == -1 || start.y == -1)) {
                    areaY->insert(0);
                    start.x = i;
                    start.y = col;
                } else {
                    // Char not success or 2 end or 2 start
                    flag = false;
                }
            }
            area.push_back(areaY);
            col++;
        }
        // Delete object in area if flag is not success
        if (!flag) {
            for (Queue* queue : area) {
                delete queue;
            }
        }
        return flag;
    }

    std::string findMinPath() {
        if (waveAlgorithm() == -1) {
            return "IMPOSSIBLE";
        }
        return visualMinPath();
    }

private:
    // Private data
    int col = -1, row = -1;
    std::vector<Queue*> area;
    Position start{-1, -1}, end{-1, -1};

    // Find min path to exit (waveAlgorithm)
    int waveAlgorithm() {
        // If area is empty or has no start or end
        if (end.x == -1 || end.y == -1 || start.x == -1 || start.y == -1 || area.empty()) {
            return -1;
        }

        // Init queue with cord position (add start position)
        Queue *queue = new Queue();
        queue->insert(start.x); queue->insert(start.y);

        // Cords around value (Up, Down, Left, Right)
        int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        while (!queue->empty()) {
            // Put cords from queue
            int x = queue->get(); queue->remove();
            int y = queue->get(); queue->remove();

            // Get middle value from area
            Data valueMiddle = _getDataByCord(x, y);

            // Check if cord in queue is end, return min path
            if (x == end.x && y == end.y) {
                return valueMiddle;
            }

            // Change value around (Up, Down, Left, Right)
            for (const auto & direction : directions) {
                int dx = x + direction[0];
                int dy = y + direction[1];

                // If values(dx,dy) in area
                if (0 <= dx && dx < col && 0 <= dy && dy < row) {
                    Data valueAround = _getDataByCord(dx, dy);

                    // If value not visited (not wall)
                    if (valueAround == -1) {
                        _setDataByCord(valueMiddle + 1, dx, dy);
                        // Add around value in queue
                        queue->insert(dx); queue->insert(dy);
                    }
                }
            }
        }
        return -1;
    }

    // Print answer
    std::string visualMinPath() {
        // Create a copy of the area for visualization
        std::vector<std::string> visualArea(col, std::string(row, '.'));

        // Fill walls and endpoints
        for (int y = 0; y < col; ++y) {
            for (int x = 0; x < row; ++x) {
                int value = _getDataByCord(x, y);
                if (value == -2) {
                    visualArea[y][x] = areaWall;
                } else if (x == start.x && y == start.y) {
                    visualArea[y][x] = areaStart;
                } else if (x == end.x && y == end.y) {
                    visualArea[y][x] = areaEnd;
                }
            }
        }

        // Backtrace the path
        int x = end.x, y = end.y;
        while (!(x == start.x && y == start.y)) {
            visualArea[y][x] = 'x'; // Mark the path

            // Find the next step by checking neighbors with value - 1
            int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
            int currentValue = _getDataByCord(x, y);

            for (const auto& direction : directions) {
                int dx = x + direction[0];
                int dy = y + direction[1];

                if (0 <= dx && dx < row && 0 <= dy && dy < col) {
                    if (_getDataByCord(dx, dy) == currentValue - 1) {
                        x = dx;
                        y = dy;
                        break;
                    }
                }
            }
        }

        // Mark the start position
        visualArea[start.y][start.x] = areaStart;
        visualArea[end.y][end.x] = areaEnd;

        std::string result;
        for (const auto& line : visualArea) {
            result += line + "\n";
        }
        return result;
    }

    // Set Data(int) in queue by cord (x,y)
    Data _getDataByCord(int x, int y) {
        if (y < 0 || y >= col || x < 0 || x >= row) {
            throw std::out_of_range("Coordinates are out of bounds: (" + std::to_string(x) + ", " + std::to_string(y) + ")");
        }
        // Safe swap, for get data on X place
        area[y]->safeSwap(-x);
        // Remove value
        Data value = area[y]->get();
        // Safe swap, for return the array to original state
        area[y]->safeSwap(x);
        return value;
    }

    // Set Data(int) in queue by cord (x,y)
    void _setDataByCord(Data value, int x, int y) {
        if (y < 0 || y >= col || x < 0 || x >= row) {
            throw std::out_of_range("Coordinates are out of bounds: (" + std::to_string(x) + ", " + std::to_string(y) + ")");
        }
        // Safe swap, for remove data on X place
        area[y]->safeSwap(-x);
        // Remove value
        area[y]->remove();
        // Safe swap, for input data on X place
        area[y]->insert(value);
        area[y]->safeSwap(1);
        // Safe swap, for return the array to original state
        area[y]->safeSwap(x);
    }
};

int main(int argc, char **argv) {
    // Test 1
    // input data from txt file
    ifstream inputTest1(argv[1]);

    // Upload area data from txt (test 1)
    Area* area1 = new Area();
    if (!area1->uploadFromTxt(inputTest1)) {
        delete area1;
        return 1;
    }

    // Find min path in Area (test 1) & Test
    std::string minPathArea1 = area1->findMinPath();
    if (minPathArea1 != "######\n#xxxX#\n#x####\n#xxxY#\n######\n") {
        cout << "Test 1: fail" << endl;
        delete area1;
        return 1;
    }
    cout << "Test 1: success" << endl;
    cout << minPathArea1 << endl;
    delete area1;

    // Test 2
    // input data from txt file
    ifstream inputTest2(argv[2]);

    // Upload area data from txt (test 2)
    Area* area2 = new Area();
    if (!area2->uploadFromTxt(inputTest2)) {
        delete area2;
        return 1;
    }

    // Find min path in Area (test 2) & Test
    std::string minPathArea2 = area2->findMinPath();
    if (minPathArea2 != "IMPOSSIBLE") {
        cout << "Test 2: fail" << endl;
        delete area2;
        return 1;
    }
    cout << "Test 2: success" << endl;
    cout << minPathArea2 << endl;
    delete area2;

    return 0;
}
