#include <iostream>
#include "stack.h"
#include "vector.h"
#include <string>

using namespace std;

//0 - 9 - çŕíîńčň ÷čńëî â ńňĺę
//+ -*/ % -ŕđčôěĺňč÷ĺńęčĺ îďĺđŕöčč.Čçâëĺęŕţň äâŕ ÷čńëŕ čç ńňĺęŕ, ŕ ďîňîě çŕíîń˙ň ňóäŕ đĺçóëüňŕň
//dup - äóáëčđóĺň ÷čńëî íŕ âĺđřčíĺ ńňĺęŕ z 122
//drop - óäŕë˙ĺň ÷čńëî ń âĺđřčíű ńňĺęŕ x 120
//swap - ěĺí˙ĺň ěĺńňŕěč äâŕ ÷čńëŕ íŕ âĺđřčíĺ ńňĺęŕ c 99 
//over - áĺđ¸ň ýëĺěĺíň ďîä âĺđřčíîé ńňĺęŕ č äîáŕâë˙ĺň ĺăî â ńňĺę v 118
//rot - ďĺđĺěĺůŕĺň "ďî ęđóăó" âĺđőíčĺ ňđč ýëĺěĺíňŕ ńňĺęŕ b 98 
//. - čçâëĺęŕĺň čç ńňĺęŕ âĺđőíčé ýëĺěĺíň č âűâîäčň íŕ ýęđŕí m 109

void show_menu() {
	cout << "Íŕćěčňĺ 0-9 äë˙ çŕíĺńĺíč˙ ÷čńëŕ â ńňĺę\n";
	cout << "Íŕćěčňĺ +-*/% ÷ňîáű čçâëĺ÷ü 2 âĺđőíčő ÷čńëŕ ńňĺęŕ č ďđîčçâĺńňč ńîîňâ. îďĺđŕöčţ\n";
	cout << "Íŕćěčňĺ z(dup), ÷ňîáű ďđîäóáëčđîâŕňü âĺđřčíó ńňĺęŕ\n";
	cout << "Íŕćěčňĺ x(drop), ÷ňîáű óäŕëčňü âĺđřčíó ńňĺęŕ\n";
	cout << "Íŕćěčňĺ c(swap), ÷ňîáű ďîěĺí˙ňü ěĺńňŕěč 2 ýëĺěĺíňŕ âĺđřčíű ńňĺęŕ\n";
	cout << "Íŕćěčňĺ v(over), ÷ňîáű äîáŕâčňü ýëĺěĺíň â ńňĺę, ęîňîđűé íŕőîäčňń˙ ďîä âĺđřčíîé\n";
	cout << "Íŕćěčňĺ b(rot), ÷ňîáű ďĺđĺěĺńňčňü ýëĺěĺíňű 'ďî ęđóăó' âĺđőíčĺ ňđč ýëĺěĺíňŕ ńňĺęŕ\n";
	cout << "Íŕćěčňĺ m(.), ÷ňîáű čçâëĺ÷ü č ďîęŕçŕňü âĺđřčíó ńňĺęŕ\n";
	cout << "Íŕćěčňĺ s, ÷ňîáű ďîęŕçŕňü ěĺíţ č î÷čńňčňü ęîíńîëü\n";
	cout << "Íŕćěčňĺ ESC, ÷ňîáű çŕęîí÷čňü âűďîëíĺíčĺ ďđîăđŕěěű\n\n";
}

//Ńëîćčňü 2 ÷čńëŕ â ńňĺęĺ
void stack_plus(Stack *stack) {
	int first_value = stack_get(stack);
	stack_pop(stack);

	int second_value = stack_get(stack);
	stack_pop(stack);

	stack_push(stack, first_value + second_value);
	cout << "Óńďĺříî!\n";
}

//Âű÷ĺńňü 2 ÷čńëŕ â ńňĺęĺ
void stack_minus(Stack *stack) {
	int first_value = stack_get(stack);
	stack_pop(stack);

	int second_value = stack_get(stack);
	stack_pop(stack);

	stack_push(stack, first_value - second_value);
	cout << "Óńďĺříî!\n";
	
}

//Đŕçäĺëčňü 2 ÷čńëŕ â ńňĺęĺ
void divide(Stack* stack) {
	int first_value = stack_get(stack);
	stack_pop(stack);

	int second_value = stack_get(stack);
	stack_pop(stack);
	if (second_value == 0) {
		throw "Divide by zero!";
	}
	else {
		stack_push(stack, first_value / second_value);
		cout << "Óńďĺříî!\n";
	}
}

//óěíîćčňü 2 ÷čńëŕ â ńňĺęĺ
void multiply(Stack* stack) {
	int first_value = stack_get(stack);
	stack_pop(stack);

	int second_value = stack_get(stack);
	stack_pop(stack);

	stack_push(stack, first_value * second_value);
	cout << "Óńďĺříî!\n";
}

//Îńňŕňîę îň äĺëĺíč˙
void percent(Stack* stack) {
	int first_value = stack_get(stack);
	stack_pop(stack);

	int second_value = stack_get(stack);
	stack_pop(stack);
	if (second_value == 0) {
		throw "Divide by zero!";
	}
	else {
		stack_push(stack, first_value % second_value);
		cout << "Óńďĺříî!\n";
	}
}

//Äóáëčđîâŕňü âĺđřčíó ńňĺęŕ
void duplicate(Stack* stack) {
	int value = stack_get(stack);
	stack_push(stack, value);
	cout << "Óńďĺříî!\n";
}

//Óäŕëčňü âĺđřčíó ńňĺęŕ
void drop(Stack* stack) {
	stack_pop(stack);
	cout << "Óńďĺříî!\n";
}

