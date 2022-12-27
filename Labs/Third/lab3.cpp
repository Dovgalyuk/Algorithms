#include <iostream>
#include "queue.h"
#include <fstream>
#include <vector>

using namespace std;

const char EMPTY = '.';
const char PASSED = '@';

bool isNumber(const char c) {
    return c >= '0' && c <= '9';
}

void checkPoint(vector<string> masFile, Queue *Qx, Queue *Yx, const int x, const int y) {
    char i = masFile[x][y];
    if (i == EMPTY || isNumber(i)) {
        queue_insert(Qx, x);
        queue_insert(Yx, y);
    }
}

void findPoints(vector<string> &masFile, Queue *Qx, Queue *Qy, const int x, const int y) {

    //left
    checkPoint(masFile, Qx, Qy, x, y + 1);

    //right
    checkPoint(masFile, Qx, Qy, x, y - 1);

    //up
    checkPoint(masFile, Qx, Qy, x - 1, y);

    //down
    checkPoint(masFile, Qx, Qy, x + 1, y);

    masFile[x][y] = PASSED;
}


int main() {

    vector<string> masFile;
    string buffer;
    Queue *x = queue_create();
    Queue *y = queue_create();

    ifstream file(R"(D:\CLion\Labs\Third\testLab3.txt)");

    if (file.is_open()) {

        while (getline(file, buffer)) {
            masFile.push_back(buffer);
        }

        for (int i = 0; i < masFile.size(); i++) {
            for (int c = 0; c < masFile.size(); c++) {
                if (masFile[i][c] == 'X') {
                    queue_insert(x, i);
                    queue_insert(y, c);
                }
            }
        }

        while (!queue_empty(x) || !queue_empty(y)) {
            int x1 = queue_get(x);
            int y1 = queue_get(y);
            if (isNumber(masFile[x1][y1])) {
                cout << "Closest number to the beginning = " << masFile[x1][y1] << endl;
                cout << "The coordinates of this number: x = " << y1 + 1 << " y = " << x1 + 1 << endl;
                queue_delete(x);
                queue_delete(y);
                file.close();
                exit(0);
            }
            queue_remove(x);
            queue_remove(y);
            if (masFile[x1][y1] != PASSED) {
                findPoints(masFile, x, y, x1, y1);
            }
        }
    } else {
        cout << "ERROR: Opening file" << endl;
    }

    queue_delete(x);
    queue_delete(y);
    file.close();
}