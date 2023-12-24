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

void upd_parent(List* parents, Data n, Data upd_iter, Data upd_value) 
{
    ListItem* temp = list_first(parents);
    if(upd_iter == 1 && list_item_data(temp) == 0) {
        list_insert_after(parents, temp, upd_value);
        list_erase_first(parents);
    }
    else {
        for (Data i = 2; i <= n; i++) {
            Data num = list_item_data(temp);
            if (i == upd_iter && num == 0) {
                list_insert_after(parents, temp, upd_value);  
                list_erase_next(parents, list_item_next(temp));       
            }
            temp = list_item_next(temp);
        }
    }
}

bool check_value(Data n, Data child_element, List* list, List* parents) 
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
        Data data = 0;
        ListItem* temp = list_first(parents);
        for (Data i = 1; i <= n; i++) 
        {
            Data num = list_item_data(temp);
            if (num != 0 && data == num) {
                flag = false;
                break;
            }
            
            if (i == child_element) {
                data = num;
            } 
            temp = list_item_next(temp);
        }
    }
    return flag;
}

List* find_shortest_road(Data n, Data start, Data finish, List* adj_list) 
{
    Queue* queue = queue_create();
    List* parents = list_create();
    List* visited_nodes = list_create();
    List* road = list_create();
    //инициализация списка родителей
    for (Data i = 1; i <= n; i++)
    {
        list_insert(parents, 0);
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

                if ( parent_element == start || check_value(n, child_element, visited_nodes, parents) ) {
                    dead_end_node = false;
                    queue_insert(queue, child_element);
                    upd_parent(parents, n, child_element, parent_element);
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
    list_delete(parents);
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
    List* road = nullptr;
    Data n = 0;
    Data start = 0, finish = 0;
    
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
