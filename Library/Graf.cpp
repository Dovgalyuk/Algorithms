#include "Graf.h"

struct Graf
{
	int size;
	Array* pole;
	Array* visited;
	Array* vertex_point;
};
struct Iterator
{
	int* cur;
	int* visited;
	int* colori;
	int* colorj;
};

Iterator* create_iterator_begin(Graf* graf, int vertex)
{
	Iterator* tmp = new Iterator;
	tmp->cur = get_pointer(graf->pole, vertex*graf->size);
	tmp->visited = get_pointer(graf->visited, vertex*graf->size);
	tmp->colori = get_pointer(graf->vertex_point, vertex);
	tmp->colorj = get_pointer(graf->vertex_point, 0);
	return tmp;
}   
Iterator* create_iterator_end(Graf* graf, int vertex)  
{
	Iterator* tmp = new Iterator;
	tmp->cur = get_pointer(graf->pole, vertex*graf->size + graf->size-1);
	tmp->visited = get_pointer(graf->visited, vertex*graf->size + graf->size - 1);
	tmp->colori = get_pointer(graf->vertex_point, vertex);
	tmp->colorj = get_pointer(graf->vertex_point, graf->size - 1);
	return tmp;
}
bool comp(Iterator* it1, Iterator* it2)
{
	if (it1->cur <= it2->cur)
		return true;
	return false;
}
void assign_it(Iterator* it1, Iterator* it2)
{
	it1->cur = it2->cur;
	it1->visited = it2->visited;
	it1->colori = it2->colori;
	it1->colorj = it2->colorj;
}
void up(Iterator* it)
{
	it->cur++;
	it->visited++;
	it->colorj++;
}
int& DerVis(Iterator* it)
{
	return *it->visited;
}
int& DerCur(Iterator* it)
{
	return *it->cur;
}
int& DerColori(Iterator* it)
{
	return *it->colori;
}
int& DerColorj(Iterator* it)
{
	return *it->colorj;
}
void delete_iterator(Iterator * it)
{
	delete it;
}

/*struct Iterator
{
	int* cur;
	int* colori;
	int* colorj;
	int* vis;
	int** HeadCur;
	int** HeadVis;
};


void up(Iterator* it, int n)
{
	it->cur += n;
	it->vis += n;
	it->colorj += n;
}
void up_col(Iterator* it)
{
	it->HeadCur += 1;
	it->HeadVis += 1;
	it->cur = *it->HeadCur;
	it->vis = *it->HeadVis;
	it->colori++;
}
bool comp(Iterator* it1, Iterator* it2)
{
	if (it1->cur <= it2->cur)
		return true;
	return false;
}
int diff_it(Iterator* it1, Iterator* it2)
{
	return it2->cur - it1->cur;
}

void assign_it(Iterator* it1, Iterator* it2)
{
	it1->cur = it2->cur;
	it1->colori = it2->colori;
	it1->colorj = it2->colorj;
	it1->HeadCur = it2->HeadCur;
	it1->HeadVis = it2->HeadVis;
	it1->vis = it2->vis;
}

Iterator* create_it(Graf *graf)
{
	Iterator* tmp = new Iterator;
	tmp->cur = get_pointer(graf->pole,0,0);
	return tmp;
}

Iterator* col_begin_it(Graf* graf)
{
	return create_it(get_pointer(graf->pole, 0, 0), get_pointer(graf->vertex_point, 0), get_pointer(graf->visited, 0,0), get_pointer(graf->pole), get_pointer(graf->visited));
}
Iterator* col_end_it(Graf* graf)
{
	return create_it(get_pointer(graf->pole, graf->size - 1, 0), get_pointer(graf->vertex_point, graf->size - 1), get_pointer(graf->visited, graf->size - 1, 0),get_pointer(graf->pole), get_pointer(graf->visited));
}
Iterator* row_end_it(Graf* graf, Iterator* it)
{
	Iterator* tmp = create_it(NULL,NULL, NULL, NULL, NULL);
	assign_it(tmp, it);
	up(tmp, graf->size-1);
	return tmp;
}
*/
Graf* graf_create(int size)
{
	Graf *tmp = new Graf;
	tmp->pole = array_create(size * size);
	tmp->vertex_point = array_create(size);
	tmp->visited = array_create(size * size);
	tmp->size = size;
	return tmp;
}
void add_vertex(Graf *graf)
{
	graf->size++;
	set_array_size(graf->pole, graf->size * graf->size);
	set_array_size(graf->visited, graf->size * graf->size);
	set_array_size(graf->vertex_point, graf->size);
}
void add_edge(Graf *graf, int Fvertex, int Tvertex)
{
	*get_pointer(graf->pole, Fvertex * graf->size + Tvertex) = 1;
}
void delete_vertex(Graf *graf, int index)
{
	int size = graf->size - 1;
	//for color
	for (int i = index; i < size; i++)
		*get_pointer(graf->vertex_point, i) = *get_pointer(graf->vertex_point, i + 1);
	*get_pointer(graf->vertex_point, size) = 0;

	//for pole and visit
	size = graf->size;
	int j = 0, ind = index;
	for (int i = 0; i < size*size; )
	{
		if (i == index * size)
		{
			i += size;
			ind += size;
		}
		else if (i == ind)
		{
			i++;
			ind += size;
		}
		else
		{
			*get_pointer(graf->pole, j) = *get_pointer(graf->pole, i);
			*get_pointer(graf->visited, j) = *get_pointer(graf->visited, i);
			j++;
			i++;
		}
	}
	for (int i = j; i < size*size; i++)
	{
		*get_pointer(graf->pole, i) = 0;
		*get_pointer(graf->visited, i) = 0;
	}

	graf->size--;
	set_array_size(graf->pole, graf->size * graf->size);
	set_array_size(graf->visited, graf->size * graf->size);
	set_array_size(graf->vertex_point, graf->size);
}
void delete_egde(Graf *graf, int Fvertex, int Tvertex)
{
	*get_pointer(graf->pole, Fvertex * graf->size + Tvertex) = 0;
	*get_pointer(graf->visited, Fvertex * graf->size + Tvertex) = 0;
}
//1 - default mark, if edge is exists
void add_mark_edge(Graf *graf, int Fvertex, int Tvertex, int mark)
{
	*get_pointer(graf->pole, Fvertex * graf->size + Tvertex) = mark;
}
void add_mark_vertex(Graf *graf, int vertex, int mark)
{
	*get_pointer(graf->vertex_point, vertex) = mark;
}
int get_mark_edge(Graf *graf, int Fvertex, int Tvertex)
{
	return *get_pointer(graf->pole, Fvertex * graf->size + Tvertex);
}
int get_mark_vertex(Graf *graf, int vertex)
{
	return *get_pointer(graf->vertex_point, vertex);
}
bool Is_edge(Graf *graf, int Fvertex, int Tvertex)
{
	if (get_mark_edge(graf, Fvertex, Tvertex) > 0)
		return true;
	else
		return false;
}
void delete_graf(Graf *graf)
{
	array_delete(graf->pole);
	array_delete(graf->vertex_point);
	array_delete(graf->visited);
	delete graf;
}
