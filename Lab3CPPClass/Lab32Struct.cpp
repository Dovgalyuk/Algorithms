#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <unordered_map>
#include "queue.h"

using namespace std;

struct GameState {
    string board;
    char move;
    int prev_index;
};

const int dx[4] = { 0, 0, -1, 1 };
const int dy[4] = { -1, 1, 0, 0 };
const char moves[4] = { 'u', 'd', 'l', 'r' };

vector<GameState> genNextStates(const string& board) {
    vector<GameState> nextStates;
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
            nextStates.push_back({ newBoard, moves[i], -1 });
        }
    }
    return nextStates;
}

string getpath(const unordered_map<int, GameState>& states, int tindex) {
    string path;
    int currindex = tindex;
    while (currindex != -1 && states.at(currindex).move != '\0') {
        path = states.at(currindex).move + path;
        currindex = states.at(currindex).prev_index;
    }
    return path;
}

vector<string> game8(const string& start) {
    Queue myqueue;
    unordered_map<string, int> visited;
    unordered_map<int, GameState> states;
    const string target = "123456780";
    int nextindex = stoi(start);
    states[nextindex] = { start, '\0', -1 };
    visited[start] = nextindex;
    myqueue.insert(nextindex);
    while (!myqueue.empty()) {
        int currindex = myqueue.get();
        myqueue.remove();
        GameState curr_state = states[currindex];
        if (curr_state.board == target) {
            string path = getpath(states, currindex);
            vector<string> result;
            string currboard = start;
            result.push_back(currboard);
            for (char move : path) {
                int empos = (int)currboard.find('0');
                int x = empos % 3;
                int y = empos / 3;
                switch (move) {
                case 'u':
                    y--;
                    break;
                case 'd':
                    y++;
                    break;
                case 'l':
                    x--;
                    break;
                case 'r':
                    x++;
                    break;
                }
                int newpos = y * 3 + x;
                swap(currboard[empos], currboard[newpos]);
                result.push_back(currboard);
            }
            return result;
        }
        vector<GameState> nextStates = genNextStates(curr_state.board);
        for (const auto& next : nextStates) {
            if (visited.find(next.board) == visited.end()) {
                nextindex = stoi(next.board);
                states[nextindex] = { next.board, next.move, currindex };
                visited[next.board] = nextindex;
                myqueue.insert(nextindex);
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
        cout << "Решение найдено за " << sol.size() - 1 << " шагов:" << endl;
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