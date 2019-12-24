#include <iostream>
#include "AVLtree.h"
#include <fstream>


int main()
{
	int num;
	srand(555);
	std::ofstream out;
	std::ifstream in;
	out.open("of.txt");
	for (int i = 0; i < 1000; i++)
	{
		out << rand() % 100 << ' ';
	}
	out.close();
	in.open("of.txt");
	in >> num;
	avl_node* s = NULL;
	while (!in.eof())
	{
		s = avl_insert(s, num);
		in >> num;
		std::cout << avl_check(s);
	}
	in.close();
	std::cout << '\n';
	std::cout << avl_check(s);
	std::cout << '\n';
	in.open("of.txt");
	in >> num;
	while (!in.eof())
	{
		if (avl_FindKey(s, num))
		{
			std::cout << std::endl << "checkHeight" << avl_checkheight(s) << std::endl;
			s = avl_remove(s, num);
			in >> num;
			std::cout << avl_check(s);
		}
		else {
			in >> num;
			std::cout << "Error";
		}
	}
	in.close();
}