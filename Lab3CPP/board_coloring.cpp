#include <cstdio>
#include <cstdlib>
#include "queue.h"
#include "vector.h"

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        return 1;
    }
    
    FILE *input = fopen(argv[1], "r");
    if (input == nullptr)
    {
        return 1;
    }
    
    int N, M;
    if (fscanf(input, "%d %d", &N, &M) != 2)
    {
        fclose(input);
        return 1;
    }
    
    // Создаём доску (0 = не покрашено, >0 = номер цвета)
    Vector *board = vector_create();
    vector_resize(board, N * M);
    
    // Инициализируем доску нулями (все клетки не покрашены)
    for (int i = 0; i < N * M; ++i)
    {
        vector_set(board, i, 0);
    }
    
    // Создаём очередь для обхода в ширину (BFS)
    Queue *queue = queue_create();
    
    // Читаем начальные покрашенные клетки (цвет 1)
    int row, col;
    while (fscanf(input, "%d %d", &row, &col) == 2)
    {
        // Переводим координаты в нумерацию с нуля
        row--;
        col--;
        
        if (row >= 0 && row < N && col >= 0 && col < M)
        {
            int idx = row * M + col;
            vector_set(board, idx, 1);
            
            // Кодируем координаты в одно число: строка * 10000 + столбец (предполагаем, что N, M < 10000)
            int encoded = row * 10000 + col;
            queue_insert(queue, encoded);
        }
    }
    
    fclose(input);
    
    // Направления движения: вверх, вниз, влево, вправо
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};
    
    // Обход в ширину: обрабатываем очередь, пока она не опустеет
    while (!queue_empty(queue))
    {
        int encoded = queue_get(queue);
        queue_remove(queue);
        
        int row = encoded / 10000;
        int col = encoded % 10000;
        int idx = row * M + col;
        int current_color = vector_get(board, idx);
        
        // Проверяем всех соседей текущей клетки
        for (int d = 0; d < 4; ++d)
        {
            int new_row = row + dr[d];
            int new_col = col + dc[d];
            
            // Проверяем, что координаты в пределах доски
            if (new_row >= 0 && new_row < N && new_col >= 0 && new_col < M)
            {
                int new_idx = new_row * M + new_col;
                int neighbor_color = vector_get(board, new_idx);
                
                // Если сосед не покрашен, красим его следующим цветом
                if (neighbor_color == 0)
                {
                    int new_color = current_color + 1;
                    vector_set(board, new_idx, new_color);
                    
                    // Добавляем соседа в очередь для дальнейшей обработки
                    int new_encoded = new_row * 10000 + new_col;
                    queue_insert(queue, new_encoded);
                }
            }
        }
    }
    
    // Ищем максимальный цвет на доске
    int max_color = 0;
    for (int i = 0; i < N * M; ++i)
    {
        int color = vector_get(board, i);
        if (color > max_color)
        {
            max_color = color;
        }
    }
    
    printf("%d\n", max_color);
    
    queue_delete(queue);
    vector_delete(board);
    
    return 0;
}

