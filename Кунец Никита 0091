#include <iostream>
using namespace std;

int main()
{
    int N;
    cout << "Enter number of values:";
    cin >> N;

    int* array = new int[N];

    for (int i = 0; i < N; i++)
        array[i] = rand() % 10;

    for (int i = 0; i < N; i += 2)
    {
        int tmp = array[i];
        array [i] = array [i + 1];
        array [i + 1] = tmp;
    }
    
     for (int i = 0; i < N;i++)
     cout << array[i] << " ";

     delete [] array;
     return 0;
}
