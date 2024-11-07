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

    rasstoianie[start_vershina] = 0;  
    ochened.push(start_vershina);  

    while (!ochened.empty()) {
        int tekushchaya_vershina = ochened.front();  
        ochened.pop();

        for (int i = 0; i < kolichestvo_vershin; ++i) {
            if (smieznost[tekushchaya_vershina][i] == 1 && rasstoianie[i] == INT_MAX) {
                rasstoianie[i] = rasstoianie[tekushchaya_vershina] + 1;  
                ochened.push(i);  
            }
        }
    }

    return rasstoianie;  
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Ошибка: не указан файл для чтения!" << endl;
        return 1;
    }

    ifstream inputFile(argv[1]);  // Используем имя файла, переданное как аргумент
    if (!inputFile) {
        cerr << "Ошибка: не удалось открыть файл " << argv[1] << endl;
        return 1;
    }

    int kolichestvo_vershin;
    inputFile >> kolichestvo_vershin;

    vector<vector<int>> smieznost(kolichestvo_vershin, vector<int>(kolichestvo_vershin));

    for (int i = 0; i < kolichestvo_vershin; ++i) {
        for (int j = 0; j < kolichestvo_vershin; ++j) {
            inputFile >> smieznost[i][j];
        }
    }

    vector<int> rasstoianie = naidit_rasstoianie_ot_vershiny(smieznost, 0);

    for (int i = 0; i < kolichestvo_vershin; ++i) {
        cout << rasstoianie[i] << endl;
    }

    return 0;
}
