#include <iostream>
#include <fstream>
#include "queue.h"

int main()
{
    Queue<int> firstQueue, secondQueue;
    std::ifstream fin;
    fin.open("C:/Users/1/CLionProjects/Algorithms/Zadanie3/num_input.txt");
    if (!fin.is_open())
    {
        std::cout << "Error opening INPUT file";
        return 0;
    }
    else {
        std::string buf;
        size_t size;
        getline (fin, buf);
        size = stoi(buf);
        if (size <= 0){
            std::cout << "Wrong size";
            return 0;
        }
        for (size_t k = 0; k < size; k++){
            getline (fin, buf);
            firstQueue.insert(stoi(buf));
        }
        for (size_t k = 0; k < size; k++){
            getline (fin, buf);
            secondQueue.insert(stoi(buf));
        }
    }
    fin.close();

    std::ofstream fout;
    fout.open("C:/Users/1/CLionProjects/Algorithms/Zadanie3/num_output.txt");
    if (!fout.is_open())
    {
        std::cout << "Error opening OUTPUT file";
        return 0;
    }
    else {
        int add = 0;
        int out;
        while (!(firstQueue.empty())){
            out = (firstQueue.get() + secondQueue.get()) + add;
            add = out / 10;
            fout << out % 10 << "\n";
            firstQueue.remove();
            secondQueue.remove();
        }
        if (add != 0){
            fout << add;
        }

    }
    fout.close();
    return 0;
}