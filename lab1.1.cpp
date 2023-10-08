// ConsoleApplication12.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <array>
#include <vector>

using namespace std;





    void summapos(const vector<int>& arr, int size) {
        cout << "Massiv:";
        for (int k = 0; k < size; k++) {
            cout << arr[k] << " ";
        }
        cout << endl;
        int sum = 0;
        for (int k = 0; k < size; k++) {
            if (arr[k] > 0 and arr[k] % 2 == 0) {
                sum += arr[k];
            }


        }
        cout << "Summaa (1 zadanie):" << sum << endl;

    }
    void nedel(const vector<int>& arr, int size) {
        cout << "Massiv";
        for (int k = 0; k < size; k++) {
            cout << arr[k] << " ";
        }
        cout << endl;
        for (int i = 0; i < size; ++i) {
            bool digit = false;
            for (int j = 0; j < size; ++j) {
                if (arr[i] % arr[j] == 0 and i != j) {
                    digit = true;
                    break;
                }
            }
            if (!digit) {
                cout << "nedel:" << " " << arr[i] << endl;
            }
        }

    }
    //void print(const vector<int>& arr, int size) {
        //for (int i = 0; i < size; ++i) {
        //    cout << arr[i] << ' ';
      //  }
      //  cout << endl;
  //  }



int main(){
    cout << endl;
    cout << "Input array: ";
    int size;
    cin >> size;
    vector<int> mas(size);
    srand(time(0));
    for (int i = 0; i < size; i++) {
        mas[i] = rand() % 100;
    }
    cout << endl;
    summapos(mas, size);
    nedel(mas, size);
    return 0;
}




