#include<iostream>
#include<fstream>
#include<vector>
#include "../Library/queue.h"

using namespace std;


int main()
{
	vector<string> labirinth;
	Queue* queue = queue_create();

	int Ax = 0, Ay, Bx = 0, By;
	
	ifstream input;
	input.open("input.txt");
	ofstream output;
	output.open("output.txt");

	while (!input.eof()) {
		string t;
		input >> t;
		labirinth.push_back(t);
	}

	for (size_t i = 1; i < labirinth.size() - 1; i++) {
		for (size_t j = 1; j < labirinth[i].length() - 1; j++) {
			if (labirinth[i][j] == 'X') {
				Ax = i;
				Ay = j;
			}
			else if (labirinth[i][j] == 'Y') {
				Bx = i;
				By = j;
			}
			if (Ax != 0 && Bx != 0)
				break;
		}
		if (Ax != 0 && Bx != 0)
			break;
	}

	int currX, currY;
    bool stop = false;
	int dx[4] = { 1, 0, -1, 0 };
	int dy[4] = { 0, 1, 0, -1 };
	labirinth[Ax][Ay] = '0';

	queue_insert(queue, Ax);
	queue_insert(queue, Ay);

	
	while (!queue_empty(queue) && !stop) {
		
		currX = queue_get(queue);
		queue_remove(queue);
		currY = queue_get(queue);
		queue_remove(queue);
		char d = labirinth[currX][currY];

		for (int k = 0; k < 4; ++k)
		{
			int iy = currY + dy[k], ix = currX + dx[k];
			if (labirinth[ix][iy] == 'Y') {
				labirinth[Bx][By] = d;
				stop = true;
				break;
			}
			if (labirinth[ix][iy] == '.') {
				queue_insert(queue, ix);
				queue_insert(queue, iy);
				labirinth[ix][iy] = d + 1;
			}
		}
	}

	if (!stop) {
		output << "IMPOSSIBLE";
		return 0;
	}
	else {
		char d = labirinth[Bx][By];
		labirinth[Ax][Ay] = 'X';
		labirinth[Bx][By] = 'Y';
		while (d > 0) {
			for (int k = 0; k < 4; ++k)
			{
				int iy = By + dy[k], ix = Bx + dx[k];
				if (labirinth[ix][iy] == 'X') {
					d = 0;
					break;
				}
				if (labirinth[ix][iy] == d) {
					labirinth[ix][iy] = 'x';
					By = iy;
					Bx = ix;
				}
			
			}
			d = ((d - '0') - 1) + '0';
		}
	
		for (size_t i = 0; i < labirinth.size(); i++) {
			for (size_t j = 0; j < labirinth[i].length(); j++) {
				
				if (labirinth[i][j] != '#' && labirinth[i][j] != 'x' && labirinth[i][j] != '.' && labirinth[i][j] != 'X' && labirinth[i][j] != 'Y' ) {
					labirinth[i][j] = '.';
				}
				output << labirinth[i][j];
			}
			output << endl;
		}
	}

}
