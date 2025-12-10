#include "vector.h"
#include "queue.h"

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

struct Pos
{
    int r, c;
};

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

    Pos start{-1,-1}, end{-1,-1};
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            if (board[i][j] == 'K')
                start = {i,j};
            if (board[i][j] == 'E')
                end = {i,j};
        }
    }
        

    const int dr[8] = { -2,-2,-1,-1,1,1,2,2 };
    const int dc[8] = { -1,1,-2,2,-2,2,-1,1 };

    std::vector<int> parent(n*m, -1);
    auto id = [&](int r,int c){ return r*m+c; };
    std::vector<char> visited(n*m, 0);

    Queue<Pos> q;
    q.insert(start);
    visited[id(start.r,start.c)] = 1;

    while (!q.empty())
    {
        Pos cur = q.get(); q.remove();
        if (cur.r == end.r && cur.c == end.c)
            break;

        for (int k=0;k<8;k++)
        {
            int nr=cur.r+dr[k], nc=cur.c+dc[k];
            if (nr<0||nr>=n||nc<0||nc>=m)
                continue;

            if (board[nr][nc]=='#')
                continue;

            if (visited[id(nr,nc)])
                continue;

            visited[id(nr,nc)] = 1;
            parent[id(nr,nc)] = id(cur.r,cur.c);
            q.insert({nr,nc});
        }
    }

    std::vector<int> path;
    for (int cur=id(end.r,end.c); cur!=-1; cur=parent[cur])
        path.push_back(cur);
    std::reverse(path.begin(), path.end());

    for (size_t i=0;i<path.size();i++)
    {
        int flat = path[i];
        int r = flat / m, c = flat % m;
        board[r][c] = char('0' + i%10);
    }

    for (size_t i = 0; i < board.size(); ++i)
    {
        output << board[i];
        if (i + 1 < board.size()) output << '\n';
    }

    return 0;
}
