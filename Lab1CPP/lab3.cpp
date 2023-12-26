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

bool check_value(const Data n, Data child_element, bool* visited_nodes, Data* parents) 
{
    bool flag = true;
    // проверка вершины на пройденность
    if (visited_nodes[--child_element] == true) {
        flag = false;
    }     
    if (flag) {
        //проверка на одинакового родителя двух вершин
        Data data = parents[child_element];
        for (Data i = 0; i < n; i++) 
        {
            Data num = parents[i];
            if (num != 0 && data == num && i != child_element) {
                flag = false;
                break;
            }
        }
    }
    return flag;
}

List* find_shortest_road(const Data n, Data start, Data finish, List** adj_list) 
{
    Queue* queue = queue_create();
    List* road = list_create();
    Data* parents = new Data[n];
    bool* visited_nodes = new bool[n];
    //инициализация массива родителей
    for (Data i = 0; i < n; i++)
    {
        parents[i] = 0;
    }
    queue_insert(queue, start);
    //обход графа
    while (!queue_empty(queue))
    {    
        Data parent_element = queue_get(queue);
        queue_remove(queue);
        list_insert(road, parent_element);
        visited_nodes[parent_element-1] = 1;
        bool dead_end_node = true;
        List* neightbours = adj_list[parent_element - 1]; 
        for (ListItem* item = list_first(neightbours); item; item = list_item_next(item)) 
        {
            Data child_element = list_item_data(item);
            if (parent_element == start || check_value(n, child_element, visited_nodes, parents)) 
            {
                if ( !(start == finish && parent_element != child_element)) dead_end_node = false;
                if (parents[child_element - 1] == 0) {
                    parents[child_element - 1] = parent_element;
                }
                queue_insert(queue, child_element);
            }
        }
        if (dead_end_node) {
            list_erase_first(road);
        }

        if (parent_element == finish) {
            if (list_first(road) && list_item_data(list_first(road)) != finish) {
                list_insert(road, finish);
            }
            break;
        } 
    }
    for (Data i = 0; i < n; i++)
    {
        cout << parents[i] << endl;
    }
    queue_delete(queue);
    delete[] parents;
    delete[] visited_nodes;
    if (list_first(road) == nullptr) {
        list_delete(road);
        road = nullptr;
    }
    return road;
}

Data reverse_output(ListItem* item, ofstream& fout) {
    if (list_item_next(item)) {
        fout << reverse_output(list_item_next(item), fout) << ' ';
    }
    return list_item_data(item);
}

void output(List* road) {
    ofstream fout;
    fout.open(("..\\..\\..\\Lab1CPP\\output.txt"));
    if (road) {
        fout << reverse_output(list_first(road), fout);
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
    // system("pause");
    return 0;
}
