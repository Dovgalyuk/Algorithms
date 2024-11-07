#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <fstream>

using namespace std;

vector<int> naidit_rasstoianie_ot_vershiny(const vector<vector<int>>& smieznost, int start_vershina) {
    int kolichestvo_vershin = smieznost.size();  
    vector<int> rasstoianie(kolichestvo_vershin, INT_MAX);  
    queue<int> ochened;  

    // Начальная вершина
    rasstoianie[start_vershina] = 0;  // Расстояние до самой себя = 0
    ochened.push(start_vershina);  // Помещаем стартовую вершину в очередь

    // Выполняем BFS
    while (!ochened.empty()) {
        int tekushchaya_vershina = ochened.front();  // Извлекаем текущую вершину из очереди
        ochened.pop();

        // Проходим по всем соседям текущей вершины
        for (int i = 0; i < kolichestvo_vershin; ++i) {
            if (smieznost[tekushchaya_vershina][i] == 1 && rasstoianie[i] == INT_MAX) {
                // Если есть путь к соседу и мы ещё не посетили эту вершину
                rasstoianie[i] = rasstoianie[tekushchaya_vershina] + 1;  // Обновляем расстояние
                ochened.push(i);  // Добавляем соседнюю вершину в очередь
            }
        }
    }

    return rasstoianie;  // Возвращаем массив с расстояниями
}

int main() {
    ifstream inputFile("input.txt");  // Открываем файл для чтения

    // Проверяем, что файл открылся
    if (!inputFile) {
        cerr << "Ошибка: не удалось открыть файл input.txt" << endl;
        return 1;
    }

    int kolichestvo_vershin;
    inputFile >> kolichestvo_vershin;  // Считываем количество вершин

    vector<vector<int>> smieznost(kolichestvo_vershin, vector<int>(kolichestvo_vershin));

    // Вводим матрицу смежности
    for (int i = 0; i < kolichestvo_vershin; ++i) {
        for (int j = 0; j < kolichestvo_vershin; ++j) {
            inputFile >> smieznost[i][j];
        }
    }

    vector<int> rasstoianie = naidit_rasstoianie_ot_vershiny(smieznost, 0);

    // Выводим результаты на экран
    for (int i = 0; i < kolichestvo_vershin; ++i) {
        cout << rasstoianie[i] << endl;
    }

    return 0;
}
