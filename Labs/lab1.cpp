#include "array.h"
#include <iostream>

using namespace std;

void task1(Array *arr)
{
    size_t size = array_size(arr);

    size_t maxElement = array_get(arr, 0);//Inizializasya max elementa pervim v massive
    for (size_t i = 0; i < size; i += 2)//Idem po chetnim chislam
    {
        size_t currentElement = array_get(arr, i);//Polucheniye teskushego elementa v massive
        if (currentElement > maxElement)
        {
            maxElement = currentElement;//Noviy max element
        }
    }

    cout << "ÌMax element sredi elementov c chetnim indexom: " << maxElement << endl;
}

void task2(Array* arr)
{
    size_t size = array_size(arr);
    cout << "Vvedite interval [a,b]:";
    size_t a;
    size_t b;
    cin >> a >> b;

    size_t zero = 0; //Kol-vo nulevih elementov

    //Peremesheniye ne nulevih elementov v nachalo massiva
    for (size_t i = 0; i < size; ++i)
    {
        size_t currentElement = array_get(arr, i);

        //Proverka,nahoditsa li element v intervale
        if (currentElement < a || currentElement > b)
        {
            //Element v intervale
            Data currentData = Data(currentElement);
            array_set(arr, zero, currentData);
            zero++;
        }
    }

    //Zapolnenie ostavshihsya pozisiy nulyami
    for (size_t i = zero; i < size; ++i)
    {
        Data zeroData = Data(); //Sozdanie object Data s nulevim znacheniyem
        array_set(arr, i, zeroData);
    }
}


void CreateArray(Array* arr) {
    size_t size = array_size(arr);
    for (size_t i = 0; i < size; i++)
        array_set(arr, i, rand());
}

int main()
{
    setlocale (LC_ALL,"ru");
    srand((unsigned int)time(NULL)); //Inizializazya generatora sluchaynih chisel
    Array* arr = nullptr;
    size_t size;

    //task1
    cout << "Vvedite razmer massiva: ";
    cin >> size;
    arr = array_create(size);
    CreateArray(arr);
    cout << "Sgenerirovanniy massiv: ";
    for (size_t i = 0; i < size; ++i)
    {
        cout << array_get(arr, i) << " ";
    }
    cout << endl;
    task1(arr);
    array_delete(arr);

    //task2
    cout << "Vvedite razmer massiva 2: ";
    cin >> size;
    arr = array_create(size);
    CreateArray(arr);
    cout << "Sgenerirovanniy massiv: ";
    for (size_t i = 0; i < size; ++i)
    {
        cout << array_get(arr, i) << " ";
    }
    cout << endl;

    task2(arr);
    //Vivod resultata
    cout << "Izmenenniy massiv: ";
    for (size_t i = 0; i < array_size(arr); ++i)
    {
        cout << array_get(arr, i) << " ";
    }
    cout << endl;
    array_delete(arr);
}
