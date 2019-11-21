//Попов Владимир 8091
#include <iostream>
//#include "queue.h"
#include "AVLtree.h"

int main()
{
	node* s = NULL;
	s = insert(s, 100);
	s = insert(s, 10);
	s = insert(s, 500);
	s = insert(s, 1000);
	std::cout << bfactor(s);
	std::cout <<  get_key(FindKey(s, 10));
	remove(s, 10);
	FindKey(s, 10);
}