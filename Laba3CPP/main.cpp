#include <fstream>
#include <iostream>
#include <string>

#include "queue.h"
#include "vector.h"

using namespace std;

struct Reaction
{
    string from;
    string to;
};

template <typename Data>
void append(Vector<Data> &items, Data value)
{
    size_t index = items.size();
    items.resize(index + 1);
    items.set(index, value);
}

bool contains(const Vector<string> &substances, const string &name)
{
    for (size_t i = 0; i < substances.size(); ++i)
    {
        if (substances.get(i) == name)
            return true;
    }
    return false;
}

string trim(const string &text)
{
    size_t first = text.find_first_not_of(" \t\r\n");
    if (first == string::npos)
        return "";

    size_t last = text.find_last_not_of(" \t\r\n");
    return text.substr(first, last - first + 1);
}

int main(int argc, char **argv)
{
    if (argc > 2)
    {
        cerr << "Expected one input file\n";
        return 1;
    }

    ifstream file;
    istream *input = &cin;
    if (argc == 2)
    {
        file.open(argv[1]);
        if (!file)
        {
            cerr << "Cannot open input file\n";
            return 1;
        }
        input = &file;
    }

    string start;
    if (!getline(*input, start) || trim(start).empty())
    {
        cerr << "Missing initial substance\n";
        return 1;
    }
    start = trim(start);

    Vector<Reaction> reactions;
    string line;
    while (getline(*input, line))
    {
        line = trim(line);
        if (line.empty())
            continue;

        size_t arrow = line.find("->");
        if (arrow == string::npos || line.find("->", arrow + 2) != string::npos)
        {
            cerr << "Invalid reaction: " << line << '\n';
            return 1;
        }

        string from = trim(line.substr(0, arrow));
        string to = trim(line.substr(arrow + 2));
        if (from.empty() || to.empty())
        {
            cerr << "Invalid reaction: " << line << '\n';
            return 1;
        }
        Reaction reaction = {from, to};
        append(reactions, reaction);
    }

    Queue<string> queue;
    Vector<string> visited;
    Vector<string> obtained;
    queue.insert(start);
    append(visited, start);

    while (!queue.empty())
    {
        string current = queue.get();
        queue.remove();

        for (size_t i = 0; i < reactions.size(); ++i)
        {
            Reaction reaction = reactions.get(i);
            if (reaction.from != current)
                continue;

            if (!contains(obtained, reaction.to))
            {
                cout << reaction.to << '\n';
                append(obtained, reaction.to);
            }

            if (!contains(visited, reaction.to))
            {
                append(visited, reaction.to);
                queue.insert(reaction.to);
            }
        }
    }
    return 0;
}
