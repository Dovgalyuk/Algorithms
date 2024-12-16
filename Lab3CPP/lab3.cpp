#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include "list.h"
#include "queue.h"
#include "vector.h"


void task1(std::string board[8], int prevX[8][8], int prevY[8][8], int dist[8][8], int start_x,int start_y)
{
    Queue* queue = queue_create();
    const int dx[8] = {1, 1, 2, 2, -1, -1, -2, -2};
    const int dy[8] = {2, -2, 1, -1, 2, -2, 1, -1};
    
    dist[start_y][start_x] = 0;

    //std::cout << "\nstart: " << start_x << " "<< start_y << "\n";
    //std::cout << "\nend: " << end_x<< " " << end_y << "\n";

    queue_insert(queue, start_y);
    queue_insert(queue, start_x);

    while(!queue_empty(queue)) {
        int tx, ty, nx = -1, ny = -1;
        tx = queue_get(queue);
        //std::cout << "\n"<< tx;
        queue_remove(queue);
        ty = queue_get(queue);
        //std::cout << " " <<ty << "\n";
        queue_remove(queue);
        for (int i = 0; i < 8; ++i) {
            nx = tx + dx[i];
            ny = ty + dy[i];

            if (nx >= 0 && nx < 8 && ny >= 0 && ny < 8 && board[nx][ny] != '#' && dist[nx][ny] == -1) {
                dist[nx][ny] = dist[tx][ty] + 1;
                prevX[nx][ny] = tx;
                prevY[nx][ny] = ty;
                //std::cout << "\n" << tx << ", " << ty << " -> " << nx << ", " << ny;
                queue_insert(queue, nx);
                queue_insert(queue, ny);
            }
        }

    }
    //std::cout << "\n\n";
    //for(int i = 0; i < 8; i ++) {
    //    for(int j = 0; j < 8; j ++) {
    //    std::cout << dist[i][j] << " ";
    //}
    //std::cout << "\n";
    //}
    //for(int i = 0; i < 8; i ++) {
    //    for(int j = 0; j < 8; j ++) {
    //    std::cout << prevX[i][j] << " ";
    //}
    //std::cout << "\n";
    //}
    //std::cout << "\n\n\n";
    //for(int i = 0; i < 8; i ++) {
    //    for(int j = 0; j < 8; j ++) {
    //    std::cout << prevY[i][j] << " ";
    //}
    //std::cout << "\n";
    //}
    queue_delete(queue);

}

void task1_b(int startX, int startY, int endX, int endY, int prevX[8][8], int prevY[8][8], std::string board[8], int dist[8][8]) {
    int currentX = endX;
    //std::cout << currentX;
    int currentY = endY;
    
    //std::cout << currentY;
    Vector* pathX = vector_create();
    Vector* pathY = vector_create();

    while (!(currentX == startX && currentY == startY)) {
        vector_resize(pathX, vector_size(pathX) + 1);
        vector_resize(pathY, vector_size(pathY) + 1);
        vector_set(pathX, vector_size(pathX) - 1, currentX);
        vector_set(pathY, vector_size(pathY) - 1, currentY);
        //std::cout << "\n" << vector_get(pathX, vector_size(pathX) - 1);
        
        //std::cout << ", " << vector_get(pathY, vector_size(pathY) - 1);
        int tempX = currentX;
        currentX = prevX[currentX][currentY];
        currentY = prevY[tempX][currentY];
    }
    //std::cout << "\n";

    vector_resize(pathX, vector_size(pathX) + 1);
    vector_resize(pathY, vector_size(pathY) + 1);
    vector_set(pathX, vector_size(pathX) - 1, startX);
    vector_set(pathY, vector_size(pathY) - 1, startY);

    for (size_t i = vector_size(pathX); i > 0; --i) {
        int x = vector_get(pathX, i - 1);
        int y = vector_get(pathY, i - 1);
        int tmp = 48 + dist[x][y];
        board[x][y] = char(tmp);
    }

    vector_delete(pathX);
    vector_delete(pathY);
}

int main(int argc, char **argv)
{
    //std::ifstream input("input.txt");
    if(argc != 2) return 1;
    std::ifstream input(argv[1]);
	if (input.is_open()) {
        const int N = 8;
        std::string board[8];
        int dist[N][N];
        int prevX[N][N];
        int prevY[N][N];
        int start_x = 0, start_y = 0, end_x = 0, end_y = 0, lines=0;

        while ((input >> board[lines])) {
	        std::cout << "\n" << board[lines];
            for(long unsigned int i = 0; i < std::size(board[lines]); i++) {
                if(board[lines][i] == 'K') {
                    start_x = i;
                    start_y = lines;
                    board[lines][i] = '0';
                }
                if(board[lines][i] == 'E') {
                    end_x = i;
                    end_y = lines;
                    board[lines][i] ='0';
                }
            }
            lines++;
        }

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                dist[i][j] = -1;
            }
        }

	    task1(board, prevX, prevY, dist, start_x, start_y);
        task1_b(start_y, start_x, end_y, end_x, prevX, prevY, board, dist);

        std::cout << "\n\n";
        for (int i = 0; i < N; ++i) {
        std::cout << board[i] << std::endl;
        }
    }
	input.close();
    	return 0;
}
