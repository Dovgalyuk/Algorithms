#ifndef ASSOCIATIVE_ARRAY_H
#define ASSOCIATIVE_ARRAY_H
#include <iostream>
#include <string>
#include "avltree.h"
using namespace std;


class AssociativeArray
{
public:
	AssociativeArray(string key, string field)
	{
		container = new Tree;
		container->insert(key, field);
	}
	~AssociativeArray()
	{
		delete container;
	}
	void add(string key, string field)
	{
		container->insert(key, field);
	}
	void remove(string key)
	{
		container->remove(key);
	}
	void print()
	{
		container->display();
	}
	string search(string key)
	{
		return container->search_field(key);
	}
private:
	Tree* container;
};



#endif

