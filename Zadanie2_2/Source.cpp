#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <conio.h>
#include <queue>
#include <windows.h>
//#include <list>
#include "../Library/queue.h"


// # = 35 | . = 46
// X = 88 |	Y = 89
// x = 120 |  y = 121 | h = 104 | b = 98

using namespace std;

struct element {
	int posX;
	int posY;
	char state;
};

bool function(vector<string> & mainMap);
element find_start(vector<string> buffer);
void return_to_start(element & out, vector<string> & buffer, vector<string> & main);

int main() {
	ifstream input("input.txt");
	ofstream output("output.txt");

	vector<string> mainArchive;
	string StrBuffer;

	while (!input.eof()) {
		input >> StrBuffer;
		mainArchive.push_back(StrBuffer);
	}

	bool res = function(mainArchive);

	if (res) {
		for (int i = 0; i < mainArchive.size(); i++) {
			for (int j = 0; j < mainArchive[0].size(); j++) {
				cout << mainArchive[i][j];
			}
			cout << endl;
		}
		cout << "yes";
	}
	else
		cout << "no";
	_getch();
	return 0;
}



bool function(vector<string> & mainMap) {

	vector <string> bufferMap = mainMap; // recovery map
	queue<element> myQueMain;
	element posStart = find_start(mainMap); // сделать защиту от старта и финиша
	myQueMain.push(posStart);
	size_t sizeQueMain = myQueMain.size();

	do {

		for (int i = 0; i < sizeQueMain; i++)
		{
			
			
			//отдельна€ €чейка лабиринта
			element * buf = new element;
			//следующа€ €чейка лабиринта
			element * bufNext = new element;
			*buf = myQueMain.front();
			myQueMain.pop();

			// ищем отростки от bufa  

			// на самом деле это POS Y + 1 POS X

			if (bufferMap[buf->posX + 1][buf->posY] == '.' || bufferMap[buf->posX + 1][buf->posY] == 'Y')
			{
				if (bufferMap[buf->posX + 1][buf->posY] != 'Y')
					//убрать динамическую пам€ть и сделать ассив направлений
					bufferMap[buf->posX + 1][buf->posY] = '2';
				bufNext->posX = buf->posX + 1;
				bufNext->posY = buf->posY;
				bufNext->state = bufferMap[buf->posX + 1][buf->posY];
				myQueMain.push(*bufNext);
				if (myQueMain.front().state == 'Y') {
					bufNext->state = '2';
					return_to_start(*bufNext, bufferMap, mainMap);
					return 1;
				}
				
			}

	

			// на самом деле это POS Y - 1 POS X
			if (bufferMap[buf->posX - 1][buf->posY] == '.' || bufferMap[buf->posX - 1][buf->posY] == 'Y')
			{

				if (bufferMap[buf->posX - 1][buf->posY] != 'Y')
					bufferMap[buf->posX - 1][buf->posY] = '4';
				bufNext->posX = buf->posX - 1;
				bufNext->posY = buf->posY;
				bufNext->state = bufferMap[buf->posX - 1][buf->posY];
				myQueMain.push(*bufNext);
				if (myQueMain.front().state == 'Y') {
					bufNext->state = '4';
					return_to_start(*bufNext, bufferMap, mainMap);
					return 1;
				}
			}
			// на самом деле это POS Y POS X + 1
			if (bufferMap[buf->posX][buf->posY + 1] == '.' || bufferMap[buf->posX][buf->posY + 1] == 'Y')
			{
				if (bufferMap[buf->posX][buf->posY + 1] != 'Y')
					bufferMap[buf->posX][buf->posY + 1] = '1';
				bufNext->posX = buf->posX;
				bufNext->posY = buf->posY + 1;
				bufNext->state = bufferMap[buf->posX][buf->posY + 1];
				myQueMain.push(*bufNext);
				if (myQueMain.front().state == 'Y') {
					bufNext->state = '1';
					return_to_start(*bufNext, bufferMap, mainMap);
					return 1;
				}
			}
				// на самом деле это POS Y POS X -1	}
			if (bufferMap[buf->posX][buf->posY - 1] == '.' || bufferMap[buf->posX][buf->posY - 1] == 'Y')
				{
					if (bufferMap[buf->posX][buf->posY - 1] != 'Y')
						bufferMap[buf->posX][buf->posY - 1] = '3';
					bufNext->posX = buf->posX;
					bufNext->posY = buf->posY - 1;
					bufNext->state = bufferMap[buf->posX][buf->posY - 1];
					myQueMain.push(*bufNext);
					if (myQueMain.front().state == 'Y') {
						bufNext->state = '3';
						return_to_start(*bufNext, bufferMap, mainMap);
						return 1;
					}
				}
			
		}
			sizeQueMain = myQueMain.size();

			if (myQueMain.size() == 0) {
				return 0; // Ё “–≈ЌЌџ… ¬џ’ќƒ, Ќ” ѕќ„“» Ё —“–≈ЌЌџ…
			}



			
			// вывод на каждый шаг
			for (int i = 0; i < bufferMap.size(); i++) {
				for (int j = 0; j < bufferMap[0].size(); j++) {
					cout << bufferMap[i][j];
				}
				cout << endl;
			}

			_getch();
			system("cls");
			



			//sizeQueMain = myQueMain.size();
		} while (true);

	}
	//   2 
	//  1 3
	//   4





void return_to_start(element & out,vector<string> & buffer, vector<string> & main) 
{
	element CurElem;
	CurElem = out;
	while (CurElem.state != 'X')
	{
		if (CurElem.state == '1') {
			main[CurElem.posX][CurElem.posY] = 'x';
			CurElem.posX = CurElem.posX;
			CurElem.posY = CurElem.posY - 1;
			CurElem.state = buffer[CurElem.posX][CurElem.posY];
		}
		else if (CurElem.state == '2') 
		{
			main[CurElem.posX][CurElem.posY] = 'x';
			CurElem.posX = CurElem.posX - 1;
			CurElem.posY = CurElem.posY;
			CurElem.state = buffer[CurElem.posX][CurElem.posY];
		}
		else if (CurElem.state == '3')
		{
			main[CurElem.posX][CurElem.posY] = 'x';
			CurElem.posX = CurElem.posX;
			CurElem.posY = CurElem.posY + 1;
			CurElem.state = buffer[CurElem.posX][CurElem.posY];
		}
		else if (CurElem.state == '4') 
		{
			main[CurElem.posX][CurElem.posY] = 'x';
			CurElem.posX = CurElem.posX + 1;
			CurElem.posY = CurElem.posY;
			CurElem.state = buffer[CurElem.posX][CurElem.posY];
		}
		else
		{
			return;
		}
	}



}


element find_start(vector<string> buffer) {
	element buf;
	buf.posX = 0;
	buf.posY = 0;
	for (int i = 0; i < buffer.size(); i++) {
		for (int j = 0; j < buffer[0].size(); j++) {
			if (buffer[i][j] == 'X') {
				buf.posX = i;
				buf.posY = j;
				buf.state = 'X';
			}
		}
	}
		return buf;
}



/*
вывод

for (int i = 0; i < mainArchive.size(); i++) {
for (int j = 0; j < mainArchive[0].size(); j++) {
cout << mainArchive[i][j];
}
cout << endl;
}

*/