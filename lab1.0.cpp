// ConsoleApplication12.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;



class masiv {
private:
    int* arr;
    int size;

public:
    masiv(int ss) {
        size = ss;
        arr = new int[size];
    }
    ~masiv() {
        delete[] arr;
    }
    void randomchik() {
        srand(time(NULL));
        for (int i = 0; i < size; ++i) {
            arr[i] = rand() % 100;
        }
    }
    int summapos() {
        int sum = 0;
        for (int i = 0; i < size; ++i) {
            if (arr[i] > 0 and arr[i] % 2 == 0) {
                sum += arr[i];
            }


        }
        return sum;

    }
    void nedel() {
        bool digit;
        for (int i = 0; i < size; ++i) {
            digit = false;
            for (int j = 0; j < size; ++j) {
                if (arr[i] % arr[j] == 0 and i != j) {
                    digit = true;
                    break;
                }
            }
            if (!digit) {
                cout << arr[i] << endl;
            }
        }

    }
    void print() {
        for (int i = 0; i < size; ++i) {
            cout << arr[i] << ' ';
        }
        cout << endl;
    }
};



int main()
{
    int size;
    cout << "Input size:";
    cin >> size;

    masiv array(size);
    array.randomchik();
    cout << "Elements:";
    array.print();

    int sum = array.summapos();
    cout << "Summaa (1 zadanie):" << sum << endl;
    cout << "Nedelyatsya (2 zadanie):" << endl;
    array.nedel();
    return 0;
}







// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
