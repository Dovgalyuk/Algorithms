#include <iostream>
#include <list.h>
#include <fstream>
#include <string>
#include <algorithm>
#include <stack.h>

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	Stack* stack = stack_create();
	/*List* list = list_create();
	list_insert(list, 1);
	list_insert(list, 2);
	list_insert(list, 3);
	ListItem* head = list_first(list);
	while (head != NULL)
	{
		cout << list_item_data(head) << endl;
		head = list_item_next(head);
	}*/
	ifstream fin("input.txt");
	ofstream fout("output.txt");
	while (fin)
	{
		string str;
		getline(fin,str);
		if (str == "")
		{
			continue;
		}
		//transform(str.begin(), str.end(), str.begin(), tolower);
		for (int i = 0; i < str.length(); i++)
		{
			str[i] = tolower(str[i]);
		}
		if (str[0] != '<' || str[str.length() - 1] != '>')
		{
			fout << "¬ходные данные имели неверный формат";
			return 0;
		}
		if (str[1] != '/')
		{
			int hash_open_tag = hash<string>()(str);
			stack_push(stack, hash_open_tag);
		}
		else
		{
			if (stack_empty(stack))
			{
				fout << "NO";
				return 0;
			}
			int hash_open_tag = stack_get(stack);
			str.erase(1, 1);
			int hash_close_tag = hash<string>()(str);
			if (hash_open_tag == hash_close_tag)
			{
				stack_pop(stack);
			}
			else 
			{
				fout << "NO";
				stack_delete(stack);
				return 0;
			}
		}
		/*int h1 = hash<string>()(str);
		int h2 = hash<string>()(str);
		cout << str << " " << h1 << " " << h2 << endl;*/
	}
	if (stack_empty(stack))
	{
		fout << "YES";
	}
	else
	{
		fout << "NO";
		stack_delete(stack);
	}
}

