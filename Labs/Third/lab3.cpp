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

bool isPass(const char i) {
    return i == PASSED;
}

void checkPoint(Queue *Qx, Queue *Yx, const int x, const int y) {
    queue_insert(Qx, x);
    queue_insert(Yx, y);
}

void findPoints(vector<string> &masFile, Queue *Qx, Queue *Qy, const int x, const int y) {
    char up = masFile[x - 1][y];
    char down = masFile[x + 1][y];
    char right = masFile[x][y - 1];
    char left = masFile[x][y + 1];

    if ((left == EMPTY || isNumber(left)) && !isPass(left)) {
        checkPoint(Qx, Qy, x, y + 1);
    }
    if ((right == EMPTY || isNumber(right)) && !isPass(right)) {
        checkPoint(Qx, Qy, x, y - 1);
    }
    if ((up == EMPTY || isNumber(up)) && !isPass(up)) {
        checkPoint(Qx, Qy, x - 1, y);
    }
    if ((down == EMPTY || isNumber(down)) && !isPass(down)) {
        checkPoint(Qx, Qy, x + 1, y);
    }

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

        while (!queue_empty(x)) {
            int x1 = queue_get(x);
            int y1 = queue_get(y);
            if (isNumber(masFile[x1][y1])) {
                cout << "x = " << x1 + 1 << " y = " << y1 + 1 << endl;
                cout << "masFile[x][y] = " << masFile[x1][y1] << endl;
                queue_delete(x);
                queue_delete(y);
                file.close();
                exit(0);
            }
            findPoints(masFile, x, y, queue_get(x), queue_get(y));
            queue_remove(x);
            queue_remove(y);
        }

    } else {
        cout << "ERROR: Opening file" << endl;
    }

    queue_delete(x);
    queue_delete(y);
    file.close();

}