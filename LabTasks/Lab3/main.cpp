#include <iostream>
#include <string>
#include "Labyrinth.hpp"

int main () {
    Labyrinth labyrinth;

    std::string path;
    std::cout << "Enter file path: "; 
    std::getline(std::cin, path);
    std::cout << std::endl;

    try{
        labyrinth.uploadLabyrinth(path);
        labyrinth.printLabyrinth();
        std::cout << std::endl;
        labyrinth.findExit();
        labyrinth.printLabyrinth();
    } catch(const char *msg) {
        std::cout << msg << std::endl;
    }
}