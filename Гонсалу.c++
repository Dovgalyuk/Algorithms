#include <iostream>
#include <array>


using namespace std;


int main()
{
    int i, j, a, tamanhoDaMatriz, * intMatrix;

    cout << "Digite o tamanho da Matriz: ";
    cin >> tamanhoDaMatriz;

    intMatrix = (int*)malloc(tamanhoDaMatriz * tamanhoDaMatriz * sizeof(int));

    for (i = 0; i < tamanhoDaMatriz; ++i)
    {
        for (j = 0; j < tamanhoDaMatriz; ++j)
        {
            cout << "Digite o valor da linha " << i + 1 << " e o valor da coluna " << j + 1 << ": ";
            cin >> intMatrix[i * tamanhoDaMatriz + j];
        }
    }
   cout << "_________________________________\n";
    cout << " Imprimindo a metade da Matriz \n";
    for (i = 0; i < tamanhoDaMatriz; i++) {
        for (j = 0; j < tamanhoDaMatriz; j++) {
            cout << intMatrix[i * tamanhoDaMatriz + j] / 2 << "\t";
        }
        cout << "\n";
    }

    return 0;
}