#include <iostream>
#include <stack.h>  // ���������� ���������� ��� 
// ������������� �����
#include <fstream>
std::ifstream fileln;
fileln.open("output.txt");
using namespase std;

int main()
{
   
  
        setlocale(LC_ALL, "rus");
        char buff[50];//�������������
         else
    {
    fin >> buff; // ������� ������ ����� �� �����
    cout << buff << endl; // ���������� ��� �����

    fin.getline(buff, 50); // ������� ������ �� �����
    fin.close(); // ��������� ����
    cout << buff << endl; // ���������� ��� ������
    }











        stack <int> steck;  // ������� ����

        int i = 0;

        

            steck.push(a);  // ��������� ��������� �����
            i++;
        }

        if (steck.empty()) cout << "���� �� ����";  // ��������� ���� �� ���� (���)

        cout << "������� ������� �����: " << steck.top() << endl; // ������� ������� �������
        cout << "������� ������ ������� ������� " << endl;

        steck.pop();  // ������� ������� �������

        cout << "� ��� ����� ������� �������: " << steck.top(); // ������� ��� �����
                                                                // ������� ������� 
        system("pause");
        return 0;
    }
}
