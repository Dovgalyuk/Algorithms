#include "vector.h"
#include "queue.h"

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

int main(int argc, char* argv[])
{
    if (argc != 3)
        return 1;

    std::ifstream input(argv[1]);
    std::ofstream output(argv[2]);

    std::vector<std::string> board;
    std::string line;
    while (std::getline(input, line))
        if (!line.empty())
            board.push_back(line);

    int n = (int)board.size();
    int m = (int)board[0].size();

    int startR = -1, startC = -1;
    int endR = -1, endC = -1;

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
        {
            if (board[i][j] == 'K')
            {
                startR = i;
                startC = j;
            }
            else if (board[i][j] == 'E')
            {
                endR = i;
                endC = j;
            }
        }

    const int dr[8] = { -2,-2,-1,-1, 1, 1, 2, 2 };
    const int dc[8] = { -1, 1,-2, 2,-2, 2,-1, 1 };

    std::vector<std::vector<int>> parent(n, std::vector<int>(m, -1));
    Queue<std::pair<int,int>> q;

    q.insert({startR, startC});
    parent[startR][startC] = -2;

    while (!q.empty())
    {
        auto pos = q.get(); q.remove();
        int r = pos.first;
        int c = pos.second;

        if (r == endR && c == endC)
            break;

        for (int k = 0; k < 8; ++k)
        {
            int nr = r + dr[k];
            int nc = c + dc[k];

            if (nr < 0 || nr >= n || nc < 0 || nc >= m)
                continue;
            if (board[nr][nc] == '#')
                continue;
            if (parent[nr][nc] != -1)
                continue;

            parent[nr][nc] = r * m + c;
            q.insert({nr, nc});
        }
    }

    std::vector<int> path;
    int cur = endR * m + endC;

    while (cur != -2)
    {
        path.push_back(cur);
        int r = cur / m;
        int c = cur % m;
        cur = parent[r][c];
    }

    std::reverse(path.begin(), path.end());

    for (int i = 0; i < (int)path.size(); ++i)
    {
        int r = path[i] / m;
        int c = path[i] % m;
        board[r][c] = char('0' + (i % 10));
    }

    for (int i = 0; i < n; ++i)
    {
        output << board[i];
        if (i + 1 < n)
            output << '\n';
    }

    return 0;
}
