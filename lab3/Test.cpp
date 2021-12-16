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
    cout << "Start spots:(-1 -1 to stop)" << endl;
    while (true)
    {
        int a, b;
        cin >> a >> b;
        if (a < 0) break;
        coords.insert( pair<int,int>(a, b));

        board[a][b] = 1;
    }

    unsigned k = 0;
    while (!coords.empty())
    {
        pair<int, int> curr = coords.get();
        unsigned intensity = board[curr.first][curr.second];
        coords.remove();
        k++;
        if (curr.first > 0 && board[curr.first - 1][curr.second] == 0) {
           board[curr.first - 1][curr.second] = intensity + 1;
           k++;
        }
        if (curr.first < N - 1 && board[curr.first + 1][curr.second] == 0) {
          board[curr.first + 1][curr.second] = intensity  + 1;
            k++;
        }
        if (curr.second > 0 && board[curr.first][curr.second - 1] == 0) {
            board[curr.first][curr.second - 1] = intensity + 1;
            k++;
        }
        if (curr.second < M - 1 && board[curr.first][curr.second + 1] == 0) {
            board[curr.first][curr.second + 1] = intensity + 1;
            k++;
        }

    }
    cout << k;
}
/*Enter N M:
3 3
Start spots:(-1 -1 to stop)
1 1
-1 -1
5
 */