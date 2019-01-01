#include <stdlib.h>
#include "Graf.h"
#include "list.h"
#include<iostream>

using namespace std;

struct Graf
{
	Data size;
	Data real_size;
	List **vertex;
	int *vPoint;
	Graf(Data _size)
	{
		size = _size;
		real_size = _size;
		vertex = new List*[size];
		vPoint = new int[size];
	}
};

struct Iterator {
	ListItem *current;
};

//------ITERATOR------//

Iterator *iterator_begin(Graf *Graf, Data index) {
	Iterator *tmp = new Iterator;
	tmp->current = list_first(Graf->vertex[index]);
	return tmp;
}

Iterator *iterator_end(Graf *Graf, Data index) {
	Iterator *tmp = new Iterator;
	tmp->current = nullptr;
	return tmp;
}

void iterator_next(Iterator *iterator) {
	iterator->current = list_item_next(iterator->current);
}

ListItem &iterator_current(Iterator *iterator) {
	return *iterator->current;
}

int &iterator_value(Iterator *iterator) {
	return *list_item_data(iterator->current);
}

bool iterator_equal(Iterator *it1, Iterator *it2) {
	if (it1->current != it2->current) return false;
	return true;
}

//--------GRAF-------//

Graf *graf_create(Data size)
{
	Graf *graf = new Graf(size);
	for (int i = 0; i < size; i++) {
		graf_set_vertex(graf, i);
	}
	return graf;
}

void graf_delete(Graf *Graf)
{
	delete[] Graf->vertex;
	delete[] Graf->vPoint;
	delete Graf;
}

void graf_set_vertex(Graf *Graf, Data value)
{
	if (value > Graf->size - 1) graf_resize(Graf, value + 1);
	Graf->vertex[value] = list_create();
	Graf->vPoint[value] = 0;
}

void graf_delete_vertex(Graf *Graf, Data value)
{
	if (graf_vertex_exist(Graf, value)) {
		list_delete(Graf->vertex[value]);
		Graf->vertex[value] = nullptr;
		if (value == Graf->size - 1) graf_resize(Graf, Graf->size - 1);
	} 
}

void graf_set_advertex(Graf *Graf, Data index_1, Data index_2)
{
	if (graf_vertex_exist(Graf, index_1) && (graf_vertex_exist(Graf, index_2)))
	list_insert(Graf->vertex[index_1], index_2);
}

void graf_delete_advertex(Graf *Graf, Data index_1, Data index_2)
{
	if (graf_vertex_exist(Graf, index_1) && (graf_vertex_exist(Graf, index_2)))
	list_erase_item(Graf->vertex[index_1], index_2);
}

bool graf_vertex_exist(Graf *Graf, Data index) {
	if (Graf->size - 1 < index || !Graf->vertex[index]) return false;
	else return true;
}

bool graf_edge_exist(Graf *Graf, Data index_1, Data index_2) {
	if (graf_vertex_exist(Graf, index_1) && (graf_vertex_exist(Graf, index_2)))
	return list_item_exist(Graf->vertex[index_1], index_2);
	else return false;
}

void graf_add_mark_edge(Graf *Graf, Data index_1, Data index_2, Data mark) {
	if (graf_vertex_exist(Graf, index_1) && graf_edge_exist(Graf, index_1, index_2) && Graf->vertex[index_1])
	*list_item_weight(Graf->vertex[index_1], index_2) = mark;
}

int graf_get_mark_edge(Graf *Graf, Data index_1, Data index_2) {
	if (graf_vertex_exist(Graf, index_1) && graf_edge_exist(Graf, index_1, index_2) && Graf->vertex[index_1])
	return *list_item_weight(Graf->vertex[index_1], index_2);
	else return 0;
}

void graf_add_mark_vertex(Graf *Graf, Data index, Data mark) {
	if (graf_vertex_exist(Graf, index)) Graf->vPoint[index] = mark;
}

int graf_get_mark_vertex(Graf *Graf, Data index) {
	if (graf_vertex_exist(Graf, index)) return Graf->vPoint[index];
	else return -1;
}

Data graf_size(Graf *Graf)
{
	return Graf->size;
}

void graf_resize(Graf *Graf, Data size)
{
	if (Graf->size > size && size < Graf->real_size)
	{
		Graf->size = size;
	}
	else if (Graf->size < size && Graf->real_size > size)
	{
		while (Graf->size != size)
		{
			Graf->size++;
			Graf->vertex[Graf->size] = list_create();
		}
	}
	else
	{
		if (Graf->real_size * 2 < size)
		{
			Graf->real_size = size;
		}
		else
		{
			Graf->real_size = Graf->real_size * 2;
		}
		List **temp = new List*[Graf->real_size];

		for (int i = 0; i < Graf->size; i++)
		{
			temp[i] = Graf->vertex[i];
		}
		Graf->size = size;
		Graf->vertex = temp;
	}
}
/*int main() {
	int ytmp = -2;
	Graf *g = graf_create(6);
	graf_set_advertex(g, 0, 1);
	graf_set_advertex(g, 1, 2);
	graf_set_advertex(g, 1, 3);
	graf_set_advertex(g, 1, 4);
	graf_set_advertex(g, 3, 5);
	graf_set_advertex(g, 5, 4);
	graf_set_advertex(g, 5, 2);
	graf_add_mark_edge(g, 0, 1, 11);
	graf_add_mark_edge(g, 1, 2, 3);
	graf_add_mark_edge(g, 1, 3, 5);
	graf_add_mark_edge(g, 1, 4, 1);
	graf_add_mark_edge(g, 3, 5, 7);
	graf_add_mark_edge(g, 5, 4, 5);
	graf_add_mark_edge(g, 5, 2, 11);
	Iterator *tmp = iterator_begin(g, 1);
	tmp++;
}*/