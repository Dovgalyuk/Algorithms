#include <iostream>
#include <stdexcept>
#include "queue.h"
#include "vector.h"
#include <string>
#include <fstream>
using namespace std;

typedef pair<size_t,size_t> Point;
typedef Vector<Vector<int>> Matrix;
typedef Vector<string> Maze;

Matrix create_distance_matrix(const Maze &maze)
{

    if (maze.size() == 0 )
    {
        return Matrix();
    }
    
    size_t rows = maze.size();
    size_t cols = maze.get(static_cast<size_t>(0)).size();
    for (size_t i = 1; i < maze.size(); i++)
    {
        if (maze.get(i).size()!=cols)
        {
            return Matrix();
        }
    }
    Matrix distances;
    distances.resize(rows);

    for (size_t i = 0; i < rows; i++)
    {
        Vector<int> row_vector;

        row_vector.resize(cols);
        for (size_t j = 0; j < cols; j++)
        {
            row_vector.set(j, -1);
        }
        distances.set(i,row_vector);
    }

    return distances;
}
bool isTrue(int next_i, int next_j, const Maze &maze)
{
    if (next_i < 0 || next_i >= static_cast<int>(maze.size()))
    {
        return false;
    }
    if (next_j < 0 || next_j >= static_cast<int>(maze.get(0).size()))
    {
        return false;
    }
    string text = maze.get(static_cast<size_t>(next_i));
    if (text[next_j]== '#')
    {
        return false;
    }
    return true;
}
void change_maze(Maze &maze, Vector<Point> &indexes, Matrix &dis)
{
    for (size_t i=0;i<indexes.size();i++)
    {
        size_t row_index=indexes.get(i).first;
        size_t cowl_index = indexes.get(i).second;
        // Если мы нашли дистанцию меньше то
        // Мне нужно изменить по индексу значение лабиринта
        // Допустим до выхода была дисданция 2 то мне нужно по индексу где был E сделать + 1
        string text = maze.get(row_index);
        // и устанавливаю в текущем столмце текущее дистанцию +1
        string temp = to_string(dis.get(row_index).get(cowl_index));
        if (!temp.empty())
        {
            text[cowl_index]=temp[0];
        }
        //Теперь нужно установать новую строку новому лабиринту
        maze.set(row_index, text);
    }

    for (size_t i= 0;i<maze.size();i++)
    {
        string text = maze.get(i);
        for (size_t j = 0; j < text.size();j++)
        {
            cout<<text[j];
        }
        cout<<endl;
    }
}
Vector<Point> rebuild_way(Matrix &dis, Point indext_exit, const Maze &maze)
{
    
    int i_dis[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int j_dis[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    
    Vector<Point> way;
  
    way.resize(way.size() + 1);
    way.set(way.size() - 1, indext_exit); // Добавляю первый индекс (Е - выход)
    while (dis.get(indext_exit.first).get(indext_exit.second)>0) //Идем по волнам пока не будет 0 
    {
        size_t exit_i = indext_exit.first;
        size_t exit_j = indext_exit.second;
        bool isFound = false;
        for (size_t k = 0; k < 8; k++)
        {
            int next_i = exit_i + i_dis[k];             // Получаем соседа по i
            int next_j = exit_j + j_dis[k];             // Получаем соседа по j
            while (isTrue(next_i, next_j, maze))
            {
                if (dis.get(exit_i).get(exit_j) - 1 == dis.get(next_i).get(next_j))
                {

                    indext_exit = make_pair(next_i, next_j);
                    way.resize(way.size() + 1);
                    way.set(way.size() - 1, indext_exit);
                    isFound = true;
                    break;
                }

                next_i += i_dis[k];
                next_j += j_dis[k];
            }
            
        }
        if (!isFound)
        {
            break;
        }
        
    }

    return way;
}

Point bfs(const Maze &maze, Matrix &dis, Queue<Point> &d) // НАЧИНАЕМ ПОИСК В ШИРИНУ
{
    //Направления куда идти
    int i_dis []= {-1,-1,-1,0,0,1,1,1};
    int j_dis [] = {-1,0,1,-1,1,-1,0,1};
   
    while (!d.empty()) //Идем по всей очереди
    {
        auto cells = d.get();
        d.remove();
        size_t i = cells.first;  // Получаем интексы текущего обработки
        size_t j = cells.second; // Получаем интексы текущего обработки
        string text = maze.get(i); //Получаем символ по индексу 
        //Проверяем если мы нашли выход
        if (text [j] == 'E')
        {
            auto the_exit = make_pair(i,j);;
            return the_exit;
        }

        for (size_t k = 0; k < 8;k++)
        {
            int next_i = cells.first + i_dis[k]; 
            int next_j = cells.second + j_dis[k]; 
            //Циклом проверяем могу ли я проходить по соседям
            while (isTrue(next_i, next_j, maze))
            {
                //Если мы посещали то пропускаем
                if (dis.get(static_cast<size_t>(next_i)).get(static_cast<size_t>(next_j)) != -1)
                {
                    break;
                }
                
                Vector<int> row = dis.get(next_i); //Получаем улицу соседей 
                row.set(next_j, dis.get(i).get(j) + 1) ; //И меняем соседа к которому только что зашли  
                dis.set(next_i,row);
                d.insert(make_pair(static_cast<size_t>(next_i), static_cast<size_t>(next_j)));

                next_i += i_dis[k];
                next_j += j_dis[k];
            }
            
        }
    }
    return make_pair(static_cast<size_t>(-1), static_cast<size_t>(-1));
}

int main (int argc, char *argv[])
{

    Maze maze;
    string line;
    if (argc <2)
    {
        cerr << "Error: File not specified "<<endl;
        return 1;
    }
    ifstream counter(argv[1]);
    if (!counter.is_open())
    {
        cerr<<"Error: Cannot open the file "<<argv[1]<<endl;
        return 1;
    }
    size_t line_counter =0;
    while (getline(counter,line))
    {
        line_counter++;
    }
    maze.resize(line_counter);
    counter.close();
    ifstream reader(argv[1]);
    if (!reader.is_open())
    {
        cerr << "Error: Cannot open the file " << argv[1] << endl;
        return 1;
    }
    size_t index = 0;
    while (getline(reader, line))
    {
        if (!line.empty() && (line.back() == '\r' || line.back() == '\n' || line.back() == '\t'))
        {
            line.pop_back();
        }
            maze.set(index, line);
        index++;
    }
    reader.close();
   
    Matrix m = create_distance_matrix(maze);
    if (m.size()==0)
    {
        cout << "Error"<<endl;
        return 1;
    }
    Queue<Point> d;
    bool isFind = false;
    for (size_t i = 0; i < maze.size(); i++)
    {
        string text = maze.get(i);
        for (size_t j = 0; j < maze.get(i).size(); j++)
        {
            if (text[j] == 'Q')
            {
                d.insert(make_pair(i, j));
                Vector<int> row = m.get(i);
                row.set(j,0);
                m.set(i,row);
                isFind=true;
            }
            
        }
        if (isFind)
        {
            break;
        }
    }
    const size_t ERROR = static_cast<size_t>(-1);
    Point indext_exit = bfs(maze, m, d);
    if (indext_exit.first == ERROR)
    {
        cout<<"Error: Exit not found "<<endl;
        return 1;
    }
  
    Vector<Point> box = rebuild_way(m, indext_exit, maze);
    change_maze(maze, box, m);
    return 0;
}
