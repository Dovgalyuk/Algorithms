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

    int n = static_cast<int>(board.size());
    int m = static_cast<int>(board[0].size());

    int startR = -1, startC = -1;
    int endR = -1, endC = -1;

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            if (board[i][j] == 'K') 
            { 
                startR = i; 
                startC = j;
            }
            if (board[i][j] == 'E') 
            {
                endR = i;
                endC = j;
            }
        }
    }

    const int dr[8] = { -2,-2,-1,-1,1,1,2,2 };
    const int dc[8] = { -1,1,-2,2,-2,2,-1,1 };

    std::vector<std::vector<int>> parent(n, std::vector<int>(m, -1));
    std::vector<std::vector<bool>> visited(n, std::vector<bool>(m, false));
    Queue<std::pair<int,int>> q;
    q.insert({startR, startC});
    visited[startR][startC] = true;

    while (!q.empty())
    {
        auto pos = q.get(); q.remove();
        int r = pos.first;
        int c = pos.second;

        if (r == endR && c == endC)
            break;

        for (int k = 0; k < 8; ++k)
        {
            int nr = r + dr[k], nc = c + dc[k];

            if (nr < 0 || nr >= n || nc < 0 || nc >= m)
                continue;
                
            if (board[nr][nc] == '#' || visited[nr][nc])
                continue;

            visited[nr][nc] = true;
            parent[nr][nc] = r * m + c;
            q.insert({nr, nc});
        }
    }

    std::vector<int> path;
    int cur = endR * m + endC;
    while (cur != -1)
    {
        path.push_back(cur);
        int r = cur / m;
        int c = cur % m;
        cur = parent[r][c];
    }
    std::reverse(path.begin(), path.end());

    for (size_t step = 0; step < path.size(); ++step)
    {
        int flat = path[step];
        int r = flat / m;
        int c = flat % m;
        board[r][c] = char('0' + (step % 10));
    }

    for (size_t i = 0; i < board.size(); ++i)
    {
        output << board[i];
        if (i + 1 < board.size()) output << '\n';
    }

    return 0;
}
