#include <iostream>
#include "queue.h"
using namespace std;

int main()
{
    cout << "Enter N M: " << endl;
    int N, M;
    cin >> N >> M;
    Queue<std::pair<int, int>> coords;
    int** board = new int*[N];
    for (int i = 0; i < N; ++i) {
        board[i] = new int[M] {0};
    }
    cout << "Start spots:(0 0 to stop)" << endl;
    while (true)
    {
        int a, b;
        cin >> a >> b;
        if (a == 0) break;
        coords.insert( pair<int,int>(a - 1, b - 1));

        board[a - 1][b - 1] = 1;
    }

    unsigned k = 0;
    while (!coords.empty())
    {
        pair<int, int> curr = coords.get();
        unsigned intensity = board[curr.first][curr.second];
        coords.remove();

        if (curr.first > 0 && board[curr.first - 1][curr.second] == 0) {
            coords.insert(pair<int,int>(curr.first - 1, curr.second));
            board[curr.first - 1][curr.second] = board[curr.first][curr.second] + 1;
            if (k < board[curr.first - 1][curr.second]) {
                k = board[curr.first - 1][curr.second];
            }
        }
        int l = board[curr.first + 1][curr.second];
        if (curr.first < N - 1 && board[curr.first + 1][curr.second] == 0) {
            coords.insert(pair<int,int>(curr.first + 1, curr.second));
            board[curr.first + 1][curr.second] = board[curr.first][curr.second] + 1;
            if (k < board[curr.first + 1][curr.second]) {
                k = board[curr.first + 1][curr.second];
            }
        }
        if (curr.second > 0 && board[curr.first][curr.second - 1] == 0) {
            coords.insert(pair<int,int>(curr.first, curr.second - 1));
            board[curr.first][curr.second - 1] = board[curr.first][curr.second] + 1;
            if (k < board[curr.first][curr.second - 1]) {
                k = board[curr.first][curr.second - 1];
            }
        }
        if (curr.second < M - 1 && board[curr.first][curr.second + 1] == 0) {
            coords.insert(pair<int,int>(curr.first, curr.second + 1));
            board[curr.first][curr.second + 1] = board[curr.first][curr.second] + 1;
            if (k < board[curr.first][curr.second + 1]) {
                k = board[curr.first][curr.second + 1];
            }
        }
    }
    cout << k;
}