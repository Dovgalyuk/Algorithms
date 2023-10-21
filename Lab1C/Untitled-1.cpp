#include <iostream>


void task1(Array *arr)
{
    cout << "Massiv:";
    for (int k = 0; k < arr.size(); k++) {
        std::cout << arr.get(k) << " ";
    }
    std::cout << std::endl;

    int sum = 0;
    for (int k = 0; k < arr.size(); k++) {
        if (arr.get(k) > 0 && arr.get(k) % 2 == 0) {
            sum += arr.get(k);
        }
}
}

void task2(Array *arr)
{
    cout << "Massiv";
    for (int k = 0; k < arr.size(); k++) {
        cout << arr.get(k) << " ";
    }
    cout << endl;

    for (int i = 0; i < arr.size(); ++i) {
        bool digit = false;
        for (int j = 0; j < arr.size(); ++j) {
            if (arr.get(i) % arr.get(j) == 0 && i != j) {
                digit = true;
                break;
            }
        }
        if (!digit) {
            cout << "nedel:" << " " << arr.get(i) << endl;
        }
    }
}

int main()
{
    Array *arr = NULL;
    /* Create array here */
    cout << "Input array: ";
    int size;
    cin >> size;
    Array mas(size);
    srand(time(0));
    for (int i = 0; i < size; i++) {
        mas.set(i, rand() % 100);
    }
    task1(arr);
    array_delete(arr);
    /* Create another array here */
    cout << "Input array: ";
    int size;
    cin >> size;
    Array mas(size);
    srand(time(0));
    for (int i = 0; i < size; i++) {
        mas.set(i, rand() % 100);
    }
    task2(arr);
    array_delete(arr);
}
