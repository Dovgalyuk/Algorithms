#include <cctype>
#include <iostream>
#include "vector.h"
#include "queue.h"
using namespace std;

struct Labirynth
{
private:
	int x_row = 0, x_col = 0;
	size_t col_count = 0, row_count = 0;
	Vector<Vector<int>*>* grid = new Vector<Vector<int>*>(100);
	size_t path_length = 0;

	const int num_path = -5, num_lattice = -4, num_dot = -3, num_end = -2, num_start = -1; // made for grid representation
	// int picked because number in path can be more then 9 and we can't visualize "10" in char

public:
	istream &operator>>(istream &is)
	{
		string row;
		for (int i = 0; is; i++)
		{
			grid->Set(i, new Vector<int>(100));
			is >> row;
			col_count = row.length();
			for (int j = 0; j < row.length(); j++)
			{
				char symbol = row[j];
				int symbolNum = 0;
				switch (row[j])
				{
				case '#':
					symbolNum = num_lattice;
					break;
				case '.':
					symbolNum = num_dot;
					break;
				case 'Y':
					symbolNum = num_end;
					break;
				case 'X':
					symbolNum = num_start;
					break;

					default: break;	
				}
				grid->GetValue(i)->Set(j, symbolNum);

				if (symbol == 'X')
				{
					x_row = i, x_col = j;
				}
			}
			row_count++;
		}
		row_count--;
		return is;
	}

	void find_path()
	{
		bool found = false;
		Queue* queue = new Queue();
		
		int curr_row = x_row, curr_col = x_col;
		queue->insert(Coord{ curr_row, curr_col, 0 });
		
		while (grid->GetValue(curr_row)->GetValue(curr_col) != num_end 
			&& !queue->is_empty())
		{
			Coord coord = queue->get();
			curr_row = coord.row;
			curr_col = coord.col;
			queue->remove();
	
			for (int i = -1; i <= 1; i++)
			{
				for (int j = -1; j <= 1; j++)
				{
					if (i * i + j * j != 0 && i * j == 0)
					{
						int row = curr_row + i;
						int col = curr_col + j;
						if (row < 0 || col < 0) break;
						
						Data cell = grid->GetValue(row)->GetValue(col);

						if (cell == num_end)
						{
							grid->GetValue(curr_row)->Set(curr_col, coord.dist + 1);
							curr_row = row;
							curr_col = col;
							found = true;
							path_length++;
						}
						
						if (row >= 0 && row < row_count && col >= 0 && col <= col_count &&
							grid->GetValue(row)->GetValue(col) == num_dot)
						{
							queue->insert(Coord{ row, col, coord.dist + 1 });
							grid->GetValue(curr_row)->Set(curr_col, coord.dist + 1);
							

							path_length++;
						}
					}
				}
			}
		}

		if (!found)
		{
			cout << "Impossible";
		}
		else
		{
			int prev_number = path_length + 1;
			queue->insert(Coord{ curr_row, curr_col });
			while (grid->GetValue(curr_row)->GetValue(curr_col) != num_start && !queue->is_empty())
			{
				Coord coord = queue->get();
				curr_row = coord.row;
				curr_col = coord.col;
				queue->remove();
				
				for (int i = -1; i <= 1; i++)
				{
					for (int j = -1; j <= 1; j++)
					{
						if (i * i + j * j != 0 && i * j == 0)
						{
							int row = curr_row + i;
							int col = curr_col + j;

							if (row < 0 || col < 0) break;
							
							int cell = grid->GetValue(row)->GetValue(col);
							if (row >= 0 && row < row_count && col >= 0 && col <= col_count &&
								cell > 0 && cell < prev_number)
							{
								queue->insert(Coord{ row, col });
								grid->GetValue(row)->Set(col, num_path);
								prev_number = cell;
							}
						}
					}
				}
			}

			cout << endl;

			for (int i = 0; i < row_count; i++)
			{
				for (int j = 0; j < col_count; j++)
				{
					int cell = grid->GetValue(i)->GetValue(j);
					if (i == x_row && j == x_col) cout << 'X';
					else if (cell == num_path) cout << 'x';
					else if (cell == num_lattice) cout << '#';
					else if (cell == num_end) cout << 'Y';
					else if (cell == num_start) cout << 'X';
				}
				cout << endl;
			}
			cout << endl << "Length of path is " << path_length;
		}
	}
};


int main()
{
	Labirynth lab;
	lab.operator>>(cin);
	lab.find_path();
}