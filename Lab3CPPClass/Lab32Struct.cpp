#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include "queue.h"

using namespace std;

struct GameState {
    string board;
    string path;
};

const int dx[4] = { 0, 0, -1, 1 };
const int dy[4] = { -1, 1, 0, 0 };
const char xy[4] = { 'u', 'd', 'l', 'r' };

vector<GameState> genNextStates(const GameState& state) {
    vector<GameState> nextStates;
    const string& board = state.board;
    const string& path = state.path;
    int empos = (int)board.find('0');
    int x = empos % 3;
    int y = empos / 3;
    for (int i = 0; i < 4; i++) {
        int newx = x + dx[i];
        int newy = y + dy[i];
        if (newx >= 0 && newx < 3 && newy >= 0 && newy < 3) {
            int newPos = newy * 3 + newx;
            string newBoard = board;
            swap(newBoard[empos], newBoard[newPos]);
            string newPath = path + xy[i];
            nextStates.push_back({ newBoard, newPath });
        }
    }
    return nextStates;
}

vector<string> getpath(const string& path, const string& start) {
    vector<string> result;
    string currboard = start;
    result.push_back(currboard);
    int empos = (int)start.find('0');
    int x = empos % 3;
    int y = empos / 3;
    for (char move : path) {
        int newx = x, newy = y;
        switch (move) {
        case 'u':
            newy--;
            break;
        case 'd':
            newy++;
            break;
        case 'l':
            newx--;
            break;
        case 'r':
            newx++;
            break;
        }
        int newpos = newy * 3 + newx;
        swap(currboard[empos], currboard[newpos]);
        result.push_back(currboard);
        empos = newpos;
        x = newx;
        y = newy;
    }
    return result;
}

vector<string> game8(const string& start) {
    Queue myqueue;
    map<string, bool> visited;
    const string target = "123456780";
    GameState initial = { start, "" };
    myqueue.insert(stoi(start));
    map<string, string> paths;
    paths[start] = "";
    visited[start] = true;
    while (!myqueue.empty()) {
        int cnumb = myqueue.get();
        myqueue.remove();
        string stemp = to_string(cnumb);
        string currboard = string(9 - stemp.length(), '0') + stemp;
        if (currboard == target) {
            return getpath(paths[currboard], start);
        }
        GameState currstate = { currboard, paths[currboard] };
        vector<GameState> nextStates = genNextStates(currstate);
        for (const auto& next : nextStates) {
            if (!visited[next.board]) {
                visited[next.board] = true;
                paths[next.board] = next.path;
                myqueue.insert(stoi(next.board));
            }
        }
    }
    return {};
}

int main(int argc, char* argv[]) {
    setlocale(LC_CTYPE, "RU");
    if (argc < 2) {
        return 1;
    }
    string start = argv[1];
    cout << "Решение игры 8 для начального состояния: " << start << endl;
    vector<string> sol = game8(start);
    if (sol.empty()) {
        cout << "Решение не найдено" << endl;
    }
    else {
        cout << "Решение найдено за  " << sol.size() - 1 << " шагов:" << endl;
        cout << "Последовательность:" << endl;
        ofstream out(argv[2]);
        if (out.is_open()) {
            for (const string& state : sol) {
                cout << state << endl;
                out << state << endl;
            }
        }
        cout << endl << "Визуализация:" << endl;
        for (size_t i = 0; i < sol.size(); i++) {
            cout << "Шаг " << i << ":" << endl;
            string board = sol[i];
            for (size_t j = 0; j < 3; j++) {
                for (size_t k = 0; k < 3; k++) {
                    char c = board[j * 3 + k];
                    if (c == '0') {
                        cout << ". ";
                    }
                    else {
                        cout << c << " ";
                    }
                }
                cout << endl;
            }

            cout << "------" << endl;
        }
    }
    return 0;
}
