#include "stack.h"
#include <iostream>
#include <fstream>

bool open(const std::string& value)
{
	if (value[0] == '<' && value[1] != '/' && value[value.size() - 1] == '>') return true;
	return false;
}
bool close(const std::string& value)
{
	if (value[0] == '<' && value[1] == '/' && value[value.size() - 1] == '>') return true;
	return false;
}
bool verify(const std::string& open_tag, const std::string& close_tag) 
{
	if (open_tag.size() + 1 != close_tag.size()) return false;
	for (size_t i = 1; i < open_tag.size() - 1; i++) { if (open_tag[i] != close_tag[i + 1]) return false; }
	return true;
}
void down(std::string& str)
{ for (int i = 0; i < str.size(); i++) str[i] = tolower(str[i]); }

int main()
{
	setlocale(LC_ALL, "rus");

	std::string input_way = "input.txt";
	std::string output_way = "output.txt";

	std::fstream input(input_way, std::fstream::app | std::fstream::in);
	std::fstream output(output_way, std::fstream::out | std::fstream::app);

	Stack* stack = stack_create();
	bool check = true;
	int count_tags = 0;

	if (!input.is_open()) std::cout << "Error opening the file\n";
	else
	{
		while (!input.eof() && check)
		{
			std::string value;
			input >> value;
			if (value != "") count_tags++;
			if (open(value))
			{
				value.erase(0, 1);
				value.erase(value.size() - 1, value.size());
				down(value);
				int hash_tag = std::hash<std::string>()(value);
				stack_push(stack, hash_tag);
			}
			else if (close(value))
			{
				value.erase(0, 2);
				value.erase(value.size() - 1, value.size());
				down(value);
				int open_hash_tag = stack_get(stack);
				stack_pop(stack);
				int close_hash_tag = std::hash<std::string>()(value);
				if (open_hash_tag != close_hash_tag) check = false;
			}
			else
			{ if (value != "") check = false; }
		}
		if (count_tags % 2 != 0 || count_tags == 0) check = false;
	}

	if (check) output << "YES\n";
	else output << "NO\n";

	stack_delete(stack);

	return 0;
}