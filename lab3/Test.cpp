#include <iostream>
#include "queue.h"
using namespace std;
unsigned board[100][100];
typedef Queue<int> queue;
int main()
{

    cout << "Enter N M: " << endl;
    int N, M;
    cin >> N >> M;
    queue x_queue ;
    queue y_queue ;
    cout << "Start spots:(0 0 to stop)" << endl;
    while (true)
    {
        int a, b;
        cin >> a >> b;
        if (a == 0) break;
        x_queue.insert( a - 1);
        y_queue.insert( b - 1);

        board[a - 1][b - 1] = 1;
    }

    unsigned k = 0;
    while (!x_queue.empty())
    {
        int x_start = x_queue.get();
        int y_start = y_queue.get();
        unsigned intensity = board[x_start][y_start];

        x_queue.remove();
        y_queue.remove();
        for (int i = -1; i <= 1; i++)
        {
            for (int j = -1; j <= 1; j++)
            {
                if (i * i + j * j != 0 && i * j == 0)
                {
                    int x = x_start + i;
                    int y = y_start + j;
                    if (x < 0 || y < 0 || x >= N || y >= M)
                    {
                        continue;
                    }
                    if (board[x][y] == 0)
                    {
                        k = intensity + 1;
                        board[x][y] = k;

                        x_queue.insert( x);
                        y_queue.insert( y);
                    }
                }

            }
        }
    }
    cout << k;
}