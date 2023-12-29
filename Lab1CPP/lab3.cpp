/*
Задан неориентированный граф. Написать программу для определения кратчайшего пути от одной вершины для другой. 
В первой строке входного файла записано количество вершин, номер стартовой вершины и номер финишной. 
В последующих строках идут описания ребер, заданные номерами вершин, которые они соединяют. 
В выходной файл выводится последовательность вершин в кратчайшем пути. 
Если решения не существует – выводится IMPOSSIBLE. 
Программа должна использовать поиск в ширину на основе очереди.

Входные данные

4 1 2
1 3
1 4
3 2
4 3

Выходные данные

1 3 2

*/

#include <iostream>
#include <string>
#include <fstream>

#include "queue.h"
#include "list.h"

using namespace std;


List** input (Data &n, Data &start, Data &finish, List** list) 
{
    ifstream fin( "..\\..\\..\\Lab1CPP\\input.txt");
    bool flag = true;
    if (fin.is_open()) {
        char buf [16];
        fin >> buf;
        n = stoi(buf);
        fin >> buf;
        start = stoi(buf);
        fin >> buf;
        finish = stoi(buf);
        if (start > n || finish > n) {
            flag = false;
        }
        if (flag) { 
            list = new List* [n];
            for (Data i = 0; i < n; i++)
            {
                list[i] = list_create();
            }
            
            while (fin >> buf) {
                int num = stoi(buf);
                fin >> buf;
                int num2 = stoi(buf);
                if (num > n || num2 > n) {
                    flag = false;
                    break;
                }
                list_insert(list[num-1], num2);
                list_insert(list[num2-1], num);
            }
        }
    }
    if (!flag && list) {
        for(Data i = 0; i < n; i++) {
            list_delete(list[i]);
        }
        delete[] list;
        list = nullptr;
    }
    fin.close();
    return list;
}

bool check_value(const Data n, Data child_element, const bool* visited_nodes, const Data* parents) 
{
    // проверка вершины на пройденность
    if (visited_nodes[--child_element] == true) {
        return false;
    }           
    //проверка на одинакового родителя двух вершин
    Data data = parents[child_element];
    for (Data i = 0; i < n; i++) 
    {
        Data num = parents[i];
        if (num != 0 && data == num && i != child_element) {
            return false;
            break;
        }
    }
    return true;
}

List* find_shortest_road(const Data n, const Data start, const Data finish, List** adj_list) 
{
    Queue* queue = queue_create();
    List* road = list_create();
    Data* parents = new Data[n] {};
    bool* visited_nodes = new bool[n] {};
    queue_insert(queue, start);
    //обход графа
    while (!queue_empty(queue))
    {    
        Data parent_element = queue_get(queue);
        List* neightbours = adj_list[parent_element - 1];
        visited_nodes[parent_element-1] = 1; 

        queue_remove(queue);

        for (ListItem* item = list_first(neightbours); item; item = list_item_next(item)) 
        {
            Data child_element = list_item_data(item);
            if (parent_element == start || check_value(n, child_element, visited_nodes, parents)) 
            {
                if (parents[child_element - 1] == 0) {
                    parents[child_element - 1] = parent_element;
                }
                if (parent_element != child_element) { 
                    queue_insert(queue, child_element);
                }
            }
        }
        if (parent_element == finish) {
            break;
        }
    }

    if (start == finish) {
        if (parents[start - 1] != 0) {
            list_insert(road, parents[start - 1]);
            list_insert(road, parents[start - 1]);
        }
    }
    else {
        Data iter = finish;
        // если существует путь до точки
        if (parents[iter - 1] != 0) {
            list_insert(road, iter);
            while (iter != 0 && iter != start) {
                iter = parents[iter - 1];
                list_insert(road, iter);  
            }
        }
    } 
    
    queue_delete(queue);
    delete[] parents;
    delete[] visited_nodes;
    return road;
}

void output(List* road) {
    ofstream fout;
    fout.open(("..\\..\\..\\Lab1CPP\\output.txt"));
    if (road && list_first(road)) {
        for (ListItem* item = list_first(road); item; item = list_item_next(item)){
            fout << list_item_data(item) << " ";
        }

    } else {
        fout << "IMPOSSIBLE";
    }
    fout.close();
}

int main()
{
    List** adj_list = nullptr;
    List* road = nullptr;
    Data n = 0;
    Data start = 0, finish = 0;
    adj_list = input(n, start, finish, adj_list);
    if (adj_list){
        road = find_shortest_road (n, start, finish, adj_list);
        for (int i = 0; i < n; i++) {
            list_delete(adj_list[i]);
        }
        delete[] adj_list;      
    }
    output(road);
    if (road) {
        list_delete(road);
    }
    return 0;
}
