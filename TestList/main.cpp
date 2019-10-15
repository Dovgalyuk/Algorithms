#include <iostream>
#include "list_s.hpp"

int main()
{
	List<int>* my_list = new List<int>;
	my_list->insert(1);
	my_list->insert(2);
	my_list->insert(3);
	if (my_list->item_data(my_list->first()) != 3)
		std::cout << "my_list_insert error\n";
	my_list->insert_after(my_list->first(), 4);
	if (my_list->item_data(my_list->item_next(my_list->first())) != 4)
		std::cout << "my_list_insert_after error\n";
	//my_list односвязный, erase не доступен
	std::cout << "my_list: ";
	for (ListItem<int>* item = (my_list->first()); item; item = my_list->item_next(item))
		std::cout << my_list->item_data(item) << " ";
	std::cout << "\n";
	delete my_list;
}