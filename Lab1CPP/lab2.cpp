#include <iostream>
#include<fstream>
#include "../LibraryCPPClass/myvector.h"
#include "../LibraryCPPClass/stack.h"

using namespace std;

struct Particle
{
	int x;
	char zarad;
};

int main(int argc, char** argv) {
	// тут проверки
	if (argc < 2) {
		cerr << "ispolzuem chasticy iz niput.txt";
		return 1;
	}
	//проверка на открытие файла
	ifstream input(argv[1]);
	if (!input.is_open()) {
		cerr << "ne otkryt input.txt";
		return 1;
	}
	while (true)
	{


		int n;
		if (!(input >> n))
			break;

		Vector cords;
		Vector charg;

		for (int i = 0; i < n; i++) {
			int x;
			char c;
			input >> x >> c;

			cords.resize(cords.size() + 1);
			charg.resize(charg.size() + 1);

			cords.set(cords.size() - 1, x);
			charg.set(charg.size() - 1, c == '+' ? 1 : -1);
		}

		Stack stack;

		Vector left, right;

		for (size_t i = 0; i < cords.size(); i++)
		{
			int x = cords.get(i);
			int charges = charg.get(i);

			if (charges == 1) {
				stack.push(x);//условие для положительной частицы.она движется в право.
			}
			else
			{
				if (!stack.empty())
				{
					int x_pos = stack.get();
					stack.pop();//условие для отрицательной частицы.она движется в лево.

					left.resize(left.size() + 1);
					right.resize(right.size() + 1);
					//сохранение частиц
					left.set(left.size() - 1, x_pos);
					right.set(right.size() - 1, x);
				}
			}
		}
		cout << "Collisions: ";
		if (left.size() == 0)
			cout << "None";
		else {
			for (size_t i = 0; i < left.size(); ++i)
				cout << left.get(i) << " " << right.get(i) << " ";
		}
		cout << endl;
	}

}