#include <iostream>
#include <string>
#include "../Library/stack.h"
#include "../Library/vector.h"
using namespace std;

int chart(char a, char b);

int main()
{
	Stack* stack = stack_create();
	Vector* interim = vector_create();
	string in, s;
	cin >> in;
	in = in + "|";
	stack_push(stack, "|");
	int i = 0, j = 0, it = 0, num = 0, operand_1 = 0, operand_2 = 0;
	while (i < in.length())
	{
		if (in[i] >= '0' && in[i] <= '9')
		{
			num++;
			i++;
		}
		else {
			s.assign(in, it, num);
			if (s != "") {
				vector_set(interim, j, s);
				j++;
			}
			switch (chart(stack_get(stack)[0], in[i]))
			{
			case 1:
				stack_push(stack, (string)"" + in[i]);
				i++;
				it = i;
				break;
			case 2:
				vector_set(interim, j, stack_get(stack));
				j++;
				stack_pop(stack);
				it = i + 1;
				break;
			case 3:
				j = 0;

				while (j < vector_size(interim)) {
					switch (vector_get(interim, j)[0])
					{
					case '+':
						operand_2 = stoi(stack_get(stack));
						stack_pop(stack);
						operand_1 = stoi(stack_get(stack));
						stack_pop(stack);
						operand_1 += operand_2;
						stack_push(stack, to_string(operand_1));
						j++;
						break;
					case '-':
						operand_2 = stoi(stack_get(stack));
						stack_pop(stack);
						operand_1 = stoi(stack_get(stack));
						stack_pop(stack);
						operand_1 -= operand_2;
						stack_push(stack, to_string(operand_1));
						j++;
						break;
					case '*':
						operand_2 = stoi(stack_get(stack));
						stack_pop(stack);
						operand_1 = stoi(stack_get(stack));
						stack_pop(stack);
						operand_1 *= operand_2;
						stack_push(stack, to_string(operand_1));
						j++;
						break;
					case '/':
						operand_2 = stoi(stack_get(stack));
						stack_pop(stack);
						operand_1 = stoi(stack_get(stack));
						stack_pop(stack);
						operand_1 /= operand_2;
						stack_push(stack, to_string(operand_1));
						j++;
						break;
					default:
						stack_push(stack, vector_get(interim, j));
						j++;
						break;
					}

				}
				cout << stack_get(stack);
				vector_delete(interim);
				stack_delete(stack);
				return 0;
			case 4:
			default:
				std::cout << "Translation error. Stoping\n";
				return 1;
			}
			num = 0;
		}
	}
}

int chart(char a, char b)
{
	switch (a)
	{
	case '|':
		switch (b)
		{
		case '|':
			return 3;
		case '+':
		case '-':
		case '*':
		case '/':
			return 1;
		default:
			return 4;
		}
	case '+':
	case '-':
		switch (b)
		{
		case '|':
		case '+':
		case '-':
			return 2;
		case '*':
		case '/':
			return 1;
		default:
			return 4;
		}
	case '*':
	case '/':
		switch (b)
		{
		case '|':
		case '+':
		case '-':
		case '*':
		case '/':
			return 2;
		default:
			return 4;
		}
	default:
		return 4;
	}
}