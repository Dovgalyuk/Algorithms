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
	element * prev;
};

bool function(vector<string> & mainMap);
element find_start(vector<string> buffer);


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

	if (res)
		/*for (int i = 0; i < mainArchive.size(); i++) {
			for (int j = 0; j < mainArchive[0].size(); j++) {
				cout << mainArchive[i][j];
			}
			cout << endl;
		}*/
		cout << "yes";
	else
		cout << "no";
	_getch();
	return 0;
}



bool function(vector<string> & mainMap) {
	vector <string> bufferMap = mainMap;
	queue<element> myQueMain, myQueBuf;
	element posStart = find_start(mainMap); // сделать защиту от старта и финиша
	myQueMain.push(posStart);
	size_t sizeQueMain = myQueMain.size();
	size_t sizeQueBuf = myQueBuf.size();
	
	do {
		for (int i = 0; i < sizeQueMain; i++) {
			//отдельная ячейка лабиринта
			element * buf = new element;
			//следующая ячейка лабиринта
			element * bufNext = new element;
			*buf = myQueMain.front();
			myQueMain.pop();

			// ищем отростки от bufa  

			// на самом деле это POS Y + 1 POS X
	
			if (bufferMap[buf->posX + 1][buf->posY] == '.' || bufferMap[buf->posX + 1][buf->posY] == 'Y')
			{
				if (bufferMap[buf->posX + 1][buf->posY] != 'Y')
					bufferMap[buf->posX + 1][buf->posY] = 'h';
				bufNext->posX = buf->posX + 1;
				bufNext->posY = buf->posY;
				bufNext->prev = buf;
				bufNext->state = bufferMap[buf->posX + 1][buf->posY];
				myQueMain.push(*bufNext);
				if (myQueMain.front().state == 'Y') {
					//mainMap = bufferMap;
					return 1;
				}
			}

			// на самом деле это POS Y - 1 POS X

			if (bufferMap[buf->posX - 1][buf->posY] == '.' || bufferMap[buf->posX - 1][buf->posY] == 'Y')
			{

				if (bufferMap[buf->posX - 1][buf->posY] != 'Y')
					bufferMap[buf->posX - 1][buf->posY] = 'h';
				bufNext->posX = buf->posX - 1;
				bufNext->posY = buf->posY;
				bufNext->prev = buf;
				bufNext->state = bufferMap[buf->posX - 1][buf->posY];
				myQueMain.push(*bufNext);
				if (myQueMain.front().state == 'Y') {
					//mainMap = bufferMap;
					return 1;
				}
			}
			// на самом деле это POS Y POS X + 1
			if (bufferMap[buf->posX][buf->posY + 1] == '.' || bufferMap[buf->posX][buf->posY + 1] == 'Y')
			{
				if (bufferMap[buf->posX][buf->posY + 1] != 'Y')
					bufferMap[buf->posX][buf->posY + 1] = 'h';
				bufNext->posX = buf->posX;
				bufNext->posY = buf->posY + 1;
				bufNext->prev = buf;
				bufNext->state = bufferMap[buf->posX][buf->posY + 1];
				myQueMain.push(*bufNext);
				if (myQueMain.front().state == 'Y') {
					//mainMap = bufferMap;
					return 1;
				}
			// на самом деле это POS Y POS X -1	}
		
			if (bufferMap[buf->posX][buf->posY - 1] == '.' || bufferMap[buf->posX][buf->posY - 1] == 'Y')
			{
				if (bufferMap[buf->posX][buf->posY - 1] != 'Y')
					bufferMap[buf->posX][buf->posY - 1] = 'h';
				bufNext->posX = buf->posX;
				bufNext->posY = buf->posY - 1;
				bufNext->prev = buf;
				bufNext->state = bufferMap[buf->posX][buf->posY - 1];
				myQueMain.push(*bufNext);
				if (myQueMain.front().state == 'Y') {
					//mainMap = bufferMap;
					return 1;
				}
			}

						}
						sizeQueMain = myQueMain.size();

						if (myQueMain.size() == 0) {
							return 0;
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