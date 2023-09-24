
#include "../../../Github/Algorithms-University/LibraryCPP/array.h"
#include <iostream>
using namespace std;


struct Array
{
public:
    Data* data;
    Data sizeArr;


};

// create array
Array* array_create(size_t size)
{
    Array* arr = new Array;  //��������� ������ ��� ���������
    arr->sizeArr = size;          //��������� ������ ��� �������� ������� �������
    arr->data = new Data[size];  // ��������� ������ ��� �������� � �������
 
    return arr;
}

// delete array, free memory
void array_delete(Array* arr)
{
    delete[] arr->data;   //�������� �������
    delete arr;    //�������� ���������
}

// returns specified array element
Data array_get(const Array* arr, size_t index)
{
    return arr->data[index];
}

// sets the specified array element to the value
void array_set(Array* arr, size_t index, Data value)
{ 
    arr->data[index] = value;  //���������� �������� � ������ �� ��������� �������


}

// returns array size
size_t array_size(const Array* arr)
{
    return arr->sizeArr;
}

int first_task(const Array* arr,int a, int b) //������ ������� 
{
    int sum=0;
    for (int i=0; i<array_size(arr);i++)
    { 
      
       if (array_get(arr, i) % a == 0 || array_get(arr, i) % b == 0)
       {
           sum += array_get(arr, i);
       }
           
    }
    return sum;

}

int second_task(const Array* arr)
{
    if (array_size(arr) < 5)
    {
        return -1;
    }
    int maxSum = 0;
    int MaxEleIndex = 0;
    for (int i = 0; i < array_size(arr) - 5; i++)
    {
        int sum = 0;
        for (int j = i; j < i + 5; j++)
        {
            sum += array_get(arr, j);
        }
        if (sum > maxSum)
        {
            maxSum = sum;
            MaxEleIndex = i;
        }
    }
    
    return MaxEleIndex;
}
 

int main()
{
    setlocale(LC_ALL, "Russian");
    int sizeofArr;
    int a, b;
    cout << "Enter size of array:";
    cin >> sizeofArr;   
    cout << endl;
    Array* arr= array_create(sizeofArr); //�������� ���������� �������

    arr->sizeArr = sizeofArr;         //����������� ����������� �������

    srand(time(NULL) / 100);            //��������� ��������� �����
    for (int i = 0; i < array_size(arr); i++)
    {
        array_set(arr, i, rand());
    }
    cout << "Enter a and b: ";  //���� ����� � � b
    cin >> a>> b;
    cout << endl;


    cout << "First task answer: "<<first_task(arr, a, b)<<endl; //����� ����������� ������� �������

    if (second_task(arr) == -1)                       //����� ����������� ������� �������
    {
        cout << "Size of array is less than 5 elements." << endl;
    }
    else
    {
        for (int i = second_task(arr); i < second_task(arr) + 5; i++)
        {
            cout << "Second task answer:" <<  array_get(arr, i) << endl;
        }
    }
 
    array_delete(arr);   //�������� �������
    
    return 0;
}