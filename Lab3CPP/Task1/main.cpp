//Реализовать в проекте Library кольцевой двусвязный список (модуль list) с фиктивным элементом и очередь на основе этого списка (модуль queue).
//Решить задачу, используя реализованную очередь.
//Добавить пример входных данных и описать тест в CMakeLists.txt, который запускает разработанную программу и использует входные данные.
//Задано начальное вещество и список химических реакций, в которых оно превращается в другое вещество. Написать программу, использующую поиск в ширину, и выводящую список веществ, которые можно получить из исходного.
//
//Входные данные
//A
//A->B
//B->C
//D->E
//
//Выходные данные
//B
//C
//В 
//примере из вещества A можно получить вещества B и C.

#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

#include "queue.h"

typedef std::map<std::string, std::vector<std::string>> Reactions;

static std::string trim(const std::string &s)
{
    const char *spaces = " \t\r\n";
    const size_t begin = s.find_first_not_of(spaces);
    if (begin == std::string::npos)
        return "";
    const size_t end = s.find_last_not_of(spaces);
    return s.substr(begin, end - begin + 1);
}

static bool read_input(std::istream &in, std::string &start, Reactions &reactions)
{
    std::string line;
    bool have_start = false;
    int line_no = 0;
    while (std::getline(in, line))
    {
        ++line_no;
        line = trim(line);
        if (line.empty())
            continue;
        if (!have_start)
        {
            start = line;
            have_start = true;
            continue;
        }
        const size_t arrow = line.find("->");
        const std::string from = arrow == std::string::npos ? "" : trim(line.substr(0, arrow));
        const std::string to = arrow == std::string::npos ? "" : trim(line.substr(arrow + 2));
        if (from.empty() || to.empty())
        {
            std::cerr << "Invalid reaction at line " << line_no << ": " << line << "\n";
            return false;
        }
        reactions[from].push_back(to);
    }
    if (!have_start)
    {
        std::cerr << "Start substance is missing\n";
        return false;
    }
    return true;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <input file>\n";
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file)
    {
        std::cerr << "cannot open file " << argv[1] << "\n";
        return 1;
    }

    std::string start;
    Reactions reactions;
    if (!read_input(file, start, reactions))
        return 1;

    Queue<std::string> queue;
    std::set<std::string> visited;
    queue.insert(start);
    visited.insert(start);

    while (!queue.empty())
    {
        const std::string current = queue.get();
        queue.remove();

        const Reactions::const_iterator it = reactions.find(current);
        if (it == reactions.end())
            continue;
        for (const std::string &next : it->second)
        {
            if (visited.insert(next).second)
            {
                std::cout << next << "\n";
                queue.insert(next);
            }
        }
    }
    return 0;
}
