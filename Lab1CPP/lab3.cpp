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


void input (Data &n, Data &start, Data &finish, List* list) 
{
    ifstream fin( "..\\..\\..\\Lab1CPP\\input.txt");

    if (fin.is_open()) {
        char buf [16];
        fin >> buf;
        n = stoi(buf);
        fin >> buf;
        start = stoi(buf);
        fin >> buf;
        finish = stoi(buf);
        while (fin >> buf) {
            int num = stoi(buf);
            fin >> buf;
            int num2 = stoi(buf);
            list_insert(list, num);
            list_insert(list, num2);
            list_insert(list, num2);
            list_insert(list, num);
        }
    } else {
        "Error open file!!!!!!\n";
    }
    fin.close();
}

void upd_queue_par(Data n, Data cnt_upd, Data upd_value, Queue* parents) 
{
    for (Data i = 1; i <= n; i++) {
        Data num = queue_get(parents);
        if (i == cnt_upd && num == 0) {
            num = upd_value;
        } 
        queue_insert(parents, num);
        queue_remove(parents);
    }
}

bool check_value(Data n, Data value_get, Data value_next, List* list, Queue* parents) 
{
    bool flag = true;
    for (ListItem* item = list_first(list); item; item = list_item_next(item)) {
        if (value_next == list_item_data(item)) {
            flag = false;
            break;
        }
    }     
    if (flag) {
        Data temp = -1;
        for (Data i = 1; i <= n; i++) {
            Data num = queue_get(parents);
            if (num != 0 && temp == num) {
                flag = false;
                break;
            }
            
            if (i == value_get || i == value_next) {
                temp = num;
            } 
            
            queue_insert(parents, num);
            queue_remove(parents);
        }
    }
    return flag;
}

void find_shortest_road(Data n, Data start, Data finish, List* adj_list, List* road) 
{
    Queue* queue = queue_create();
    Queue* parents = queue_create();
    List* visited_nodes = list_create();
    //инициализация очереди родителей
    for (Data i = 1; i <= n; i++)
    {
        queue_insert(parents, 0);
    }
    queue_insert(queue, start);

    while (!queue_empty(queue))
    {    
        Data value_get = queue_get(queue), value_next = 0;
        if (value_get == finish && road && (start == finish || list_item_data(list_first(road)) != finish)) {
            list_insert(road, finish);
            break;
        } 
        queue_remove(queue);
        list_insert(visited_nodes, value_get);
        list_insert(road, value_get);
        bool check_from_road = false;
        //поиск следующих элементов
        for( ListItem* item = list_first(adj_list); item; item = list_item_next(list_item_next(item)) ) 
        {
            if (value_get == list_item_data(item)) 
            {
                value_next = list_item_data(list_item_next(item));

                if (value_get == start || check_value(n, value_get, value_next, visited_nodes, parents)) {
                    queue_insert(queue, value_next);
                    check_from_road = true;
                    upd_queue_par(n, value_next, value_get, parents);
                }
            }
        }
        //если узел тупиковый, то удаляем элемент из пути
        if (!check_from_road) {
            list_erase_first(road);
        }
    }

    queue_delete(queue);
    //queue_delete(distance);
    queue_delete(parents);
    list_delete(visited_nodes);
}

Data reverse_output(ListItem* road, ofstream& fout) {
    if (list_item_next(road)) {
        fout << reverse_output(list_item_next(road), fout) << ' ';
    }
    return list_item_data(road);
}

void output(List* road, Data start, Data finish) {
    ofstream fout;
    fout.open(("..\\..\\..\\Lab1CPP\\output.txt"));
    if (road && (start == finish || list_item_data(list_first(road)) != start)) 
    {
        fout << reverse_output(list_first(road), fout);
    } else {
        fout << "IMPOSSIBLE";
    }
    fout.close();
}

int main()
{
    
    List* adj_list = list_create();
    List* road = list_create();
    
    Data n = 0;
    Data start = 0, finish = 0;
    
    input(n, start, finish, adj_list);
    find_shortest_road(n, start, finish, adj_list, road);
    output(road, start, finish);

    list_delete(adj_list);

    return 0;
}
