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
	Vector<Vector<int>*> grid = Vector<Vector<int>*>(100);
	size_t path_length = 0;

	const int num_path = -5, num_lattice = -4, num_dot = -3, num_end = -2, num_start = -1; // made for grid representation
	// int picked because number in path can be more then 9 and we can't visualize "10" in char

public:
	friend istream &operator>>(istream &is, Labirynth& lab)
	{
		string row;
		for (int i = 0; is; i++)
		{
			is >> row;
			lab.col_count = row.length();
			Vector<int>* sub =  new Vector<int>(lab.col_count);
			lab.grid.Set(i, sub);
			for (int j = 0; j < row.length(); j++)
			{
				char symbol = row[j];
				int symbolNum = 0;
				switch (row[j])
				{
				case '#':
					symbolNum = lab.num_lattice;
					break;
				case '.':
					symbolNum = lab.num_dot;
					break;
				case 'Y':
					symbolNum = lab.num_end;
					break;
				case 'X':
					symbolNum = lab.num_start;
					break;

					default: break;	
				}
				lab.grid.GetValue(i)->Set(j, symbolNum);

				if (symbol == 'X')
				{
					lab.x_row = i, lab.x_col = j;
				}
			}
			lab.row_count++;
		}
		lab.row_count--;
		return is;
	}

	void find_path()
	{
		bool found = false;
		Queue queue = Queue();
		
		int curr_row = x_row, curr_col = x_col;
		queue.insert(Coord{ curr_row, curr_col, 0 });
		
		while (grid.GetValue(curr_row)->GetValue(curr_col) != num_end && !queue.is_empty())
		{
			Coord coord = queue.get();
			curr_row = coord.row;
			curr_col = coord.col;
			queue.remove();
	
			for (int i = -1; i <= 1; i++)
			{
				for (int j = -1; j <= 1; j++)
				{
					if (i * i + j * j != 0 && i * j == 0)
					{
						int row = curr_row + i;
						int col = curr_col + j;
						if (row < 0 || col < 0)
						{
							continue;
						}
						
						Data cell = grid.GetValue(row)->GetValue(col);

						if (row < row_count && col < col_count)
						{
							if (cell == num_end)
							{
								grid.GetValue(curr_row)->Set(curr_col, coord.dist + 1);
								curr_row = row;
								curr_col = col;
								found = true;
							}

							else if (cell == num_dot)
							{
								queue.insert(Coord{ row, col, coord.dist + 1 });
								grid.GetValue(curr_row)->Set(curr_col, coord.dist + 1);
							}
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
			Data cell = 0;
			while (cell != 1)
			{	
				for (int i = -1; i <= 1; i++)
				{
					for (int j = -1; j <= 1; j++)
					{
						if (i * i + j * j != 0 && i * j == 0)
						{
							int row = curr_row + i;
							int col = curr_col + j;

							if (row < 0 || col < 0)
							{
								continue;
							}
							
							cell = grid.GetValue(row)->GetValue(col);
							if (cell == 1)
							{
								curr_row = row;
								curr_col = col;
								i = 1, j = 1;
							}
							else if (cell > 0 && cell < prev_number)
							{
								grid.GetValue(row)->Set(col, num_path);
								prev_number = cell;
								curr_row = row;
								curr_col = col;
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
					int cell = grid.GetValue(i)->GetValue(j);
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
	cin >> lab;
	lab.find_path();
}