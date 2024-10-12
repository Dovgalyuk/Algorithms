#include <iostream>
#include <fstream>
#include "queue.h"
#include <string>

using namespace std;

void waynahod(ifstream& v) {
    string o;
    int strok = 1;
    int stolbec = 1;
    while (v >> o) {
        for (int i = 5; i != 0; i--) {
            stolbec = i;
            if (o[stolbec] == '.' || o[stolbec] == 'X') {
                string sk = to_string(strok);
                string sc = to_string(stolbec);
                sk = sk + sc;

                cout << sk << endl;
            }
        }
        strok++;
    }
}

int main()
{
    ifstream v("input.txt");
    Queue* q = queue_create();
    waynahod(v);
    cin.get();
    queue_delete(q);


}