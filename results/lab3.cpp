#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "queue.h"
#include "vector.h"

using namespace std;

int count_step(vector<string> lab)
{
    int count = 0;
    for (int i = 0; i < lab.size(); i++) {
        for (int j = 0; j < lab[i].size(); j++) {
            if (lab[i][j] == 'X') {
                count++;
            }
        }
    }
    return count;
}
bool try_make_step(Queue* queue, vector<string>& lab, int x, int y)
{
    if (x < 0 || x >= lab.size() || y < 0 || y >= lab[0].size() || lab[x][y] != '.')
    {
        return false;
    }
    lab[x][y] = 'X';
    queue_insert(queue, x);
    queue_insert(queue, y);
    return true;
}
void step_in_labirint(Queue* queue, vector<string> &lab)
{
    int x = queue_get(queue);
    queue_remove(queue);
    int y = queue_get(queue);
    queue_remove(queue);
    try_make_step(queue, lab, x, y - 1);
    try_make_step(queue, lab, x - 1, y);
    try_make_step(queue, lab, x, y + 1);
    try_make_step(queue, lab, x +1, y); 
}

int main()
{
    int n = 0,m = 0;
    vector<string> lab;
	setlocale(LC_ALL, "Russian");
    ifstream fin;
    Queue* queue = queue_create();
    string lab_row;
    fin.open("labirint.txt");
    if (!fin.is_open()) {
        cout << "Файл не открыт" << endl;
        return 1;
    }
    else {
        while (!fin.eof()) {
            getline(fin, lab_row);
            lab.push_back(lab_row + "\n");
        }
    }

    int x = 0, y = 0;
    n = lab.size();
    if (n == 0)
    {
        cout << "Файл не содержит данных" << endl;
        return 1;
    }
    else
    {
        m = lab[0].size();
    }
    for (int i = 0; i < lab.size(); i++) {
        if(m != lab[i].size())
        {
            cout << "Файл содержит строки разной длины" << endl;
            return 1;
        }
        for (int j = 0; j < lab[i].size(); j++) { 
            if (lab[i][j] == 'X') {
                x = i;
                y = j;
            }
        }
    }	
    queue_insert(queue,x);
    queue_insert(queue,y);
    while (!queue_empty(queue))
    {
        step_in_labirint(queue,lab);
    }
    cout << count_step(lab) << endl;
    for (int i = 0; i < lab.size(); i++)
    {
        cout << lab[i];
    }
}

