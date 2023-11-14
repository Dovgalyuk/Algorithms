#include<fstream>
#include<iostream>
#include<vector>
#include<string>
#include<queue.h>

using namespace std;

void BFS(vector<string>& labyrinth, const int start_position_height, const int start_position_width)
{
	int position_height = start_position_height, position_width = start_position_width;

	int past_item_position_height=-1, past_item_position_width=-1;

	int change_coordinate[2][8] = { {-1,-1,-1,0,1,1,1,0}, {-1,0,1,1,1,0,-1,-1} }; //1st to y, 2nd to x

	bool f_exit=0;

	Queue* queue = queue_create();

	queue_insert(queue, position_height);
	queue_insert(queue, position_width);

	while (!queue_empty(queue))
	{
		position_height = queue_get(queue);
		queue_remove(queue);

		position_width = queue_get(queue);
		queue_remove(queue);

		if (!f_exit)
		{
			for (int j = 0, x = 0, y = 0; j < 8; j++)  //SÑANNER
			{
				y = position_height + change_coordinate[0][j];
				x = position_width + change_coordinate[1][j];

				if (labyrinth[y][x] == '.')
				{
					queue_insert(queue, y);
					queue_insert(queue, x);
					labyrinth[y][x] = *"#";
				}

				else if (labyrinth[y][x] >= *"0" && labyrinth[y][x] <= *"9")
				{
					f_exit = 1;
					cout << "\nOutput Data: " << labyrinth[y][x];
					break;
				}
			}
		}

		if (past_item_position_height >= 0) labyrinth[past_item_position_height][past_item_position_width] = *".";

		past_item_position_height = position_height;

		past_item_position_width = position_width;

	}

	labyrinth[past_item_position_height][past_item_position_width] = *".";

	labyrinth[start_position_height][start_position_height] = *"X";
}



int main()
{
	vector<string> labyrinth;
	string input;

	string path = "input.txt"; //file added by cmake command 

	ifstream fin;
	fin.open(path);

	char ch;
	int heigh = 0, width = 0;
	int position_height = 0, position_width = 0;

	while (fin.get(ch))
	{
		input += ch;

		if (ch == *"X")
		{
			position_height = heigh;
			position_width = width;
		}

		else if (ch == *"\n")
		{
			heigh++;
			width = -1;
			labyrinth.push_back(input);
			input = "";
		}

		width++;
	}

	fin.close();

	BFS(labyrinth, position_height, position_width);
	
	return 0;
}
