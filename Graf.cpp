#include "stdafx.h"
#include <stdlib.h>
#include <iostream>
#include "Graf.h"

using namespace std;

struct Graf
{
	size_t CountOfVertexs;
	Array* graf;
	Array* Ves;
};

struct Iter
{
	unsigned ves;
	Data MainVertex;
	Data SecondVertex;
};

Iter* iter_create(Graf* graf, Data Vertex)
{
	Iter* NewIter;
	try
	{
		NewIter = new Iter;
	}
	catch (bad_alloc xa)
	{
		cout << "Iterator is not created" << endl;
		return NULL;
	}
	
	find_vertex(NewIter, graf, Vertex);
	return NewIter;
}

void find_vertex(Iter* iter, Graf* graf, Data Vertex)
{
	iter->MainVertex = Vertex;
	iter->SecondVertex = 0;
	next_iterator(iter, graf);
}

void next_iterator(Iter* iter, Graf* graf)
{
	size_t IndexOfArray;
	do
	{
		if (iter->SecondVertex == graf->CountOfVertexs - 1)
		{
			iter->SecondVertex = -1;
			break;
		}
		
		iter->SecondVertex++;
		IndexOfArray = graf->CountOfVertexs * iter->MainVertex + iter->SecondVertex;
		iter->ves = array_get(graf->Ves, IndexOfArray);

	} while (array_get(graf->graf , IndexOfArray) != 1);
}

Data get_vertex(const Iter* iter)
{
	return iter->SecondVertex;
}

void delete_iterator(Iter* iter)
{
	delete iter;
}

Graf* graf_create(size_t CountOfVertex)
{
	Graf* NewGraf;
	try
	{
		NewGraf = new Graf;
	}
	catch (bad_alloc xa)
	{
		cout << "Невозможно создать граф" << endl;
		return NULL;
	}
	NewGraf->graf = array_create(CountOfVertex * CountOfVertex);
	NewGraf->Ves = array_create(CountOfVertex * CountOfVertex);
	NewGraf->CountOfVertexs = CountOfVertex;
	return NewGraf;
}

void add_vertex(Graf* graf)
{
	Array* NewMatrix = array_create((graf->CountOfVertexs + 1) * (graf->CountOfVertexs + 1));
	Array* NewMatrixOfVes = array_create((graf->CountOfVertexs + 1) * (graf->CountOfVertexs + 1));
	size_t line = 0;
	for (size_t i = 0, j = 0; i < (graf->CountOfVertexs + 1) * graf->CountOfVertexs + graf->CountOfVertexs; i++)
	{
		if (line == (graf->CountOfVertexs + 1))
		{
			array_set(NewMatrix, i, 0);
			array_set(NewMatrixOfVes, i, 0);
			continue;
		}
		else if (i == (graf->CountOfVertexs + 1) * line + graf->CountOfVertexs)
		{
			array_set(NewMatrix, i, 0);
			array_set(NewMatrixOfVes, i, 0);
			++line;
			continue;
		}
		array_set(NewMatrix, i, array_get(graf->graf, j));
		array_set(NewMatrixOfVes, i, array_get(graf->Ves, j));
		++j;
	}
	array_delete(graf->graf);
	array_delete(graf->Ves);
	graf->graf = NewMatrix;
	graf->Ves = NewMatrixOfVes;
	graf->CountOfVertexs++;
}

void add_rib(Graf* graf, Data StartVertex, Data EndVertex)
{
	size_t IndexOfArray = graf->CountOfVertexs * StartVertex + EndVertex;
	array_set(graf->graf, IndexOfArray, 1);
}

void delete_vertex(Graf* graf, Data vertex)
{
	Array* NewMatrix = array_create((graf->CountOfVertexs - 1) * (graf->CountOfVertexs - 1));
	Array* NewMatrixOfVes = array_create((graf->CountOfVertexs - 1) * (graf->CountOfVertexs - 1));
	size_t line = 0;
	for (size_t i = 0, j = 0; j < (graf->CountOfVertexs - 1) * (graf->CountOfVertexs - 1) - 1; i++)
	{
		if (line == vertex)
		{
			if (i == graf->CountOfVertexs * (line + 1))
			{
				++line;
				--i;
				continue;
			}
			continue;
		}
		else if (i == graf->CountOfVertexs * line + vertex)
		{
			++line;
			continue;
		}
		array_set(NewMatrix, j, array_get(graf->graf, i));
		array_set(NewMatrixOfVes, j, array_get(graf->Ves, i));
		++j;
	}
	array_delete(graf->graf);
	array_delete(graf->Ves);
	graf->graf = NewMatrix;
	graf->Ves = NewMatrixOfVes;
	graf->CountOfVertexs++;
}

void delete_rib(Graf* graf, Data StartVertex, Data EndVertex)
{
	size_t IndexOfArray = graf->CountOfVertexs * StartVertex + EndVertex;
	array_set(graf->graf, IndexOfArray, 0);
	array_set(graf->Ves, IndexOfArray, 0);
}

bool rib_is(const Graf* graf, Data StartVertex, Data EndVertex)
{
	size_t IndexOfArray = graf->CountOfVertexs * StartVertex + EndVertex;
	if (array_get(graf->graf, IndexOfArray))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void ves_set(Graf* graf, Data StartVertex, Data EndVertex, int Ves)
{
	size_t IndexOfArray = graf->CountOfVertexs * StartVertex + EndVertex;
	array_set(graf->Ves, IndexOfArray, Ves);
}

int ves_get(const Graf* graf, Data StartVertex, Data EndVertex)
{
	size_t IndexOfArray = graf->CountOfVertexs * StartVertex + EndVertex;
	return array_get(graf->Ves, IndexOfArray);
}

int get_ves(const Iter* it)
{
	return it->ves;
}

void delete_graf(Graf* graf)
{
	array_delete(graf->graf);
	array_delete(graf->Ves);
	delete graf;
}
bool is_neighbors(Iter* it)
{
	if (get_vertex(it) == -1)
	{
		return true;
	}
	else
	{
		return false;
	}
}
