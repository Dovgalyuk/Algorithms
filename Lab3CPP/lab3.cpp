#include <iostream>
#include <string>
#include <fstream>
#include "queue.h"
#include "vector.h"

const int INF = 1e9;

struct Point
{
    int x;
    int y;
 
    Point() : x(0), y(0) {} 
    Point(int x, int y) : x(x), y(y) {} 
};

const int move_size = 8;
const Point move[move_size] = {Point(-1, -1), Point(-1, 0), Point(-1, 1), Point(0, -1), Point(0, 1), Point(1, -1), Point(1, 0), Point(1, 1)};

int bfs(Vector* vector, int height, int width, Point start, Point end)
{
    Vector* dist = vector_create();
    vector_resize(dist, height * width);

    Vector* count = vector_create();
    vector_resize(count, height * width);

    for(int i = 0; i < height * width; i++) 
    {
        vector_set(dist, i, INF);
        vector_set(count, i, 0);
    }

    Queue* queue = queue_create();

    int startIndex = start.y * width + start.x;
    int endIndex = end.y * width + end.x;
    
    vector_set(dist, startIndex, 0);
    vector_set(count, startIndex, 1);
    queue_insert(queue, startIndex);
    
    while(!queue_empty(queue)) 
    {
        int current = queue_get(queue);
        queue_remove(queue);

        int cur_x = current % width;
        int cur_y = current / width;

        int cur_dist = vector_get(dist, current);

        for(int i = 0; i < move_size; i++)
        {
            int x = move[i].x;
            int y = move[i].y;
            
            int new_x = cur_x + x;
            int new_y = cur_y + y;
            
            while(!(new_x < 0 || new_x >= width || new_y < 0 || new_y >= height)) 
            {
                int newIndex= new_y * width + new_x;
                char c = (char)vector_get(vector, newIndex);
            
                if(c == '#')
                {
                    break;
                }
                
                int new_dist = cur_dist + 1;
                int old_dist = vector_get(dist, newIndex);
                
                if(new_dist < old_dist)
                {
                    vector_set(dist, newIndex, new_dist);
                    int new_count = vector_get(count, current);
                    vector_set(count, newIndex, new_count);
                    queue_insert(queue, newIndex);
                }
                else if(new_dist == old_dist)
                {
                    int new_count = vector_get(count, newIndex) + vector_get(count, current);
                    vector_set(count, newIndex, new_count);
                }
                
                new_x += x;
                new_y += y;
            }
        }
    }

    int result = vector_get(count, endIndex);

    vector_delete(dist);
    vector_delete(count);
    queue_delete(queue);

    return result;
}

void task(std::ifstream& file)
{ 
    Vector* vector = vector_create();
   
    int height = 0, width = 0;
    std::string line;
    Point start, end;

    while(std::getline(file, line))
    {
        if(width == 0) 
        {
            width = line.size();
        }

        vector_resize(vector, (height + 1) * width);

        for(int x = 0; x < width; x++)
        {
            char c = line[x];
            vector_set(vector, height * width + x, (Data)c);
            
            if(c == 'Q')
            {
                start = Point(x, height);
            }
            else if(c == 'E')
            {
                end = Point(x, height);
            }
        }

        height++;
    }

    int result = bfs(vector, height, width, start, end);
    std::cout << result << std::endl;
    
    vector_delete(vector);
}

int main(int argc, char **argv)
{
    std::ifstream file(argv[1]);
    task(file);
    file.close();
}
