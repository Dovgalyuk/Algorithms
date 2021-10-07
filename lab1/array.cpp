#include "array.h"
#include "iostream"
#include "math.h"
#include "time.h"

int main() {
    setlocale(LC_ALL, "cp1151");
    srand(time(NULL));
    int k = 0; // k - счетчик
    int sum = 0; // sum - сумма
    float x; // x - среднее арифметическое
    Array<int> arr(10);
    for (int i = 0; i < 10; i++) {
        arr.set(i, rand()%100);
    }

    for (int i = 0; i < arr.size(); i++) {
        if (arr.get(i)>10) {
            sum += arr.get(i);
            k = k + 1;
        }
    }
    x = sum/k;
    std::cout << "Avg " << x;

    return 0;
}