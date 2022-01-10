#include <iostream>
#include <fstream>
#include "queue.h"

int main()
{
    Queue<int> queue;
    std::ifstream fin;
    fin.open("C:/Users/1/CLionProjects/Algorithms/Zadanie3/num_input.txt");
    size_t size;
    std::string buf;
    if (!fin.is_open())
    {
        std::cout << "Error opening INPUT file";
        return 0;
    }
    else {
        getline (fin, buf);
        size = stoi(buf);
        if (size <= 0){
            std::cout << "Wrong size";
            return 0;
        }
        for (size_t k = 0; k < size; k++){
            getline (fin, buf);
            queue.insert(stoi(buf));
        }
    }

    std::ofstream fout;
    fout.open("C:/Users/1/CLionProjects/Algorithms/Zadanie3/num_output.txt");
    if (!fout.is_open())
    {
        std::cout << "Error opening OUTPUT file";
        return 0;
    }
    else {
        int add = 0;
        int out, firstNum, secondNum;
        while (!(queue.empty())){
            for (size_t k = 0; k < size; k++){
                getline (fin, buf);
                secondNum = stoi(buf);
                firstNum = queue.get();
                out = (secondNum + firstNum) + add;
                add = out / 10;
                fout << out % 10 << "\n";
                queue.remove();
            }
        }
        if (add != 0){
            fout << add;
        }

    }

    fin.close();
    fout.close();
    return 0;
}