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


bool input (Data &n, Data &start, Data &finish, List* list) 
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
            while (fin >> buf) {
                int num = stoi(buf);
                fin >> buf;
                int num2 = stoi(buf);
                if (num > n || num2 > n) {
                    flag = false;
                    break;
                }
                list_insert(list, num);
                list_insert(list, num2);
                list_insert(list, num2);
                list_insert(list, num);

            }
        }
    }
    fin.close();
    return flag;
}

void upd_queue_par(Data n, Data upd_iter, Data upd_value, Queue* parents) 
{
    //прокрутка очереди для вставки значения
    for (Data i = 1; i <= n; i++) {
        Data num = queue_get(parents);
        if (i == upd_iter && num == 0) {
            num = upd_value;
        } 
        queue_insert(parents, num);
        queue_remove(parents);
    }
}

bool check_value(Data n, Data parent_element, Data child_element, List* list, Queue* parents) 
{
    bool flag = true;
    // проверка вершины на пройденность
    for (ListItem* item = list_first(list); item; item = list_item_next(item)) 
    {
        if (child_element == list_item_data(item)) {
            flag = false;
            break;
        }
    }     
    if (flag) {
        //проверка на одинакового родителя двух вершин
        Data temp = 0;
        for (Data i = 1; i <= n; i++) 
        {
            Data num = queue_get(parents);
            if (num != 0 && temp == num) {
                flag = false;
                break;
            }
            
            if (i == parent_element || i == child_element) {
                temp = num;
            } 
            //прокрутка очереди для вставки значения
            queue_insert(parents, num);
            queue_remove(parents);
        }
    }
    return flag;
}

List* find_shortest_road(Data n, Data start, Data finish, List* adj_list) 
{
    Queue* queue = queue_create();
    Queue* parents = queue_create();
    List* visited_nodes = list_create();
    List* road = list_create();
    //инициализация очереди родителей
    for (Data i = 1; i <= n; i++)
    {
        queue_insert(parents, 0);
    }
    queue_insert(queue, start);
    //обход графа
    while (!queue_empty(queue))
    {    
        Data parent_element = queue_get(queue), child_element = 0;
        if (parent_element == finish ) {
            if (road && (start == finish || list_item_data(list_first(road)) != finish)) {
                list_insert(road, finish);
            }
            break;
        } 
        queue_remove(queue);
        list_insert(visited_nodes, parent_element);
        list_insert(road, parent_element);
        bool dead_end_node = true;

        for( ListItem* item = list_first(adj_list); item; item = list_item_next(list_item_next(item)) ) 
        {
            if (parent_element == list_item_data(item)) 
            {
                child_element = list_item_data(list_item_next(item));

                if (parent_element == start || check_value(n, parent_element, child_element, visited_nodes, parents)) {
                    dead_end_node = false;
                    queue_insert(queue, child_element);
                    upd_queue_par(n, child_element, parent_element, parents);
                }
            }
        }

        if (dead_end_node) {
            list_erase_first(road);
        }
    }
    if (list_first(road) == nullptr) {
        road = nullptr;
    }
    queue_delete(queue);
    queue_delete(parents);
    list_delete(visited_nodes);
    return road;
}

Data reverse_output(ListItem* item, ofstream& fout) {
    if (list_item_next(item)) {
        fout << reverse_output(list_item_next(item), fout) << ' ';
    }
    return list_item_data(item);
}

void output(List* road, Data start, Data finish) {
    ofstream fout;
    fout.open(("..\\..\\..\\Lab1CPP\\output.txt"));
    if (road && (start == finish || list_item_data(list_first(road)) != start)) {
        fout << reverse_output(list_first(road), fout);
    } else {
        fout << "IMPOSSIBLE";
    }
    fout.close();
}

int main()
{
    List* adj_list = list_create();
    Data n = 0;
    Data start = 0, finish = 0;
    List* road = nullptr;
    if (input(n, start, finish, adj_list)){
        road = find_shortest_road(n, start, finish, adj_list);        
    }
    output(road, start, finish);
    list_delete(adj_list);
    if (road) {
        list_delete(road);
    }
    return 0;
}