//Ěĺí˙ĺň ěĺńňŕěč äâŕ ÷čńëŕ íŕ âĺđřčíĺ ńňĺęŕ
void swap(Stack* stack) {
	int first_value = stack_get(stack);
	stack_pop(stack);

	int second_value = stack_get(stack);
	stack_pop(stack);

	stack_push(stack, first_value);
	stack_push(stack, second_value);
	cout << "Óńďĺříî!\n";
}

//Äîáŕâčňü ýëĺěĺíň â ńňĺę, ęîňîđűé íŕőîäčňń˙ ďîä âĺđřčíîé
void over(Stack* stack) {
	int first_value = stack_get(stack);
	stack_pop(stack);

	int second_value = stack_get(stack);

	stack_push(stack, first_value);
	stack_push(stack, second_value);
	cout << "Óńďĺříî!\n";
}



//ďĺđâűé ńňŕíîâčňń˙ âňîđűě (ďîńëĺäíčé(âĺđřčíŕ) ýëĺěĺíň ńňĺęŕ ńňŕíîâčňń˙ âňîđűě)
//âňîđîé ńňŕíîâčňń˙ ňđĺňüčě (âňîđîé ńňŕíîâčňń˙ ďĺđâűě ýëĺěĺíňîě â ńňĺęĺ)
//ňđĺňčé ńňŕíîâčňń˙ ďĺđâűě (ďĺđâűé ýëĺěĺíň ńňĺęŕ ńňŕíîâčňń˙ ďîńëĺäíčě (âĺđřčíŕ))
void rot(Stack *stack) {
	int first_value = stack_get(stack); //Ďĺđâűé ýëĺěĺíň (Ďîńëĺäíčé(âĺđřčíŕ) â ńňĺęĺ) 3
	stack_pop(stack);

	int second_value = stack_get(stack); //Âňîđîé ýëĺěĺíň  2
	stack_pop(stack);

	int third_value = stack_get(stack); //Ňđĺňčé ýëĺěĺíň (ďĺđâűé â ńňĺęĺ) 1
	stack_pop(stack);

	stack_push(stack, second_value); //âňîđîé ńňŕë ďĺđâűě ýëĺěĺíňîě ńňĺęŕ 1
	stack_push(stack, first_value); //âĺđřčíŕ ńňĺęŕ ńňŕëŕ âňîđűě ýëĺěĺíňîě 3
	stack_push(stack, third_value); //ďĺđâűé ýëĺěĺíň ńňĺęŕ ńňŕë âĺđřčíîé(ďîńëĺäíčě) 2
	cout << "Óńďĺříî!\n";
}

//Ďîęŕçŕňü č čçâëĺ÷ü čç ńňĺęŕ
void show_and_pop(Stack* stack) {
	cout << stack_get(stack) << "\n";
	stack_pop(stack);
}

void program_execution(Stack* stack, bool& is_run) {

	string choise;
	cout << "choise: ";
	cin >> choise;

	for (char _choise : choise) {
		if (_choise >= '0' && _choise <= '9') {
			stack_push(stack, _choise - 48);
			continue;
		}
		switch (_choise) {
			//Ńëîćčňü âĺđőíčĺ 2 ýëĺěĺíňŕ ńňĺęŕ +
		case '+':
			stack_plus(stack);
			break;

			//Âű÷ĺńňü âĺđőíčĺ 2 ýëĺěĺíňŕ ńňĺęŕ -
		case '-':
			stack_minus(stack);
			break;

			//Óěíîćčňü âĺđőíčĺ 2 ýëĺěĺíňŕ ńňĺęŕ *
		case '*':
			multiply(stack);
			break;

			//Đŕçäĺëčňü âĺđőíčĺ 2 ýëĺěĺíňŕ ńňĺęŕ /
		case '/':
			divide(stack);
			break;
		case '%':
			percent(stack);
			break;
			//Äóáëčđóĺň âĺđőíčé ýëĺěĺíň ńňĺęŕ z 
		case 'z':
			duplicate(stack);
			break;

			//Óäŕë˙ĺň âĺđőíčé ýëĺěĺíň ńňĺęŕ x
		case 'x':
			drop(stack);
			break;

			//ěĺí˙ĺň ěĺńňŕěč äâŕ ÷čńëŕ íŕ âĺđřčíĺ ńňĺęŕ c
		case 'c':
			swap(stack);
			break;

			//áĺđ¸ň ýëĺěĺíň ďîä âĺđřčíîé ńňĺęŕ č äîáŕâë˙ĺň ĺăî â ńňĺę v
		case 'v':
			over(stack);
			break;

			//ďĺđĺěĺůŕĺň "ďî ęđóăó" âĺđőíčĺ ňđč ýëĺěĺíňŕ ńňĺęŕ b 
		case 'b':
			rot(stack);
			break;

			//čçâëĺęŕĺň čç ńňĺęŕ âĺđőíčé ýëĺěĺíň č âűâîäčň íŕ ýęđŕí m 
		case 'm':
			show_and_pop(stack);
			break;

			//Ďîęŕçŕňü ěĺíţ
		case 's':
			cout << "\n";
			//system("cls");
			show_menu();
			break;
			//Çŕâĺđřčňü âűďîëíĺíčĺ ďđîăđŕěěű
		case 27:
			is_run = false;
			break;
		default:
			break;
		}
	}
}


int main()
{
	setlocale(LC_ALL, "rus");

	Stack *stack = stack_create();
	bool is_run = true;

	show_menu();
	
	do
	{
		try
		{
			program_execution(stack, is_run);
		}
		catch (const char* a)
		{
			cout << a << "\n";
		}
	} while (is_run);
}
